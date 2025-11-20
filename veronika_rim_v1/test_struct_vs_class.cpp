#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include "studentas.h"
#include "studentas_struct.h"
#include "failu_generavimas.h"
#include "nuskaityti.h"
#include "util.h"
#include "strategijos.h"

struct DetalusTestoRezultatai {
    long long skaitymo_laikas;
    long long skirstymo_laikas;
    long long bendras_laikas;
    size_t vargsiukai;
    size_t kietakiai;
};

DetalusTestoRezultatai testuoti_struct_strategija3(const std::string& failoVardas) {
    DetalusTestoRezultatai rez;
    
    auto start_viso = std::chrono::high_resolution_clock::now();
    
    auto start_skaitymo = std::chrono::high_resolution_clock::now();
    auto studentai_struct = nuskaityti_struct(failoVardas);
    auto end_skaitymo = std::chrono::high_resolution_clock::now();
    rez.skaitymo_laikas = std::chrono::duration_cast<std::chrono::milliseconds>(end_skaitymo - start_skaitymo).count();
    
    auto start_skirstymo = std::chrono::high_resolution_clock::now();
    std::vector<StudentasStruct> vargsiukai_struct;
    
    TestoRezultatai strategijos_rez = strategija_3_struct(studentai_struct, vargsiukai_struct, 'v');
    rez.skirstymo_laikas = strategijos_rez.skirstymo_laikas;
    
    auto end_skirstymo = std::chrono::high_resolution_clock::now();
    
    auto end_viso = std::chrono::high_resolution_clock::now();
    rez.bendras_laikas = std::chrono::duration_cast<std::chrono::milliseconds>(end_viso - start_viso).count();
    
    rez.vargsiukai = vargsiukai_struct.size();
    rez.kietakiai = studentai_struct.size(); // kietakiai liko originaliame konteineryje
    
    return rez;
}

DetalusTestoRezultatai testuoti_class_strategija3(const std::string& failoVardas) {
    DetalusTestoRezultatai rez;
    
    auto start_viso = std::chrono::high_resolution_clock::now();
    
    auto start_skaitymo = std::chrono::high_resolution_clock::now();
    auto studentai_class = nuskaityti(failoVardas);
    auto end_skaitymo = std::chrono::high_resolution_clock::now();
    rez.skaitymo_laikas = std::chrono::duration_cast<std::chrono::milliseconds>(end_skaitymo - start_skaitymo).count();
    
    auto start_skirstymo = std::chrono::high_resolution_clock::now();
    std::vector<Studentas> vargsiukai_class;
    
    TestoRezultatai strategijos_rez = strategija_3(studentai_class, vargsiukai_class, 'v');
    rez.skirstymo_laikas = strategijos_rez.skirstymo_laikas;
    
    auto end_skirstymo = std::chrono::high_resolution_clock::now();
    
    auto end_viso = std::chrono::high_resolution_clock::now();
    rez.bendras_laikas = std::chrono::duration_cast<std::chrono::milliseconds>(end_viso - start_viso).count();
    
    rez.vargsiukai = vargsiukai_class.size();
    rez.kietakiai = studentai_class.size();
    
    return rez;
}

void testuoti_su_failu(const std::string& failoVardas, int testu_kartai = 3) {
    std::cout << "\n=== STRUCT vs CLASS TESTAS SU GREIČIAUSIA STRATEGIJA 3 ===\n";
    std::cout << "Failas: " << failoVardas << std::endl;
    
    std::ifstream testas(failoVardas);
    if (!testas.good()) {
        std::cout << "Klaida: Failas '" << failoVardas << "' neegzistuoja!\n";
        return;
    }
    testas.close();
    
    auto temp = nuskaityti(failoVardas);
    long dydis = temp.size();
    std::cout << "Studentų skaičius: " << dydis << std::endl;
    std::cout << "Testavimo kartai: " << testu_kartai << std::endl;
    std::cout << "Naudojama: Strategija 3 (greičiausia)\n\n";
    
    long long total_struct_skaitymas = 0, total_struct_skirstymas = 0, total_struct_bendras = 0;
    long long total_class_skaitymas = 0, total_class_skirstymas = 0, total_class_bendras = 0;
    size_t vargsiukai_count = 0, kietakiai_count = 0;
    
    for (int kartas = 1; kartas <= testu_kartai; kartas++) {
        std::cout << "--- Kartas " << kartas << "/" << testu_kartai << " ---\n";
        
        auto rez_struct = testuoti_struct_strategija3(failoVardas);
        total_struct_skaitymas += rez_struct.skaitymo_laikas;
        total_struct_skirstymas += rez_struct.skirstymo_laikas;
        total_struct_bendras += rez_struct.bendras_laikas;
        
        auto rez_class = testuoti_class_strategija3(failoVardas);
        total_class_skaitymas += rez_class.skaitymo_laikas;
        total_class_skirstymas += rez_class.skirstymo_laikas;
        total_class_bendras += rez_class.bendras_laikas;
        
        vargsiukai_count = rez_struct.vargsiukai;
        kietakiai_count = rez_struct.kietakiai;
        
        std::cout << "STRUCT:\n";
        std::cout << "  Skaitymas: " << rez_struct.skaitymo_laikas << "ms\n";
        std::cout << "  Skirstymas: " << rez_struct.skirstymo_laikas << "ms\n";
        std::cout << "  Bendras: " << rez_struct.bendras_laikas << "ms\n";
        
        std::cout << "CLASS:\n";
        std::cout << "  Skaitymas: " << rez_class.skaitymo_laikas << "ms\n";
        std::cout << "  Skirstymas: " << rez_class.skirstymo_laikas << "ms\n";
        std::cout << "  Bendras: " << rez_class.bendras_laikas << "ms\n";
        
        if (rez_struct.bendras_laikas > 0) {
            double skirtumas = ((double)rez_class.bendras_laikas / rez_struct.bendras_laikas - 1.0) * 100;
            std::cout << "Bendras skirtumas: " << std::fixed << std::setprecision(1) << skirtumas << "%\n";
        }
        std::cout << std::endl;
    }
    
    long long vid_struct_skaitymas = total_struct_skaitymas / testu_kartai;
    long long vid_struct_skirstymas = total_struct_skirstymas / testu_kartai;
    long long vid_struct_bendras = total_struct_bendras / testu_kartai;
    
    long long vid_class_skaitymas = total_class_skaitymas / testu_kartai;
    long long vid_class_skirstymas = total_class_skirstymas / testu_kartai;
    long long vid_class_bendras = total_class_bendras / testu_kartai;
    
    std::cout << "=== GALUTINIAI REZULTATAI (VIDURKIS iš " << testu_kartai << " kartų) ===\n";
    std::cout << "STRUCT:\n";
    std::cout << "  Skaitymas: " << vid_struct_skaitymas << "ms\n";
    std::cout << "  Skirstymas: " << vid_struct_skirstymas << "ms\n";
    std::cout << "  Bendras: " << vid_struct_bendras << "ms\n";
    
    std::cout << "CLASS:\n";
    std::cout << "  Skaitymas: " << vid_class_skaitymas << "ms\n";
    std::cout << "  Skirstymas: " << vid_class_skirstymas << "ms\n";
    std::cout << "  Bendras: " << vid_class_bendras << "ms\n";
    
    std::cout << "Studentų pasiskirstymas:\n";
    std::cout << "  Vargsiukai: " << vargsiukai_count << "\n";
    std::cout << "  Kietakiai: " << kietakiai_count << "\n";
    
    if (vid_struct_bendras > 0) {
        double vid_skirtumas = ((double)vid_class_bendras / vid_struct_bendras - 1.0) * 100;
        std::cout << "VIDUTINIS BENDRAS SKIRTUMAS: " << std::fixed << std::setprecision(1) << vid_skirtumas << "%\n";
        
        if (vid_skirtumas > 0) {
            std::cout << "CLASS lėtesnė už STRUCT\n";
        } else if (vid_skirtumas < 0) {
            std::cout << "CLASS greitesnė už STRUCT\n";
        } else {
            std::cout << "CLASS ir STRUCT vienodo greičio\n";
        }
    }
    
    std::ofstream rezultatai("struct_vs_class_rezultatai.txt", std::ios::app);
    rezultatai << dydis << ",struct," << vid_struct_skaitymas << "," << vid_struct_skirstymas << ","
               << vid_struct_bendras << "," << vargsiukai_count << "," << kietakiai_count << "\n";
    rezultatai << dydis << ",class," << vid_class_skaitymas << "," << vid_class_skirstymas << ","
               << vid_class_bendras << "," << vargsiukai_count << "," << kietakiai_count << "\n";
    rezultatai.close();
    
    std::cout << "\nRezultatai išsaugoti į: struct_vs_class_rezultatai.txt\n";
}

void testuoti_sugeneruotus_failus(int testu_kartai = 3) {
    std::vector<int> dydziai = {1000, 10000, 100000, 1000000};
    
    std::cout << "\n=== STRUCT vs CLASS TESTAS SU SUGENERUOTAIS FAILAIS ===\n";
    std::cout << "Dydžiai: ";
    for (int dydis : dydziai) std::cout << dydis << " ";
    std::cout << "\n";
    std::cout << "Testavimo kartai: " << testu_kartai << std::endl;
    std::cout << "Naudojama: Strategija 3 (greičiausia)\n";
    
    std::ofstream rezultatai("struct_vs_class_rezultatai.txt");
    rezultatai << "Dydis,Tipas,Skaitymas(ms),Skirstymas(ms),Bendras(ms),Vargsiukai,Kietakiai\n";
    rezultatai.close();
    
    for (int dydis : dydziai) {
        std::string failoVardas = "struct_class_test_" + std::to_string(dydis) + ".txt";
        
        std::cout << "\n=== Generuojamas ir testuojamas failas su " << dydis << " studentų ===\n";
        
        auto gen_start = std::chrono::high_resolution_clock::now();
        std::cout << "Generuojamas failas... ";
        generuoti_faila(dydis, failoVardas, 5);
        auto gen_end = std::chrono::high_resolution_clock::now();
        auto gen_laikas = std::chrono::duration_cast<std::chrono::milliseconds>(gen_end - gen_start).count();
        std::cout << "baigta (" << gen_laikas << "ms)\n";
        
        testuoti_su_failu(failoVardas, testu_kartai);
    }
    
    std::cout << "\n=== VISI TESTAI BAIGTI ===\n";
    std::cout << "Rezultatai išsaugoti į: struct_vs_class_rezultatai.txt\n";
}

void testuoti_struct_vs_class() {
    std::cout << "=== STRUCT vs CLASS SPRARTOS PALYGINIMAS ===\n";
    std::cout << "NAUDOJAMA: Strategija 3 (greičiausia)\n";
    std::cout << "Pasirinkite testavimo būdą:\n";
    std::cout << " 1 - Testuoti su pasirinktu failu\n";
    std::cout << " 2 - Sugeneruoti ir testuoti standartinius failus\n";
    std::cout << "Pasirinkimas: ";
    
    int pasirinkimas;
    std::cin >> pasirinkimas;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (pasirinkimas == 1) {
        std::cout << "Įveskite failo pavadinimą: ";
        std::string failoVardas;
        std::getline(std::cin, failoVardas);
        
        if (failoVardas.empty()) {
            failoVardas = "kursiokai.txt";
        }
        
        testuoti_su_failu(failoVardas, 3);
        
    } else if (pasirinkimas == 2) {
        testuoti_sugeneruotus_failus(3);
        
    } else {
        std::cout << "Neteisingas pasirinkimas!\n";
    }
}
