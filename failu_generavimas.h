/**
 * @file failu_generavimas.h
 * @brief Failų generavimo pagalbinės funkcijos
 *
 * Šiame header faile pateikiamos funkcijos skirtos generuoti testinius failus
 * su atsitiktiniais studentų duomenimis testavimo tikslams.
 */

#pragma once
#include <string>

/**
 * @brief Sugeneruoti atsitiktinį pažymį nurodytame rėžyje
 * @param min Minimali pažymio reikšmė (numatytasis: 1)
 * @param max Maksimali pažymio reikšmė (numatytasis: 10)
 * @return Atsitiktinis pažymys tarp min ir max imtinai
 */
int gen_paz(int min = 1, int max = 10);

/**
 * @brief Sugeneruoti testinį failą su atsitiktiniais studentų duomenimis
 * @param n Studentų skaičius
 * @param failas Išvestinio failo pavadinimas
 * @param nd_kiek Namų darbų pažymių skaičius vienam studentui (numatytasis: 5)
 */
void generuoti_faila(int n, const std::string& failas, int nd_kiek = 5);
