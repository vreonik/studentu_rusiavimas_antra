#pragma once
#include "studentas.h"
#include "studentas_struct.h"
#include <vector>
#include <list>

/**
 * @struct TestoRezultatai
 * @brief Testavimo rezultatų struktūra
 */
struct TestoRezultatai {
    long long skirstymo_laikas;  ///< Skirstymo laikas milisekundėmis
    size_t atmintis_vargsiukai;  ///< Atmintis vargsiukams
    size_t atmintis_kietakiai;   ///< Atmintis kietakiams
    size_t atmintis_bendra;      ///< Bendra atmintis
};

template<typename Container>
TestoRezultatai strategija_1(const Container& visi_stud,
                            Container& vargsiukai,
                            Container& kietakiai,
                            char pasirinkimas);

template<typename Container>
TestoRezultatai strategija_2(Container& visi_stud,
                            Container& vargsiukai,
                            char pasirinkimas);

template<typename Container>
TestoRezultatai strategija_3(Container& visi_stud,
                            Container& vargsiukai,
                            char pasirinkimas);

//STRUCT versijos
TestoRezultatai strategija_1_struct(std::vector<StudentasStruct>& visi_stud,
                                   std::vector<StudentasStruct>& vargsiukai,
                                   std::vector<StudentasStruct>& kietakiai,
                                   char pasirinkimas);

TestoRezultatai strategija_2_struct(std::vector<StudentasStruct>& visi_stud,
                                   std::vector<StudentasStruct>& vargsiukai,
                                   char pasirinkimas);

TestoRezultatai strategija_3_struct(std::vector<StudentasStruct>& visi_stud,
                                   std::vector<StudentasStruct>& vargsiukai,
                                   char pasirinkimas);

TestoRezultatai strategija_2(std::vector<Studentas>& visi_stud,
                            std::vector<Studentas>& vargsiukai,
                            char pasirinkimas);

TestoRezultatai strategija_2(std::list<Studentas>& visi_stud,
                            std::list<Studentas>& vargsiukai,
                            char pasirinkimas);

TestoRezultatai strategija_3(std::vector<Studentas>& visi_stud,
                            std::vector<Studentas>& vargsiukai,
                            char pasirinkimas);

TestoRezultatai strategija_3(std::list<Studentas>& visi_stud,
                            std::list<Studentas>& vargsiukai,
                            char pasirinkimas);
