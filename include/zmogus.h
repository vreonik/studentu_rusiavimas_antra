    /**
     * @file zmogus.h
     * @brief Abstrakčios bazinės klasės Zmogus deklaracija
     *
     * Ši klasė yra abstrakti bazinė klasė, iš kurios paveldi Studentas klasė.
     */

    #pragma once
    #include <string>
    #include <iostream>

    /**
     * @class Zmogus
     * @brief Abstrakti bazinė klasė žmogaus duomenims
     */
    class Zmogus {
    protected:
        std::string vardas_;  ///< Vardas
        std::string pavarde_; ///< Pavardė

    public:
        //Abstraktus metodai
        /**
         * @brief Abstraktus metodas informacijos spausdinimui
         */
        virtual void spausdintiInformacija() const = 0;
        
        /**
         * @brief Virtualus destruktorius
         */
        virtual ~Zmogus() = default;

        //Konstruktoriai
        /**
         * @brief Default konstruktorius
         */
        Zmogus() : vardas_(""), pavarde_("") {}
        
        /**
         * @brief Parametrizuotas konstruktorius
         * @param vardas Vardas
         * @param pavarde Pavardė
         */
        Zmogus(const std::string& vardas, const std::string& pavarde)
            : vardas_(vardas), pavarde_(pavarde) {}
        
        //Getter'iai
        /**
         * @brief Gauti vardą
         * @return Vardas
         */
        std::string getVardas() const { return vardas_; }
        
        /**
         * @brief Gauti pavardę
         * @return Pavardė
         */
        std::string getPavarde() const { return pavarde_; }

        //Setter'iai
        /**
         * @brief Nustatyti vardą
         * @param vardas Vardas
         */
        void setVardas(const std::string& vardas) { vardas_ = vardas; }
        
        /**
         * @brief Nustatyti pavardę
         * @param pavarde Pavardė
         */
        void setPavarde(const std::string& pavarde) { pavarde_ = pavarde; }

        /**
         * @brief Išvalyti duomenis
         */
        virtual void isvalytiDuomenis() {
            vardas_.clear();
            pavarde_.clear();
        }
    };
