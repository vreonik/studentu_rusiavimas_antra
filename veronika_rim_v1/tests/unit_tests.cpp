
#include "studentas.h"
#include "studentas_struct.h"
#include "strategijos.h"
#include "nuskaityti.h"
#include "util.h"
#include "failu_generavimas.h"
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <filesystem>

TEST(StudentasTest, DefaultConstructor) {
    Studentas s;
    EXPECT_TRUE(s.getVardas().empty());
    EXPECT_TRUE(s.getPavarde().empty());
    EXPECT_TRUE(s.getNd().empty());
    EXPECT_EQ(s.getEgzas(), 0);
}

TEST(StudentasTest, ParametrizedConstructor) {
    Studentas s("Jonas", "Jonaitis");
    EXPECT_EQ(s.getVardas(), "Jonas");
    EXPECT_EQ(s.getPavarde(), "Jonaitis");
    EXPECT_TRUE(s.getNd().empty());
    EXPECT_EQ(s.getEgzas(), 0);
}

TEST(StudentasTest, FullConstructor) {
    std::vector<int> nd = {8, 9, 7};
    Studentas s("Ona", "Onaite", nd, 9);
    EXPECT_EQ(s.getVardas(), "Ona");
    EXPECT_EQ(s.getPavarde(), "Onaite");
    EXPECT_EQ(s.getNd().size(), 3);
    EXPECT_EQ(s.getNd()[0], 8);
    EXPECT_EQ(s.getNd()[1], 9);
    EXPECT_EQ(s.getNd()[2], 7);
    EXPECT_EQ(s.getEgzas(), 9);
}

TEST(StudentasTest, CopyConstructor) {
    std::vector<int> nd = {10, 9, 8};
    Studentas s1("Petras", "Petraitis", nd, 8);
    Studentas s2 = s1;
    
    EXPECT_EQ(s2.getVardas(), "Petras");
    EXPECT_EQ(s2.getPavarde(), "Petraitis");
    EXPECT_EQ(s2.getNd().size(), 3);
    EXPECT_EQ(s2.getEgzas(), 8);
}

TEST(StudentasTest, MoveConstructor) {
    std::vector<int> nd = {7, 8, 9};
    Studentas s1("Testas", "Testavimas", nd, 10);
    Studentas s2 = std::move(s1);
    
    EXPECT_EQ(s2.getVardas(), "Testas");
    EXPECT_EQ(s2.getPavarde(), "Testavimas");
    EXPECT_EQ(s2.getNd().size(), 3);
    EXPECT_EQ(s2.getEgzas(), 10);
}

TEST(StudentasTest, AssignmentOperator) {
    Studentas s1("A", "A", {8, 9}, 8);
    Studentas s2;
    s2 = s1;
    
    EXPECT_EQ(s2.getVardas(), "A");
    EXPECT_EQ(s2.getPavarde(), "A");
    EXPECT_GT(s2.getNd().size(), 0);
    EXPECT_GE(s2.getEgzas(), 1);
}

TEST(StudentasTest, AverageCalculation) {
    std::vector<int> nd = {8, 9, 7};
    Studentas s("Vardenis", "Pavardenis", nd, 8);
    
    double expected_avg = (8 + 9 + 7) / 3.0;
    double actual_avg = s.skaiciuotiVidurki();
    
    EXPECT_NEAR(actual_avg, expected_avg, 0.001);
}

TEST(StudentasTest, MedianCalculation) {
    std::vector<int> nd = {8, 10, 7, 9, 6};
    Studentas s("Test", "User", nd, 8);
    
    double expected_median = 8.0;
    double actual_median = s.skaiciuotiMediana();
    
    EXPECT_NEAR(actual_median, expected_median, 0.001);
}

TEST(StudentasTest, FinalGradeCalculation) {
    std::vector<int> nd = {8, 9, 7};
    Studentas s("Student", "Test", nd, 8);
    
    auto [vid, med] = s.skaiciuotiGalutinius();
    double expected_vid = 0.4 * 8.0 + 0.6 * 8;
    double expected_med = 0.4 * 8.0 + 0.6 * 8;
    
    EXPECT_NEAR(vid, expected_vid, 0.001);
    EXPECT_NEAR(med, expected_med, 0.001);
}

TEST(StudentasTest, ComparisonOperators) {
    Studentas s1("A", "A", {8, 9}, 8);
    Studentas s2("B", "B", {7, 8}, 8);
    
    EXPECT_TRUE(s1 > s2);
    EXPECT_FALSE(s1 < s2);
    EXPECT_TRUE(s1 != s2);
    EXPECT_FALSE(s1 == s2);
}

TEST(StudentasTest, SettersAndGetters) {
    Studentas s;
    
    s.setVardas("Naujas");
    s.setPavarde("Studentas");
    s.setEgzas(9);
    s.setNd({10, 9, 8});
    
    EXPECT_EQ(s.getVardas(), "Naujas");
    EXPECT_EQ(s.getPavarde(), "Studentas");
    EXPECT_EQ(s.getEgzas(), 9);
    EXPECT_EQ(s.getNd().size(), 3);
    EXPECT_EQ(s.getNd()[0], 10);
    EXPECT_EQ(s.getNd()[1], 9);
    EXPECT_EQ(s.getNd()[2], 8);
}

TEST(StudentasTest, StreamingOperators) {
    Studentas s("Testas", "Output", {8, 9}, 8);
    std::ostringstream oss;
    oss << s;
    std::string output = oss.str();
    
    EXPECT_TRUE(output.find("Testas") != std::string::npos);
    EXPECT_TRUE(output.find("Output") != std::string::npos);
    
    std::istringstream iss("Jonas Jonaitis 8 9 7 0 8");
    Studentas s2;
    iss >> s2;
    
    EXPECT_EQ(s2.getVardas(), "Jonas");
    EXPECT_EQ(s2.getPavarde(), "Jonaitis");
    EXPECT_GT(s2.getNd().size(), 0);
    EXPECT_GE(s2.getEgzas(), 1);
}

TEST(StudentasStructTest, StructOperations) {
    StudentasStruct s;
    s.vardas = "Jonas";
    s.pavarde = "Jonaitis";
    s.nd = {8, 9, 7};
    s.egzas = 8;
    
    EXPECT_EQ(s.vardas, "Jonas");
    EXPECT_EQ(s.pavarde, "Jonaitis");
    EXPECT_EQ(s.nd.size(), 3);
    EXPECT_EQ(s.egzas, 8);
    
    double vid = s.skaiciuotiVidurki();
    double expected_vid = (8 + 9 + 7) / 3.0;
    EXPECT_NEAR(vid, expected_vid, 0.001);
}

TEST(StudentasStructTest, StructMedian) {
    StudentasStruct s;
    s.nd = {8, 10, 7, 9, 6};
    double med = s.skaiciuotiMediana();
    EXPECT_NEAR(med, 8.0, 0.001);
}

TEST(StrategijosTest, Strategija1_Vector_Basic) {
    std::vector<Studentas> visi = {
        Studentas("A", "A", {8, 9}, 8),
        Studentas("B", "B", {5, 6}, 5),
        Studentas("C", "C", {10, 10}, 10),
        Studentas("D", "D", {4, 4}, 4)
    };
    
    std::vector<Studentas> vargsiukai, kietakiai;
    [[maybe_unused]] TestoRezultatai rez = strategija_1(visi, vargsiukai, kietakiai, 'v');
    
    EXPECT_EQ(vargsiukai.size(), 1);
    EXPECT_EQ(kietakiai.size(), 3);
    EXPECT_GE(rez.skirstymo_laikas, 0);
}

TEST(StrategijosTest, Strategija1_List_Basic) {
    std::list<Studentas> visi = {
        Studentas("A", "A", {8, 9}, 8),
        Studentas("B", "B", {4, 4}, 4),
        Studentas("C", "C", {10, 10}, 10)
    };
    
    std::list<Studentas> vargsiukai, kietakiai;
    [[maybe_unused]] TestoRezultatai rez = strategija_1(visi, vargsiukai, kietakiai, 'v');
    
    EXPECT_EQ(vargsiukai.size(), 1);
    EXPECT_EQ(kietakiai.size(), 2);
}

TEST(StrategijosTest, Strategija2_Vector) {
    std::vector<Studentas> visi = {
        Studentas("A", "A", {8, 9}, 8),
        Studentas("B", "B", {4, 4}, 4),
        Studentas("C", "C", {10, 10}, 10)
    };
    
    std::vector<Studentas> vargsiukai;
    [[maybe_unused]] TestoRezultatai rez = strategija_2(visi, vargsiukai, 'v');
    
    EXPECT_EQ(vargsiukai.size(), 1);
    EXPECT_EQ(visi.size(), 2);
}

TEST(StrategijosTest, Strategija3_Vector) {
    std::vector<Studentas> visi = {
        Studentas("A", "A", {8, 9}, 8),
        Studentas("B", "B", {4, 4}, 4),
        Studentas("C", "C", {10, 10}, 10)
    };
    
    std::vector<Studentas> vargsiukai;
    [[maybe_unused]] TestoRezultatai rez = strategija_3(visi, vargsiukai, 'v');
    
    EXPECT_EQ(vargsiukai.size(), 1);
    EXPECT_EQ(visi.size(), 2);
}

TEST(EdgeCaseTest, EmptyStudentList) {
    std::vector<Studentas> visi;
    std::vector<Studentas> vargsiukai, kietakiai;
    
    [[maybe_unused]] TestoRezultatai rez = strategija_1(visi, vargsiukai, kietakiai, 'v');
    
    EXPECT_EQ(vargsiukai.size(), 0);
    EXPECT_EQ(kietakiai.size(), 0);
}

TEST(EdgeCaseTest, AllStudentsFail) {
    std::vector<Studentas> visi = {
        Studentas("A", "A", {4, 4}, 4),
        Studentas("B", "B", {3, 3}, 3),
        Studentas("C", "C", {2, 2}, 2)
    };
    
    std::vector<Studentas> vargsiukai, kietakiai;
    [[maybe_unused]] TestoRezultatai rez = strategija_1(visi, vargsiukai, kietakiai, 'v');
    
    EXPECT_EQ(vargsiukai.size(), 3);
    EXPECT_EQ(kietakiai.size(), 0);
}

TEST(EdgeCaseTest, AllStudentsPass) {
    std::vector<Studentas> visi = {
        Studentas("A", "A", {8, 9}, 8),
        Studentas("B", "B", {9, 9}, 9),
        Studentas("C", "C", {10, 10}, 10)
    };
    
    std::vector<Studentas> vargsiukai, kietakiai;
    [[maybe_unused]] TestoRezultatai rez = strategija_1(visi, vargsiukai, kietakiai, 'v');
    
    EXPECT_EQ(vargsiukai.size(), 0);
    EXPECT_EQ(kietakiai.size(), 3);
}

TEST(EdgeCaseTest, SingleStudent) {
    std::vector<Studentas> visi = {
        Studentas("Vienas", "Studentas", {5, 5}, 5)
    };
    
    std::vector<Studentas> vargsiukai, kietakiai;
    [[maybe_unused]] TestoRezultatai rez = strategija_1(visi, vargsiukai, kietakiai, 'v');
    
    EXPECT_EQ(vargsiukai.size(), 0);
    EXPECT_EQ(kietakiai.size(), 1);
}

TEST(UtilTest, BePriesdelioFunction) {
    EXPECT_EQ(be_priesdelio("failas.txt"), "failas");
    EXPECT_EQ(be_priesdelio("data.csv"), "data");
    EXPECT_EQ(be_priesdelio("be_pletinio"), "be_pletinio");
    EXPECT_EQ(be_priesdelio(""), "");
}

TEST(NuskaitytiTest, CreateAndReadFile) {
    std::ofstream test_file("test_nuskaityti.txt");
    test_file << "Vardas Pavarde ND1 ND2 ND3 Egzaminas\n";
    test_file << "Jonas Jonaitis 8 9 7 8\n";
    test_file << "Ona Onaite 10 9 8 9\n";
    test_file.close();
    
    auto studentai = nuskaityti("test_nuskaityti.txt");
    EXPECT_EQ(studentai.size(), 2);
    
    std::remove("test_nuskaityti.txt");
}


TEST(FileGenerationTest, GenerateFile) {
    generuoti_faila(5, "test_generated.txt", 3);
    
    std::ifstream test_file("test_generated.txt");
    EXPECT_TRUE(test_file.good());
    
    std::string line;
    std::getline(test_file, line);
    EXPECT_TRUE(line.find("Vardas") != std::string::npos);
    EXPECT_TRUE(line.find("Pavarde") != std::string::npos);
    
    test_file.close();
    std::remove("test_generated.txt");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    
    std::cout << "Studentų Rūšiavimo Sistemos Testai\n";
    std::cout << "Versija 2.0\n";
    
    int result = RUN_ALL_TESTS();
    std::cout << "Testai baigti. Rezultatas: "
              << (result == 0 ? "Visi testau pavyko" : "Kai kurie testai nepavyko")
              << "\n";
    
    return result;
}
