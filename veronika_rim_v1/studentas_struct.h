#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

struct StudentasStruct {
    std::string vardas;
    std::string pavarde;
    std::vector<int> nd;
    int egzas;

    double skaiciuotiVidurki() const;
    double skaiciuotiMediana() const;
    std::pair<double, double> skaiciuotiGalutinius() const;
};

std::istream& operator>>(std::istream& is, StudentasStruct& studentas);
std::ostream& operator<<(std::ostream& os, const StudentasStruct& studentas);
