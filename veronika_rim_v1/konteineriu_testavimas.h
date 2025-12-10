/**
 * @file konteineriu_testavimas.h
 * @brief Funkcijos konteinerių palyginimo testavimui
 *
 * Šiame header faile pateikiamos įvairios funkcijos skirtos testuoti ir palyginti
 * skirtingus konteinerių tipus (vector, list) ir rūšiavimo strategijas.
 */

#pragma once
#include <string>
#include <vector>
#include <list>
#include "studentas.h"
#include "strategijos.h"

/**
 * @brief Testuoti konteinerius su konkrečiu failu
 * @param fname Įvestinio failo pavadinimas
 */
void testuoti_konteinerius_su_failu(const std::string& fname);

/**
 * @brief Testuoti konteinerius su sugeneruotais įvairaus dydžio failais
 */
void testuoti_konteinerius_sugeneruotus();

/**
 * @brief Testuoti konteinerius su vartotojo pasirinktu failu
 */
void testuoti_konteinerius_su_pasirinktu_failu();

/**
 * @brief Testuoti visas strategijas su konkrečiu failu
 * @param fname Įvestinio failo pavadinimas
 */
void testuoti_visas_strategijas(const std::string& fname);

/**
 * @brief Testuoti strategijas su visais iš anksto nustatytais dydžiais
 */
void testuoti_strategijas_su_visais_dydziais();

/**
 * @brief Atlikti išsamią strategijų analizę
 * @param fname Įvestinio failo pavadinimas
 * @param testu_kartai Testų iteracijų skaičius (numatytasis: 3)
 */
void atlikti_isamiai_analize(const std::string& fname, int testu_kartai = 3);

/**
 * @brief Palyginti strategijas pagal duomenų dydį
 */
void palyginti_strategijas_pagal_dydi();

/**
 * @brief Testuoti struct vs class našumą
 */
void testuoti_struct_vs_class();
