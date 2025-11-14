#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

class Studentas {
private:
    std::string vardas_;
    std::string pavarde_;
    std::vector<int> nd_;
    int egzas_;

public:
    Studentas();
    Studentas(const std::string& vardas, const std::string& pavarde);
    Studentas(const std::string& vardas, const std::string& pavarde,
              const std::vector<int>& nd, int egzas);
    
    //Rule of Five
    Studentas(const Studentas& other);
    Studentas(Studentas&& other) noexcept;
    Studentas& operator=(const Studentas& other);
    Studentas& operator=(Studentas&& other) noexcept;
    ~Studentas();

    //Getter'iai
    std::string getVardas() const { return vardas_; }
    std::string getPavarde() const { return pavarde_; }
    std::vector<int> getNd() const { return nd_; }
    int getEgzas() const { return egzas_; }

    //Setter'iai
    void setVardas(const std::string& vardas) { vardas_ = vardas; }
    void setPavarde(const std::string& pavarde) { pavarde_ = pavarde; }
    void setNd(const std::vector<int>& nd) { nd_ = nd; }
    void setEgzas(int egzas) { egzas_ = egzas; }

    double skaiciuotiVidurki() const;
    double skaiciuotiMediana() const;
    std::pair<double, double> skaiciuotiGalutinius() const;

    bool operator<(const Studentas& other) const;
    bool operator>(const Studentas& other) const;

    friend std::istream& operator>>(std::istream& is, Studentas& studentas);
    friend std::ostream& operator<<(std::ostream& os, const Studentas& studentas);
};
