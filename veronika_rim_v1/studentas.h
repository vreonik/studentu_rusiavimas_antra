#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <iomanip>


#ifdef DEBUG_MODE
    #define DEBUG_LOG(msg) std::cout << msg << "\n"
#else
    #define DEBUG_LOG(msg)
#endif

class Studentas {
private:
    std::string vardas_;
    std::string pavarde_;
    std::vector<int> nd_;
    int egzas_;
    
    // Cache reikšmės
    mutable double galutinis_vid_ = -1.0;
    mutable double galutinis_med_ = -1.0;

public:
    //Konstruktoriai
    Studentas();
    Studentas(const std::string& vardas, const std::string& pavarde);
    Studentas(const std::string& vardas, const std::string& pavarde,
              const std::vector<int>& nd, int egzas);
    
    //Rule of five!
    Studentas(const Studentas& other);
    Studentas(Studentas&& other) noexcept;
    Studentas& operator=(const Studentas& other);
    Studentas& operator=(Studentas&& other) noexcept;
    ~Studentas();

    //Getteriai
    inline std::string getVardas() const { return vardas_; }
    inline std::string getPavarde() const { return pavarde_; }
    inline std::vector<int> getNd() const { return nd_; }
    inline int getEgzas() const { return egzas_; }

    //Setteriai
    inline void setVardas(const std::string& vardas) {
        vardas_ = vardas;
        galutinis_vid_ = -1.0;
        galutinis_med_ = -1.0;
    }
    inline void setPavarde(const std::string& pavarde) {
        pavarde_ = pavarde;
    }
    inline void setNd(const std::vector<int>& nd) {
        nd_ = nd;
        galutinis_vid_ = -1.0;
        galutinis_med_ = -1.0;
    }
    inline void setEgzas(int egzas) {
        egzas_ = egzas;
        galutinis_vid_ = -1.0;
        galutinis_med_ = -1.0;
    }

    //metodai
    double skaiciuotiVidurki() const;
    double skaiciuotiMediana() const;
    std::pair<double, double> skaiciuotiGalutinius() const;
    
    // Optimizuoti metodai su caching
    double gautiGalutiniVidurki() const;
    double gautiGalutiniMediana() const;

    //operatoriai
    bool operator<(const Studentas& other) const;
    bool operator>(const Studentas& other) const;
    bool operator==(const Studentas& other) const;
    bool operator!=(const Studentas& other) const;

    friend std::istream& operator>>(std::istream& is, Studentas& studentas);
    friend std::ostream& operator<<(std::ostream& os, const Studentas& studentas);

    //papildomi metodai
    void isvalytiDuomenis();
    void generuotiPazymius(int nd_kiekis);
    void spausdintiInformacija() const;
};

//papildomos funkcijos
void demonstruotiRuleOfThree();
void demonstruotiIOMetodus();
void demonstruotiVisusRežimus();
void demonstruotiRankiniĮvedimą();
void demonstruotiAutomatiniGeneravimą();
void demonstruotiĮvestįIšFailo();
void demonstruotiIšvestįĮFailą();
void paleistiVisusRežimus();
