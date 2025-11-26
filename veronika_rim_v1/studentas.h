#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include "zmogus.h"

#ifdef DEBUG_MODE
    #define DEBUG_LOG(msg) std::cout << msg << "\n"
#else
    #define DEBUG_LOG(msg)
#endif

class Studentas : public Zmogus {
private:
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

    //Getter'iai - paveldimi iš Zmogus
    using Zmogus::getVardas;
    using Zmogus::getPavarde;
    
    inline std::vector<int> getNd() const { return nd_; }
    inline int getEgzas() const { return egzas_; }

    //Setter'iai
    using Zmogus::setVardas;
    using Zmogus::setPavarde;
    
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

    void spausdintiInformacija() const override;

    //Skaiciavimo metodai
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

    void isvalytiDuomenis() override;
    void generuotiPazymius(int nd_kiekis);
};

//papildomos funkcijos
void demonstruotiRuleOfThree();
void demonstruotiAbstrakciaKlase();
void demonstruotiVisusRežimus();
void demonstruotiRankiniĮvedimą();
void demonstruotiAutomatiniGeneravimą();
void demonstruotiĮvestįIšFailo();
void demonstruotiIšvestįĮFailą();
void paleistiVisusRežimus();
