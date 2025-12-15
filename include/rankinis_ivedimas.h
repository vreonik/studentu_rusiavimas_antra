    /**
     * @file rankinis_ivedimas.h
     * @brief Rankinio įvedimo funkcijos studentų duomenims
     *
     * Šiame header faile pateikiamos šabloninės funkcijos skirtos rankiniu būdu
     * įvesti studentų duomenis per konsolės įvestį.
     */

    #pragma once
    #include <iostream>
    #include <string>
    #include <vector>
    #include <list>
    #include <sstream>
    #include <limits>
    #include "studentas.h"
    #include "failu_generavimas.h"

    /**
     * @brief Rankinis studentų duomenų įvedimas
     * @tparam Container Konteinerio tipas (vector, list)
     * @param visi Nuoroda į konteinerį, kuriame saugomi studentai
     */
    template<typename Container>
    void rankinis_ivedimas(Container& visi) {
        char dar = 't';
        while (dar == 't' || dar == 'T') {
            if constexpr (std::is_same_v<Container, std::vector<Studentas>>) {
                //Vector atveju emplace_back
                visi.emplace_back();
                Studentas& s = visi.back();
                std::cout << "Objekto adresas atmintyje: " << &s << std::endl;
                
                std::string vardas, pavarde;
                std::cout << "Vardas: ";
                std::cin >> vardas;
                std::cout << "Pavardė: ";
                std::cin >> pavarde;
                
                s.setVardas(vardas);
                s.setPavarde(pavarde);
                
            } else {
                //List atveju naują objektą
                Studentas s;
                std::cout << "Objekto adresas atmintyje: " << &s << std::endl;
                
                std::string vardas, pavarde;
                std::cout << "Vardas: ";
                std::cin >> vardas;
                std::cout << "Pavardė: ";
                std::cin >> pavarde;
                
                s.setVardas(vardas);
                s.setPavarde(pavarde);
                
                visi.push_back(std::move(s));
            }
            
            std::cout << "Generuoti (r) ar įvesti (i)? ";
            char pas;
            std::cin >> pas;

            if (pas == 'i' || pas == 'I') {
                std::cout << "Įveskite ND (tuščia eilutė - pabaiga):\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::vector<int> nd;
                while (true) {
                    std::cout << "Pažymys: ";
                    std::string eil;
                    std::getline(std::cin, eil);
                    if (eil.empty()) break;
                    std::stringstream ss(eil);
                    int paz;
                    if (ss >> paz) nd.push_back(paz);
                }
                
                if constexpr (std::is_same_v<Container, std::vector<Studentas>>) {
                    Studentas& s = visi.back();
                    s.setNd(nd);
                } else {
                    auto& s = visi.back();
                    const_cast<Studentas&>(s).setNd(nd);
                }
                
                int egzas;
                std::cout << "Egzamino pažymys: ";
                std::cin >> egzas;
                
                if constexpr (std::is_same_v<Container, std::vector<Studentas>>) {
                    Studentas& s = visi.back();
                    s.setEgzas(egzas);
                } else {
                    auto& s = visi.back();
                    const_cast<Studentas&>(s).setEgzas(egzas);
                }
                
            } else {
                int kiek;
                std::cout << "Kiek ND generuoti? ";
                std::cin >> kiek;
                std::vector<int> nd;
                for (int i = 0; i < kiek; i++) nd.push_back(gen_paz());
                
                if constexpr (std::is_same_v<Container, std::vector<Studentas>>) {
                    Studentas& s = visi.back();
                    s.setNd(nd);
                    s.setEgzas(gen_paz());
                } else {
                    auto& s = visi.back();
                    const_cast<Studentas&>(s).setNd(nd);
                    const_cast<Studentas&>(s).setEgzas(gen_paz());
                }
            }
            
            std::cout << "Dar pridėti? (t/T): ";
            std::cin >> dar;
        }
    }
