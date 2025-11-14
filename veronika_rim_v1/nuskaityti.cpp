#include "nuskaityti.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <list>

std::vector<Studentas> nuskaityti(const std::string& failas){
    std::ifstream fd(failas);
    if (!fd.is_open()) {
        std::cerr << "Klaida: Nepavyko atidaryti failo: " << failas << std::endl;
        return {};
    }

    std::vector<Studentas> visi;
    std::string eil;
    std::getline(fd, eil);

    while (std::getline(fd, eil)) {
        if (eil.empty()) continue;
        
        std::stringstream ss(eil);
        Studentas s;
        ss >> s;
        
        visi.push_back(s);
    }

    return visi;
}

std::list<Studentas> nuskaityti_i_list(const std::string& failas) {
    std::ifstream fd(failas);
    if (!fd.is_open()) {
        std::cerr << "Klaida: Nepavyko atidaryti failo: " << failas << std::endl;
        return {};
    }

    std::list<Studentas> result;
    std::string eil;
    std::getline(fd, eil);

    while (std::getline(fd, eil)) {
        if (eil.empty()) continue;
        
        std::stringstream ss(eil);
        Studentas s;
        ss >> s;
        
        result.push_back(s);
    }

    return result;
}
