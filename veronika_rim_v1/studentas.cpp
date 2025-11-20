#include "studentas.h"
#include <algorithm>
#include <numeric>
#include <sstream>


Studentas::Studentas() : vardas_(""), pavarde_(""), egzas_(0) {}

// Konstruktorius su vardu ir pavarde
Studentas::Studentas(const std::string& vardas, const std::string& pavarde)
    : vardas_(vardas), pavarde_(pavarde), egzas_(0) {}

// Pilnas konstruktorius
Studentas::Studentas(const std::string& vardas, const std::string& pavarde,
                     const std::vector<int>& nd, int egzas)
    : vardas_(vardas), pavarde_(pavarde), nd_(nd), egzas_(egzas) {}

// Copy konstruktorius
Studentas::Studentas(const Studentas& other)
    : vardas_(other.vardas_), pavarde_(other.pavarde_),
      nd_(other.nd_), egzas_(other.egzas_) {}

// Move konstruktorius
Studentas::Studentas(Studentas&& other) noexcept
    : vardas_(std::move(other.vardas_)),
      pavarde_(std::move(other.pavarde_)),
      nd_(std::move(other.nd_)),
      egzas_(other.egzas_) {
    other.egzas_ = 0;
}

// Copy assignment operator
Studentas& Studentas::operator=(const Studentas& other) {
    if (this != &other) {
        vardas_ = other.vardas_;
        pavarde_ = other.pavarde_;
        nd_ = other.nd_;
        egzas_ = other.egzas_;
    }
    return *this;
}

// Move assignment operator
Studentas& Studentas::operator=(Studentas&& other) noexcept {
    if (this != &other) {
        vardas_ = std::move(other.vardas_);
        pavarde_ = std::move(other.pavarde_);
        nd_ = std::move(other.nd_);
        egzas_ = other.egzas_;
        other.egzas_ = 0;
    }
    return *this;
}

// Destruktorius
Studentas::~Studentas() {
}

// Metodai
double Studentas::skaiciuotiVidurki() const {
    if(nd_.empty()) return 0;
    double sum = std::accumulate(nd_.begin(), nd_.end(), 0.0);
    return sum / nd_.size();
}

double Studentas::skaiciuotiMediana() const {
    if(nd_.empty()) return 0;
    std::vector<int> temp_nd = nd_;
    std::sort(temp_nd.begin(), temp_nd.end());
    size_t size = temp_nd.size();
    if(size % 2 == 0)
        return (temp_nd[size/2 - 1] + temp_nd[size/2]) / 2.0;
    else
        return temp_nd[size/2];
}

std::pair<double, double> Studentas::skaiciuotiGalutinius() const {
    double vidurkis = skaiciuotiVidurki();
    double mediana = skaiciuotiMediana();
    double galutinis_vid = 0.4 * vidurkis + 0.6 * egzas_;
    double galutinis_med = 0.4 * mediana + 0.6 * egzas_;
    return {galutinis_vid, galutinis_med};
}

// Operatoriai
bool Studentas::operator<(const Studentas& other) const {
    auto [vid1, med1] = skaiciuotiGalutinius();
    auto [vid2, med2] = other.skaiciuotiGalutinius();
    return vid1 < vid2;
}

bool Studentas::operator>(const Studentas& other) const {
    auto [vid1, med1] = skaiciuotiGalutinius();
    auto [vid2, med2] = other.skaiciuotiGalutinius();
    return vid1 > vid2;
}

// Friend funkcijos
std::istream& operator>>(std::istream& is, Studentas& studentas) {
    is >> studentas.vardas_ >> studentas.pavarde_;
    
    studentas.nd_.clear();
    int pazymys;
    while (is >> pazymys) {
        studentas.nd_.push_back(pazymys);
    }
    is.clear();
    
    if (!studentas.nd_.empty()) {
        studentas.egzas_ = studentas.nd_.back();
        studentas.nd_.pop_back();
    }
    
    return is;
}

std::ostream& operator<<(std::ostream& os, const Studentas& studentas) {
    os << studentas.vardas_ << " " << studentas.pavarde_;
    for (int pazymys : studentas.nd_) {
        os << " " << pazymys;
    }
    os << " " << studentas.egzas_;
    return os;
}
