#pragma once
#include <string>
#include <iostream>

class Zmogus {
protected:
    std::string vardas_;
    std::string pavarde_;

public:
    virtual void spausdintiInformacija() const = 0;
    virtual ~Zmogus() = default;

    Zmogus() : vardas_(""), pavarde_("") {}
    Zmogus(const std::string& vardas, const std::string& pavarde)
        : vardas_(vardas), pavarde_(pavarde) {}
    
    std::string getVardas() const { return vardas_; }
    std::string getPavarde() const { return pavarde_; }

    void setVardas(const std::string& vardas) { vardas_ = vardas; }
    void setPavarde(const std::string& pavarde) { pavarde_ = pavarde; }

    virtual void isvalytiDuomenis() {
        vardas_.clear();
        pavarde_.clear();
    }
};
