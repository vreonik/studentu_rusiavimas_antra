    /**
     * @file nuskaityti.cpp
     * @brief Failų skaitymo funkcijų implementacijos studentų duomenims
     *
     * Šiame faile yra funkcijos skirtos skaityti studentų duomenis iš failų
     * į skirtingus konteinerių tipus (vector, list) ir duomenų struktūras
     * (class vs struct).
     */

    #include "nuskaityti.h"
    #include <fstream>
    #include <sstream>
    #include <iostream>
    #include <algorithm>
    #include <list>

    /**
     * @brief Nuskaityti studentų duomenis į Studentas objektų vektorių
     * @param failas Skaitymo failo pavadinimas
     * @return Vektorius su visais studentais iš failo
     */
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

    /**
     * @brief Nuskaityti studentų duomenis į Studentas objektų sąrašą
     * @param failas Skaitymo failo pavadinimas
     * @return Sąrašas su visais studentais iš failo
     */
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

    /**
     * @brief Nuskaityti studentų duomenis į StudentasStruct objektų vektorių
     * @param failas Skaitymo failo pavadinimas
     * @return Vektorius su visais studentais kaip struct iš failo
     */
    std::vector<StudentasStruct> nuskaityti_struct(const std::string& failas) {
        std::ifstream fd(failas);
        if (!fd.is_open()) {
            std::cerr << "Klaida: Nepavyko atidaryti failo: " << failas << std::endl;
            return {};
        }

        std::vector<StudentasStruct> visi;
        std::string eil;
        std::getline(fd, eil);

        while (std::getline(fd, eil)) {
            if (eil.empty()) continue;
            
            std::stringstream ss(eil);
            StudentasStruct s;
            
            ss >> s.vardas >> s.pavarde;
            
            s.nd.clear();
            int pazymys;
            while (ss >> pazymys) {
                s.nd.push_back(pazymys);
            }
            
            if (!s.nd.empty()) {
                s.egzas = s.nd.back();
                s.nd.pop_back();
            }
            
            visi.push_back(s);
        }

        return visi;
    }

    /**
     * @brief Nuskaityti studentų duomenis į StudentasStruct objektų sąrašą
     * @param failas Skaitymo failo pavadinimas
     * @return Sąrašas su visais studentais kaip struct iš failo
     */
    std::list<StudentasStruct> nuskaityti_i_list_struct(const std::string& failas) {
        std::ifstream fd(failas);
        if (!fd.is_open()) {
            std::cerr << "Klaida: Nepavyko atidaryti failo: " << failas << std::endl;
            return {};
        }

        std::list<StudentasStruct> result;
        std::string eil;
        std::getline(fd, eil);

        while (std::getline(fd, eil)) {
            if (eil.empty()) continue;
            
            std::stringstream ss(eil);
            StudentasStruct s;
            
            ss >> s.vardas >> s.pavarde;
            
            s.nd.clear();
            int pazymys;
            while (ss >> pazymys) {
                s.nd.push_back(pazymys);
            }
            
            if (!s.nd.empty()) {
                s.egzas = s.nd.back();
                s.nd.pop_back();
            }
            
            result.push_back(s);
        }

        return result;
    }
