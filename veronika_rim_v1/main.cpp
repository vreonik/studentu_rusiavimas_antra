#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <chrono>
#include <limits>

#include "studentas.h"
#include "nuskaityti.h"
#include "failu_generavimas.h"
#include "rankinis_ivedimas.h"
#include "konteineriu_testavimas.h"
#include "apdorojimas.h"
#include "util.h"
#include "strategijos.h"

using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::list;

using Laikmatis = std::chrono::high_resolution_clock;
using ms = std::chrono::milliseconds;

using StudentuVector = std::vector<Studentas>;
using StudentuList = std::list<Studentas>;

void testuoti_programa();
void testuoti_strategijas();
void naudoti_strategija_su_failu();

int main() {
    
    cout << "STUDENTŲ RŪŠIAVIMO SISTEMA v1.5\n";
    cout << "Pasirinkite režimą:\n"
         << " f - skaityti iš failo\n"
         << " g - sugeneruoti failą\n"
         << " p - rankinis įvedimas\n"
         << " t - testuoti konteinerius\n"
         << " s - strategijų palyginimas\n"
         << " n - naudoti konkrečią strategiją\n"
         << " x - testuoti struct vs class spartą\n"
         << " d - demonstracinė programa (Rule of Three + I/O operatoriai)\n"
         << " Pasirinkimas: ";

    char rez;
    cin >> rez;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (rez == 'd' || rez == 'D') {
        demonstruotiVisusRežimus();
        return 0;
    }

    if (rez == 'x' || rez == 'X') {
        testuoti_struct_vs_class();
        return 0;
    }

    if (rez == 's' || rez == 'S') {
        testavimo_rezimas = true;
        testuoti_strategijas();
        return 0;
    }

    if (rez == 'n' || rez == 'N') {
        naudoti_strategija_su_failu();
        return 0;
    }

    if (rez == 't' || rez == 'T') {
        testavimo_rezimas = true;
        
        cout << "Konteinerių palyginimo pasirinkimas:\n"
             << " s - sugeneruoti naujus failus\n"
             << " e - naudoti esamą failą\n"
             << " o - optimizavimo testas\n"
             << " Pasirinkimas: ";
        char palyginimo_tipas;
        cin >> palyginimo_tipas;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (palyginimo_tipas == 'e' || palyginimo_tipas == 'E') {
            testuoti_konteinerius_su_pasirinktu_failu();
        } else if (palyginimo_tipas == 'o' || palyginimo_tipas == 'O') {
            system("./test_optimization.sh");
        } else {
            testuoti_konteinerius_sugeneruotus();
        }
        return 0;
    }

    char konteinerio_tipas = 'v';
    char rikiuoti_kriterijus = 'v';

    if (rez == 'f' || rez == 'F' || rez == 'g' || rez == 'G' || rez == 'p' || rez == 'P') {
        cout << "Pasirinkite konteinerio tipą:\n"
             << " v - std::vector (rekomenduojama)\n"
             << " l - std::list\n"
             << " Pasirinkimas: ";
        cin >> konteinerio_tipas;

        cout << "Rikiuoti pagal:\n"
             << " v - vidurkį\n"
             << " m - medianą\n"
             << " p - vardą\n"
             << " Pasirinkimas: ";
        cin >> rikiuoti_kriterijus;

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if (rez == 'g' || rez == 'G') {
        cout << "Failo pavadinimas: ";
        string fname;
        std::getline(cin, fname);
        if (fname.empty()) fname = "kursiokai.txt";
        
        cout << "Kiek įrašų generuoti? ";
        int N;
        cin >> N;
        
        cout << "Kiek ND pažymių? ";
        int nd;
        cin >> nd;

        auto g_s = Laikmatis::now();
        generuoti_faila(N, fname, nd);
        auto g_e = Laikmatis::now();
        cout << "Sugeneruota per " << std::chrono::duration_cast<ms>(g_e - g_s).count() << "ms\n";
        
        cout << "Naudoti šį failą dabar? (t/T): ";
        char d;
        cin >> d;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (d == 't' || d == 'T') {
            cout << "Pasirinkite galutinio pažymio skaičiavimo būdą:\n"
                 << " v - vidurkis\n"
                 << " m - mediana\n"
                 << " a - abu\n"
                 << " Pasirinkimas: ";
            char budas;
            cin >> budas;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (konteinerio_tipas == 'v' || konteinerio_tipas == 'V') {
                apdoroti_faila<StudentuVector>(fname, budas, rikiuoti_kriterijus);
            } else {
                apdoroti_faila<StudentuList>(fname, budas, rikiuoti_kriterijus);
            }
        }
        return 0;
    }

    if (rez == 'f' || rez == 'F') {
        cout << "Failo pavadinimas: ";
        string fname;
        std::getline(cin, fname);
        if (fname.empty()) fname = "kursiokai.txt";

        cout << "Pasirinkite galutinio pažymio skaičiavimo būdą:\n"
             << " v - vidurkis\n"
             << " m - mediana\n"
             << " a - abu\n"
             << " Pasirinkimas: ";
        char budas;
        cin >> budas;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (konteinerio_tipas == 'v' || konteinerio_tipas == 'V') {
            apdoroti_faila<StudentuVector>(fname, budas, rikiuoti_kriterijus);
        } else {
            apdoroti_faila<StudentuList>(fname, budas, rikiuoti_kriterijus);
        }
        return 0;
    }

    if (rez == 'p' || rez == 'P') {
        cout << "Pasirinkite galutinio pažymio skaičiavimo būdą:\n"
             << " v - vidurkis\n"
             << " m - mediana\n"
             << " a - abu\n"
             << " Pasirinkimas: ";
        char budas;
        cin >> budas;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (konteinerio_tipas == 'v' || konteinerio_tipas == 'V') {
            StudentuVector studentai;
            rankinis_ivedimas(studentai);
            long long skirstymo_ms = 0, rusiavimo_ms = 0, irasymo_ms = 0;
            klasifikuoti_ir_irasyti(studentai, budas, "vargsiukai_rankiniai.txt",
                                     "kietakiai_rankiniai.txt", skirstymo_ms, rusiavimo_ms, irasymo_ms, rikiuoti_kriterijus);
        } else {
            StudentuList studentai;
            rankinis_ivedimas(studentai);
            long long skirstymo_ms = 0, rusiavimo_ms = 0, irasymo_ms = 0;
            klasifikuoti_ir_irasyti(studentai, budas, "vargsiukai_rankiniai.txt",
                                     "kietakiai_rankiniai.txt", skirstymo_ms, rusiavimo_ms, irasymo_ms, rikiuoti_kriterijus);
        }
        return 0;
    }

    cout << "Nesuprantamas pasirinkimas.\n";
    return 0;
}

void testuoti_strategijas() {
    cout << "STRATEGIJŲ TESTAVIMAS\n";
    cout << "Pasirinkite testavimo būdą:\n"
         << " s - sugeneruoti naujus failus\n"
         << " e - naudoti esamą failą\n"
         << " Pasirinkimas: ";
    
    char pasirinkimas;
    cin >> pasirinkimas;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (pasirinkimas == 'e' || pasirinkimas == 'E') {
        cout << "Įveskite failo pavadinimą: ";
        string fname;
        std::getline(cin, fname);
        
        if (fname.empty()) fname = "kursiokai.txt";
        
        testuoti_visas_strategijas(fname);
    } else {
        testuoti_strategijas_su_visais_dydziais();
    }
}

void naudoti_strategija_su_failu() {
    cout << "STRATEGIJOS NAUDOJIMAS SU FAILU\n";
    cout << "Įveskite failo pavadinimą: ";
    string fname;
    std::getline(cin, fname);
    
    if (fname.empty()) fname = "kursiokai.txt";

    std::ifstream testas(fname);
    if (!testas.good()) {
        cout << "Klaida: Failas '" << fname << "' neegzistuoja!\n";
        return;
    }
    testas.close();

    cout << "Pasirinkite strategiją:\n"
         << " 1 - Dvi naujos grupės\n"
         << " 2 - Viena nauja grupė + trynimas\n"
         << " 3 - STL algoritmai\n"
         << " Pasirinkimas: ";
    int strategija;
    cin >> strategija;

    if (strategija < 1 || strategija > 3) {
        cout << "Neteisingas strategijos pasirinkimas!\n";
        return;
    }

    cout << "Pasirinkite konteinerio tipą:\n"
         << " v - std::vector (rekomenduojama)\n"
         << " l - std::list\n"
         << " Pasirinkimas: ";
    char konteinerio_tipas;
    cin >> konteinerio_tipas;

    cout << "Pasirinkite galutinio pažymio skaičiavimo būdą:\n"
         << " v - vidurkis\n"
         << " m - mediana\n"
         << " Pasirinkimas: ";
    char budas;
    cin >> budas;

    auto start = Laikmatis::now();
    
    if (konteinerio_tipas == 'v' || konteinerio_tipas == 'V') {
        auto visi = nuskaityti(fname);
        StudentuVector vargsiukai, kietakiai;
        
        TestoRezultatai rez;
        switch(strategija) {
            case 1:
                rez = strategija_1(visi, vargsiukai, kietakiai, budas);
                break;
            case 2:
                rez = strategija_2(visi, vargsiukai, budas);
                kietakiai = std::move(visi);
                break;
            case 3:
                rez = strategija_3(visi, vargsiukai, budas);
                kietakiai = std::move(visi);
                break;
        }
        
        cout << "Skirstymas užtruko: " << rez.skirstymo_laikas << "ms\n";
        cout << "Vargsiukų: " << vargsiukai.size() << "\n";
        cout << "Kietakių: " << kietakiai.size() << "\n";
        cout << "Atmintis: " << rez.atmintis_bendra / 1024 << " KB\n";
        
    } else {
        auto visi = nuskaityti_i_list(fname);
        StudentuList vargsiukai, kietakiai;
        
        TestoRezultatai rez;
        switch(strategija) {
            case 1:
                rez = strategija_1(visi, vargsiukai, kietakiai, budas);
                break;
            case 2:
                rez = strategija_2(visi, vargsiukai, budas);
                kietakiai = std::move(visi);
                break;
            case 3:
                rez = strategija_3(visi, vargsiukai, budas);
                kietakiai = std::move(visi);
                break;
        }
        
        cout << "Skirstymas užtruko: " << rez.skirstymo_laikas << "ms\n";
        cout << "Vargsiukų: " << vargsiukai.size() << "\n";
        cout << "Kietakių: " << kietakiai.size() << "\n";
        cout << "Atmintis: " << rez.atmintis_bendra / 1024 << " KB\n";
    }
    
    auto end = Laikmatis::now();
    cout << "Visas apdorojimas užtruko: " << std::chrono::duration_cast<ms>(end - start).count() << "ms\n";
}

void testuoti_programa() {
    vector<int> dydziai = {1000, 10000, 100000, 1000000, 10000000};
    int nd_kiek = 5;

    cout << "Testavimas su " << dydziai.size() << " dydžiais (OPTIMIZUOTAS):\n";
    cout << "Dydžiai: ";
    for (int dydis : dydziai) {
        cout << dydis << " ";
    }
    cout << "\n";

    for (int N : dydziai) {
        cout << "\n=== Testas su " << N << " įrašų\n";
        string fname = "test_" + std::to_string(N) + ".txt";

        cout << "Generuojamas failas...";
        auto gen_pradzia = Laikmatis::now();
        generuoti_faila(N, fname, nd_kiek);
        auto gen_pabaiga = Laikmatis::now();
        cout << "Sugeneruota per " << std::chrono::duration_cast<ms>(gen_pabaiga - gen_pradzia).count() << "ms\n";

        cout << "Testuojamas vector... ";
        auto v_start = Laikmatis::now();
        apdoroti_faila<StudentuVector>(fname, 'v', 'v');
        auto v_end = Laikmatis::now();
        cout << "Užtruko: " << std::chrono::duration_cast<ms>(v_end - v_start).count() << "ms\n";

        cout << "Testuojamas list... ";
        auto l_start = Laikmatis::now();
        apdoroti_faila<StudentuList>(fname, 'v', 'v');
        auto l_end = Laikmatis::now();
        cout << "Užtruko: " << std::chrono::duration_cast<ms>(l_end - l_start).count() << "ms\n";
    }
}

template<typename Container>
Container optimizuotas_nuskaitymas(const std::string& fname) {
    Container studentai;
    std::ifstream fd(fname);
    
    if (!fd.good()) {
        throw std::runtime_error("Failas '" + fname + "' neegzistuoja arba nepasiekiamas");
    }

    std::string eilute;
    std::getline(fd, eilute);

    while (std::getline(fd, eilute)) {
        if (eilute.empty()) continue;
        
        std::istringstream iss(eilute);
        Studentas studentas;
        
        std::string vardas, pavarde;
        iss >> vardas >> pavarde;
        studentas.setVardas(std::move(vardas));
        studentas.setPavarde(std::move(pavarde));
        
        std::vector<int> pazymiai;
        int pazymys;
        while (iss >> pazymys) {
            pazymiai.push_back(pazymys);
        }
        
        if (!pazymiai.empty()) {
            studentas.setEgzas(pazymiai.back());
            pazymiai.pop_back();
            studentas.setNd(std::move(pazymiai));
        }
        
        if constexpr (std::is_same_v<Container, StudentuVector>) {
            studentai.push_back(std::move(studentas));
        } else {
            studentai.push_back(std::move(studentas));
        }
    }
    
    fd.close();
    return studentai;
}
