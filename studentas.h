    /**
     * @file studentas.h
     * @brief Studentas klasės deklaracija
     * @author Veronika
     * @version 2.0
     * @date 2025
     */

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

    /**
     * @class Studentas
     * @brief Studentų duomenų klasė, paveldi iš Zmogus
     *
     * Ši klasė saugo studento duomenis ir atlieka skaičiavimus.
     * Įgyvendina Rule of Five principą.
     */
    class Studentas : public Zmogus {
    private:
        std::vector<int> nd_;
        int egzas_;
        
        /// @brief Cache reikšmė galutiniam vidurkiui
        mutable double galutinis_vid_ = -1.0;
        /// @brief Cache reikšmė galutinei medianai
        mutable double galutinis_med_ = -1.0;

    public:
        //Konstruktoriai
        /// @brief Default konstruktorius
        Studentas();
        /// @brief Parametrizuotas konstruktorius
        Studentas(const std::string& vardas, const std::string& pavarde);
        /// @brief Pilnas konstruktorius
        Studentas(const std::string& vardas, const std::string& pavarde,
                  const std::vector<int>& nd, int egzas);
        
        //Rule of five!
        /// @brief Kopijavimo konstruktorius
        Studentas(const Studentas& other);
        /// @brief Perkėlimo konstruktorius
        Studentas(Studentas&& other) noexcept;
        /// @brief Kopijavimo priskyrimo operatorius
        Studentas& operator=(const Studentas& other);
        /// @brief Perkėlimo priskyrimo operatorius
        Studentas& operator=(Studentas&& other) noexcept;
        /// @brief Destruktorius
        ~Studentas();

        //Getter'iai - paveldimi iš Zmogus
        using Zmogus::getVardas;
        using Zmogus::getPavarde;
        
        /// @brief Gauti namų darbų pažymius
        inline std::vector<int> getNd() const { return nd_; }
        /// @brief Gauti egzamino pažymį
        inline int getEgzas() const { return egzas_; }

        //Setter'iai
        using Zmogus::setVardas;
        using Zmogus::setPavarde;
        
        /// @brief Nustatyti namų darbų pažymius
        inline void setNd(const std::vector<int>& nd) {
            nd_ = nd;
            galutinis_vid_ = -1.0;
            galutinis_med_ = -1.0;
        }
        /// @brief Nustatyti egzamino pažymį
        inline void setEgzas(int egzas) {
            egzas_ = egzas;
            galutinis_vid_ = -1.0;
            galutinis_med_ = -1.0;
        }

        /// @brief Spausdinti informaciją apie studentą (abstraktaus metodo implementacija)
        void spausdintiInformacija() const override;

        //Skaiciavimo metodai
        /// @brief Apskaičiuoti namų darbų vidurkį
        double skaiciuotiVidurki() const;
        /// @brief Apskaičiuoti namų darbų medianą
        double skaiciuotiMediana() const;
        /// @brief Apskaičiuoti galutinius pažymius (vidurkį ir medianą)
        std::pair<double, double> skaiciuotiGalutinius() const;
        
        // Optimizuoti metodai su caching
        /// @brief Gauti galutinį pažymį pagal vidurkį (su caching)
        double gautiGalutiniVidurki() const;
        /// @brief Gauti galutinį pažymį pagal medianą (su caching)
        double gautiGalutiniMediana() const;

        //operatoriai
        /// @brief Palyginimo operatorius "<" (pagal galutinį pažymį)
        bool operator<(const Studentas& other) const;
        /// @brief Palyginimo operatorius ">" (pagal galutinį pažymį)
        bool operator>(const Studentas& other) const;
        /// @brief Lygybės operatorius
        bool operator==(const Studentas& other) const;
        /// @brief Nelygybės operatorius
        bool operator!=(const Studentas& other) const;

        /// @brief Įvesties operatorius
        friend std::istream& operator>>(std::istream& is, Studentas& studentas);
        /// @brief Išvesties operatorius
        friend std::ostream& operator<<(std::ostream& os, const Studentas& studentas);

        /// @brief Išvalyti studento duomenis
        void isvalytiDuomenis() override;
        /// @brief Sugeneruoti atsitiktinius pažymius
        void generuotiPazymius(int nd_kiekis);
    };

    //papildomos funkcijos
    /// @brief Demonstruoti Rule of Three/Five principą
    void demonstruotiRuleOfThree();
    /// @brief Demonstruoti abstrakčios klasės naudojimą
    void demonstruotiAbstrakciaKlase();
    /// @brief Demonstruoti visus režimus
    void demonstruotiVisusRežimus();
    /// @brief Demonstruoti rankinį įvedimą
    void demonstruotiRankiniĮvedimą();
    /// @brief Demonstruoti automatinį generavimą
    void demonstruotiAutomatiniGeneravimą();
    /// @brief Demonstruoti įvestį iš failo
    void demonstruotiĮvestįIšFailo();
    /// @brief Demonstruoti išvestį į failą
    void demonstruotiIšvestįĮFailą();
    /// @brief Paleisti visus režimus iš eilės
    void paleistiVisusRežimus();
