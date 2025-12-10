    /**
     * @file failu_generavimas.cpp
     * @brief Failų generavimo funkcijų implementacijos
     *
     * Šiame faile yra funkcijų implementacijos skirtos generuoti testinius failus
     * su atsitiktiniais studentų duomenimis.
     */

    #include "failu_generavimas.h"
    #include <fstream>
    #include <random>

    /**
     * @brief Sugeneruoti atsitiktinį pažymį nurodytame rėžyje
     * @param min Minimali pažymio reikšmė (numatytasis: 1)
     * @param max Maksimali pažymio reikšmė (numatytasis: 10)
     * @return Atsitiktinis pažymys tarp min ir max imtinai
     */
    int gen_paz(int min, int max){
        static std::mt19937 mt(std::random_device{}());
        std::uniform_int_distribution<int> dist(min, max);
        return dist(mt);
    }

    /**
     * @brief Sugeneruoti testinį failą su atsitiktiniais studentų duomenimis
     * @param n Studentų skaičius
     * @param failas Išvestinio failo pavadinimas
     * @param nd_kiek Namų darbų pažymių skaičius vienam studentui (numatytasis: 5)
     */
    void generuoti_faila(int n, const std::string& failas, int nd_kiek){
        std::ofstream fs(failas);
        fs << "Vardas Pavarde";
        for (int i = 1; i <= nd_kiek; i++)
            fs << " ND" << i;
        fs << " Egzaminas\n";

        for (int i = 1; i <= n; i++) {
            fs << "Vardas" << i << " Pavarde" << i;
            for (int j = 0; j < nd_kiek; j++)
                fs << " " << gen_paz(1, 10);
            fs << " " << gen_paz(1, 10) << "\n";
        }
    }
