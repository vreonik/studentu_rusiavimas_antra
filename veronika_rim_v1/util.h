    /**
     * @file util.h
     * @brief Pagalbinių funkcijų deklaracijos
     */

    #pragma once
    #include <string>
    #include "studentas.h"
    #include "studentas_struct.h"

    /**
     * @brief Pašalinti kelią ir plėtinį iš failo pavadinimo
     * @param kelias Pilnas failo kelias
     * @return Failo vardas be kelio ir plėtinio
     */
    std::string be_priesdelio(const std::string &kelias);
