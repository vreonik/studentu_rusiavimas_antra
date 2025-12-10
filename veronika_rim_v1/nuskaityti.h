/**
 * @file nuskaityti.h
 * @brief Failų skaitymo funkcijų deklaracijos
 *
 * Šiame header faile deklaruojamos funkcijos skirtos skaityti studentų duomenis iš failų
 * į skirtingus konteinerių tipus ir duomenų struktūras.
 */

#pragma once
#include <string>
#include <vector>
#include <list>
#include "studentas.h"
#include "studentas_struct.h"

/**
 * @brief Nuskaityti studentų duomenis į Studentas objektų vektorių
 * @param failas Skaitymo failo pavadinimas
 * @return Vektorius su visais studentais iš failo
 */
std::vector<Studentas> nuskaityti(const std::string& failas);

/**
 * @brief Nuskaityti studentų duomenis į Studentas objektų sąrašą
 * @param failas Skaitymo failo pavadinimas
 * @return Sąrašas su visais studentais iš failo
 */
std::list<Studentas> nuskaityti_i_list(const std::string& failas);

/**
 * @brief Nuskaityti studentų duomenis į StudentasStruct objektų vektorių
 * @param failas Skaitymo failo pavadinimas
 * @return Vektorius su visais studentais kaip struct iš failo
 */
std::vector<StudentasStruct> nuskaityti_struct(const std::string& failas);

/**
 * @brief Nuskaityti studentų duomenis į StudentasStruct objektų sąrašą
 * @param failas Skaitymo failo pavadinimas
 * @return Sąrašas su visais studentais kaip struct iš failo
 */
std::list<StudentasStruct> nuskaityti_i_list_struct(const std::string& failas);
