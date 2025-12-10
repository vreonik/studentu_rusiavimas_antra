    /**
     * @file studentas_struct.h
     * @brief StudentasStruct struktūros deklaracija
     *
     * Šiame faile deklaruojama struct versija studentų duomenims,
     * naudojama spartos palyginimo testams.
     */

    #pragma once
    #include <string>
    #include <vector>
    #include <iostream>
    #include <algorithm>
    #include <numeric>

    /**
     * @struct StudentasStruct
     * @brief Studentų duomenų struktūra (struct versija)
     */
    struct StudentasStruct {
        std::string vardas;       ///< Studento vardas
        std::string pavarde;      ///< Studento pavardė
        std::vector<int> nd;      ///< Namų darbų pažymiai
        int egzas;                ///< Egzamino pažymys

        /**
         * @brief Apskaičiuoti namų darbų vidurkį
         * @return Vidurkis
         */
        double skaiciuotiVidurki() const;
        
        /**
         * @brief Apskaičiuoti namų darbų medianą
         * @return Mediana
         */
        double skaiciuotiMediana() const;
        
        /**
         * @brief Apskaičiuoti galutinius pažymius
         * @return Porą (vidurkis, mediana)
         */
        std::pair<double, double> skaiciuotiGalutinius() const;
    };

    /**
     * @brief Įvesties operatorius struct versijai
     */
    std::istream& operator>>(std::istream& is, StudentasStruct& studentas);

    /**
     * @brief Išvesties operatorius struct versijai
     */
    std::ostream& operator<<(std::ostream& os, const StudentasStruct& studentas);
