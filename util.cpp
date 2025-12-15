    /**
     * @file util.cpp
     * @brief Pagalbinių funkcijų implementacijos
     */

    #include "util.h"
    #include <algorithm>

    /**
     * @brief Pašalinti kelią ir plėtinį iš failo pavadinimo
     * @param kelias Pilnas failo kelias
     * @return Failo vardas be kelio ir plėtinio
     */
    std::string be_priesdelio(const std::string &kelias){
        auto pos = kelias.find_last_of("/\\");
        std::string vardas = (pos == std::string::npos) ? kelias : kelias.substr(pos + 1);
        auto taskas = vardas.find_last_of('.');
        if (taskas == std::string::npos) return vardas;
        return vardas.substr(0, taskas);
    }
