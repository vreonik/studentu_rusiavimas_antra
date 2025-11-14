#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include "studentas.h"
#include "studentas_struct.h"
#include "failu_generavimas.h"
#include "nuskaityti.h"
#include "util.h"

void testuotiStruct(int studentuKiekis, const std::string& failoVardas) {
    auto start = std::chrono::high_resolution_clock::now();
    
    auto studentai = nuskaityti(failoVardas);
    std::vector<Studentas> vargsiukai, kietakiai;
    
    for (const auto& s : studentai) {
        auto [vid, med] = skaiciuoti_galutinius(s);
        if (vid < 5.0)
            vargsiukai.push_back(s);
        else
            kietakiai.push_back(s);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Struct: " << studentuKiekis << " studentų - " << duration.count() << "ms" << std::endl;
}

void testuotiClass(int studentuKiekis, const std::string& failoVardas) {
    auto start = std::chrono::high_resolution_clock::now();
    
    auto studentai = nuskaityti(failoVardas);
    std::vector<Studentas> vargsiukai, kietakiai;
    
    for (const auto& s : studentai) {
        auto [vid, med] = s.skaiciuotiGalutinius(); // Naudojame klasės metodą
        if (vid < 5.0)
            vargsiukai.push_back(s);
        else
            kietakiai.push_back(s);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Class:  " << studentuKiekis << " studentų - " << duration.count() << "ms" << std::endl;
}

int main() {
    std::vector<int> dydziai = {100000, 1000000};
    
    std::cout << "=== STRUCT vs CLASS SPRARTOS PALYGINIMAS ===" << std::endl;
    
    for (int dydis : dydziai) {
        std::string failoVardas = "test_" + std::to_string(dydis) + ".txt";
        
        std::cout << "\n--- Testas su " << dydis << " studentų ---" << std::endl;
        
        std::ifstream testas(failoVardas);
        if (!testas.good()) {
            std::cout << "Generuojamas failas " << failoVardas << "..." << std::endl;
            generuoti_faila(dydis, failoVardas, 5);
        }
        testas.close();
        
        testuotiStruct(dydis, failoVardas);
        testuotiClass(dydis, failoVardas);
    }
    
    return 0;
}
