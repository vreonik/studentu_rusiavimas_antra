#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <limits>
#include "studentas.h"
#include "failu_generavimas.h"

template<typename Container>
void rankinis_ivedimas(Container& visi) {
    char dar = 't';
    while (dar == 't' || dar == 'T') {
        Studentas s;
        std::string vardas, pavarde;
        
        std::cout << "Vardas: ";
        std::cin >> vardas;
        std::cout << "Pavardė: ";
        std::cin >> pavarde;
        
        s.setVardas(vardas);
        s.setPavarde(pavarde);
        
        std::cout << "Objekto adresas atmintyje: " << &s << std::endl;
        
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
            s.setNd(nd);
            
            int egzas;
            std::cout << "Egzamino pažymys: ";
            std::cin >> egzas;
            s.setEgzas(egzas);
        } else {
            int kiek;
            std::cout << "Kiek ND generuoti? ";
            std::cin >> kiek;
            std::vector<int> nd;
            for (int i = 0; i < kiek; i++) nd.push_back(gen_paz());
            s.setNd(nd);
            s.setEgzas(gen_paz());
        }
        visi.push_back(s);
        
        std::cout << "Dar pridėti? (t/T): ";
        std::cin >> dar;
    }
}
