#include <gtest/gtest.h>
#include "studentas.h"
#include "studentas_struct.h"
#include "strategijos.h"
#include <vector>
#include <list>

// Studentas klasės testai
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
    EXPECT_TRUE(s1 == s2);
}

TEST(StudentasTest, MoveConstructor) {
    std::vector<int> nd = {7, 8, 9};
    Studentas s1("Testas", "Testavimas", nd, 10);
    Studentas s2 = std::move(s1);
    
    EXPECT_EQ(s2.getVardas(), "Testas");
    EXPECT_EQ(s2.getPavarde(), "Testavimas");
    EXPECT_EQ(s2.getNd().size(), 3);
    EXPECT_EQ(s2.getEgzas(), 10);
    
    EXPECT_TRUE(s1.getVardas().empty());
    EXPECT_TRUE(s1.getPavarde().empty());
    EXPECT_TRUE(s1.getNd().empty());
    EXPECT_EQ(s1.getEgzas(), 0);
}

TEST(StudentasTest, AverageCalculation) {
    std::vector<int> nd = {8, 9, 7};
    Studentas s("Vardenis", "Pavardenis", nd, 8);
    
    double expected_avg = (8 + 9 + 7) / 3.0;
    double expected_final = 0.4 * expected_avg + 0.6 * 8;
    
    EXPECT_NEAR(s.skaiciuotiVidurki(), expected_avg, 0.001);
    
    auto [vid, med] = s.skaiciuotiGalutinius();
    EXPECT_NEAR(vid, expected_final, 0.001);
}

TEST(StudentasTest, MedianCalculation) {
    std::vector<int> nd = {8, 10, 7, 9, 6};
    Studentas s("Test", "User", nd, 8);
    
    double expected_median = 8.0;
    double expected_final = 0.4 * expected_median + 0.6 * 8;
    
    auto [vid, med] = s.skaiciuotiGalutinius();
    EXPECT_NEAR(med, expected_final, 0.001);
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

// StudentasStruct testai
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

// Strategijų testai
TEST(StrategijosTest, Strategija1Vector) {
    std::vector<Studentas> visi = {
        Studentas("A", "A", {8, 9}, 8),
        Studentas("B", "B", {5, 6}, 5),
        Studentas("C", "C", {10, 10}, 10),
        Studentas("D", "D", {4, 4}, 4)
    };
    
    std::vector<Studentas> vargsiukai, kietakiai;
    TestoRezultatai rez = strategija_1(visi, vargsiukai, kietakiai, 'v');
    
    EXPECT_EQ(vargsiukai.size(), 1);
    EXPECT_EQ(kietakiai.size(), 3);
}

TEST(StrategijosTest, Strategija2Vector) {
    std::vector<Studentas> visi = {
        Studentas("A", "A", {8, 9}, 8),
        Studentas("B", "B", {5, 6}, 5),
        Studentas("C", "C", {10, 10}, 10),
        Studentas("D", "D", {4, 4}, 4)
    };
    
    std::vector<Studentas> vargsiukai;
    TestoRezultatai rez = strategija_2(visi, vargsiukai, 'v');
    
    EXPECT_EQ(vargsiukai.size(), 1);
    EXPECT_EQ(visi.size(), 3);
}

// Templatinių funkcijų testai
TEST(TemplateTest, Strategy1WorksWithBothContainers) {
    // Testuojame su vector
    {
        std::vector<Studentas> visi = {
            Studentas("A", "A", {8, 9}, 8),
            Studentas("B", "B", {4, 4}, 4)
        };
        std::vector<Studentas> vargsiukai, kietakiai;
        TestoRezultatai rez = strategija_1(visi, vargsiukai, kietakiai, 'v');
        EXPECT_GE(rez.skirstymo_laikas, 0);
    }
    
    // Testuojame su list
    {
        std::list<Studentas> visi = {
            Studentas("A", "A", {8, 9}, 8),
            Studentas("B", "B", {4, 4}, 4)
        };
        std::list<Studentas> vargsiukai, kietakiai;
        TestoRezultatai rez = strategija_1(visi, vargsiukai, kietakiai, 'v');
        EXPECT_GE(rez.skirstymo_laikas, 0);
    }
}

TEST(EdgeCaseTest, EmptyStudentList) {
    std::vector<Studentas> visi;
    std::vector<Studentas> vargsiukai, kietakiai;
    
    TestoRezultatai rez = strategija_1(visi, vargsiukai, kietakiai, 'v');
    
    EXPECT_EQ(vargsiukai.size(), 0);
    EXPECT_EQ(kietakiai.size(), 0);
    EXPECT_GE(rez.skirstymo_laikas, 0);
}

TEST(EdgeCaseTest, AllStudentsFail) {
    std::vector<Studentas> visi = {
        Studentas("A", "A", {4, 4}, 4),
        Studentas("B", "B", {3, 3}, 3),
        Studentas("C", "C", {2, 2}, 2)
    };
    
    std::vector<Studentas> vargsiukai, kietakiai;
    TestoRezultatai rez = strategija_1(visi, vargsiukai, kietakiai, 'v');
    
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
    TestoRezultatai rez = strategija_1(visi, vargsiukai, kietakiai, 'v');
    
    EXPECT_EQ(vargsiukai.size(), 0);
    EXPECT_EQ(kietakiai.size(), 3);
}

TEST(PerformanceTest, MemoryUsageCalculation) {
    Studentas s("Testas", "Testavimas", {8, 9, 7, 6, 5}, 8);
    
    std::vector<Studentas> visi(1000, s);
    std::vector<Studentas> vargsiukai, kietakiai;
    
    TestoRezultatai rez = strategija_1(visi, vargsiukai, kietakiai, 'v');
    
    EXPECT_GT(rez.atmintis_bendra, 0);
    EXPECT_GT(rez.atmintis_vargsiukai, 0);
    EXPECT_GT(rez.atmintis_kietakiai, 0);
}

// Streaming operatorių testai
TEST(IOTest, InputOperator) {
    std::istringstream input("Jonas Jonaitis 8 9 7 0 8");
    Studentas s;
    input >> s;
    
    EXPECT_EQ(s.getVardas(), "Jonas");
    EXPECT_EQ(s.getPavarde(), "Jonaitis");
    EXPECT_EQ(s.getNd().size(), 3);
    EXPECT_EQ(s.getEgzas(), 8);
}

TEST(IOTest, OutputOperator) {
    Studentas s("Ona", "Onaite", {9, 10, 8}, 9);
    std::ostringstream output;
    output << s;
    
    std::string result = output.str();
    EXPECT_TRUE(result.find("Ona") != std::string::npos);
    EXPECT_TRUE(result.find("Onaite") != std::string::npos);
    EXPECT_TRUE(result.find("9.00") != std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
