    /**
     * @file strategijos.h
     * @brief Studentų skirstymo strategijų deklaracijos
     */

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

    /**
     * @brief Strategija 1: kurti dvi naujas grupes
     * @tparam Container Konteinerio tipas
     * @param visi_stud Visi studentai
     * @param vargsiukai Išvesties konteineris vargsiukams
     * @param kietakiai Išvesties konteineris kietakiams
     * @param pasirinkimas Skaičiavimo būdas ('v' - vidurkis, 'm' - mediana)
     * @return Testo rezultatai
     */
    template<typename Container>
    TestoRezultatai strategija_1(const Container& visi_stud,
                                Container& vargsiukai,
                                Container& kietakiai,
                                char pasirinkimas);

    /**
     * @brief Strategija 2: viena nauja grupė + trynimas
     * @tparam Container Konteinerio tipas
     * @param visi_stud Visi studentai (modifikuojamas)
     * @param vargsiukai Išvesties konteineris vargsiukams
     * @param pasirinkimas Skaičiavimo būdas
     * @return Testo rezultatai
     */
    template<typename Container>
    TestoRezultatai strategija_2(Container& visi_stud,
                                Container& vargsiukai,
                                char pasirinkimas);

    /**
     * @brief Strategija 3: STL algoritmai su partition
     * @tparam Container Konteinerio tipas
     * @param visi_stud Visi studentai (modifikuojamas)
     * @param vargsiukai Išvesties konteineris vargsiukams
     * @param pasirinkimas Skaičiavimo būdas
     * @return Testo rezultatai
     */
    template<typename Container>
    TestoRezultatai strategija_3(Container& visi_stud,
                                Container& vargsiukai,
                                char pasirinkimas);

    //STRUCT versijos
    /**
     * @brief Strategija 1 struct versijai
     */
    TestoRezultatai strategija_1_struct(std::vector<StudentasStruct>& visi_stud,
                                       std::vector<StudentasStruct>& vargsiukai,
                                       std::vector<StudentasStruct>& kietakiai,
                                       char pasirinkimas);

    /**
     * @brief Strategija 2 struct versijai
     */
    TestoRezultatai strategija_2_struct(std::vector<StudentasStruct>& visi_stud,
                                       std::vector<StudentasStruct>& vargsiukai,
                                       char pasirinkimas);

    /**
     * @brief Strategija 3 struct versijai
     */
    TestoRezultatai strategija_3_struct(std::vector<StudentasStruct>& visi_stud,
                                       std::vector<StudentasStruct>& vargsiukai,
                                       char pasirinkimas);

    /**
     * @brief Strategija 2 vektoriaus specializacija
     */
    TestoRezultatai strategija_2(std::vector<Studentas>& visi_stud,
                                std::vector<Studentas>& vargsiukai,
                                char pasirinkimas);

    /**
     * @brief Strategija 2 sąrašo specializacija
     */
    TestoRezultatai strategija_2(std::list<Studentas>& visi_stud,
                                std::list<Studentas>& vargsiukai,
                                char pasirinkimas);

    /**
     * @brief Strategija 3 vektoriaus specializacija
     */
    TestoRezultatai strategija_3(std::vector<Studentas>& visi_stud,
                                std::vector<Studentas>& vargsiukai,
                                char pasirinkimas);

    /**
     * @brief Strategija 3 sąrašo specializacija
     */
    TestoRezultatai strategija_3(std::list<Studentas>& visi_stud,
                                std::list<Studentas>& vargsiukai,
                                char pasirinkimas);
