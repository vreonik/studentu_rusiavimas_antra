#include "studentas.h"
#include <algorithm>
#include <numeric>
#include <sstream>
#include <random>
#include <limits>

//Konstruktoriai
Studentas::Studentas() : vardas_(""), pavarde_(""), egzas_(0) {
    std::cout << "Iškviestas default konstruktorius (" << this << ")\n";
}

Studentas::Studentas(const std::string& vardas, const std::string& pavarde)
    : vardas_(vardas), pavarde_(pavarde), egzas_(0) {
    std::cout << "Iškviestas parametrizuotas konstruktorius (" << this << ")\n";
}

Studentas::Studentas(const std::string& vardas, const std::string& pavarde,
                     const std::vector<int>& nd, int egzas)
    : vardas_(vardas), pavarde_(pavarde), nd_(nd), egzas_(egzas) {
    std::cout << "Iškviestas pilnas konstruktorius (" << this << ")\n";
}

// === RULE OF FIVE ===
Studentas::Studentas(const Studentas& other)
    : vardas_(other.vardas_), pavarde_(other.pavarde_),
      nd_(other.nd_), egzas_(other.egzas_) {
    std::cout << "Iškviestas COPY konstruktorius (" << this << " iš " << &other << ")\n";
}

Studentas::Studentas(Studentas&& other) noexcept
    : vardas_(std::move(other.vardas_)),
      pavarde_(std::move(other.pavarde_)),
      nd_(std::move(other.nd_)),
      egzas_(other.egzas_) {
    other.egzas_ = 0;
    std::cout << "Iškviestas MOVE konstruktorius (" << this << " iš " << &other << ")\n";
}

Studentas& Studentas::operator=(const Studentas& other) {
    if (this != &other) {
        std::cout << "Iškviestas COPY assignment (" << this << " = " << &other << ")\n";
        vardas_ = other.vardas_;
        pavarde_ = other.pavarde_;
        nd_ = other.nd_;
        egzas_ = other.egzas_;
    }
    return *this;
}

Studentas& Studentas::operator=(Studentas&& other) noexcept {
    if (this != &other) {
        std::cout << "Iškviestas MOVE assignment (" << this << " = " << &other << ")\n";
        vardas_ = std::move(other.vardas_);
        pavarde_ = std::move(other.pavarde_);
        nd_ = std::move(other.nd_);
        egzas_ = other.egzas_;
        other.egzas_ = 0;
    }
    return *this;
}

Studentas::~Studentas() {
    std::cout << "Iškviestas destruktorius (" << this << ")\n";
}

//Skaiciavimo metodai
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

//Operatoriai
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

bool Studentas::operator==(const Studentas& other) const {
    return vardas_ == other.vardas_ && pavarde_ == other.pavarde_;
}

bool Studentas::operator!=(const Studentas& other) const {
    return !(*this == other);
}

//i/o operatoriai
std::istream& operator>>(std::istream& is, Studentas& studentas) {
    std::cout << "=== STUDENTO DUOMENŲ ĮVEDIMAS ===\n";
    
    std::cout << "Vardas: ";
    is >> studentas.vardas_;
    
    std::cout << "Pavardė: ";
    is >> studentas.pavarde_;
    
    studentas.nd_.clear();
    std::cout << "Įveskite ND pažymius (baigti su 0): ";
    int pazymys;
    while (is >> pazymys && pazymys != 0) {
        if (pazymys >= 1 && pazymys <= 10) {
            studentas.nd_.push_back(pazymys);
            std::cout << "Įvestas: " << pazymys << " (kitas arba 0 baigti): ";
        } else {
            std::cout << "Netinkamas pažymys! Turi būti 1-10. Bandykite dar kartą: ";
        }
    }
    is.clear();
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "Egzamino pažymys: ";
    while (!(is >> studentas.egzas_) || studentas.egzas_ < 1 || studentas.egzas_ > 10) {
        std::cout << "Netinkamas pažymys! Turi būti 1-10. Bandykite dar kartą: ";
        is.clear();
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    std::cout << "Studento duomenys sėkmingai įvesti!\n";
    return is;
}

std::ostream& operator<<(std::ostream& os, const Studentas& studentas) {
    auto [vid, med] = studentas.skaiciuotiGalutinius();
    
    os << "STUDENTO INFORMACIJA:\n"
       << "────────────────────────\n"
       << "Vardas:    " << studentas.vardas_ << "\n"
       << "Pavardė:   " << studentas.pavarde_ << "\n"
       << "ND:        [";
    
    for (size_t i = 0; i < studentas.nd_.size(); ++i) {
        os << studentas.nd_[i];
        if (i < studentas.nd_.size() - 1) os << ", ";
    }
    
    os << "]\n"
       << "Egzaminas: " << studentas.egzas_ << "\n"
       << "Galutinis: " << std::fixed << std::setprecision(2) << vid << " (vid.) / "
       << med << " (med.)\n"
       << "Adresas:   " << &studentas << "\n"
       << "────────────────────────";
    
    return os;
}

//papildomi metodai
void Studentas::isvalytiDuomenis() {
    vardas_.clear();
    pavarde_.clear();
    nd_.clear();
    egzas_ = 0;
    std::cout << "Studento duomenys išvalyti (" << this << ")\n";
}

void Studentas::generuotiPazymius(int nd_kiekis) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 10);
    
    nd_.clear();
    for (int i = 0; i < nd_kiekis; ++i) {
        nd_.push_back(dist(gen));
    }
    egzas_ = dist(gen);
    
    std::cout << "Sugeneruoti " << nd_kiekis << " ND ir egzamino pažymiai (" << this << ")\n";
}

void Studentas::spausdintiInformacija() const {
    std::cout << *this << "\n";
}

//tam kad demonstruoti, bet istiesu tai demonstruoji rule of five nes geresne
void demonstruotiRuleOfThree() {
    std::cout << "\n ===== RULE OF THREE/FIVE DEMONSTRAVIMAS =====\n\n";
    
    std::cout << "1. SUKURIAMAS ORIGINALUS STUDENTAS:\n";
    Studentas s1("Jonas", "Jonaitis");
    std::vector<int> nd = {8, 9, 7, 10};
    s1.setNd(nd);
    s1.setEgzas(8);
    std::cout << s1 << "\n\n";
    
    std::cout << "2. COPY KONSTRUKTORIUS (s1 ->s2):\n";
    Studentas s2 = s1;
    std::cout << s2 << "\n\n";
    
    std::cout << "3. COPY ASSIGNMENT (s2 -> s3):\n";
    Studentas s3;
    s3 = s2;
    std::cout << s3 << "\n\n";
    
    std::cout << "4.  MOVE KONSTRUKTORIUS (s1 -> s4):\n";
    Studentas s4 = std::move(s1);
    std::cout << s4 << "\n\n";
    
    std::cout << "5. MOVE ASSIGNMENT (s4 -> s5):\n";
    Studentas s5;
    s5 = std::move(s4);
    std::cout << s5 << "\n\n";
    
    std::cout << "6. PALYGINIMO OPERATORIAI:\n";
    std::cout << "s2 == s3: " << (s2 == s3 ? "TAIP" : "NE") << "\n";
    std::cout << "s2 != s5: " << (s2 != s5 ? "TAIP" : "NE") << "\n";
    std::cout << "s2 < s5:  " << (s2 < s5 ? "TAIP" : "NE") << "\n\n";
    
    std::cout << " RULE OF THREE/FIVE DEMONSTRAVIMAS BAIGTAS!\n";
}

void demonstruotiIOMetodus() {
    std::cout << "\n ===== I/O OPERATORIŲ DEMONSTRAVIMAS =====\n\n";
    
    std::cout << "1. RANKINIS ĮVEDIMAS:\n";
    Studentas s1;
    std::cin >> s1;
    std::cout << "\n" << s1 << "\n\n";
    
    std::cout << "2. AUTOMATINIS GENERAVIMAS:\n";
    Studentas s2("Ona", "Onaite");
    s2.generuotiPazymius(5);
    std::cout << s2 << "\n\n";
    
    std::cout << "3. ĮVESTIS IŠ FAILO (SIMULIACIJA):\n";
    Studentas s3("Petras", "Petraitis");
    std::vector<int> failo_nd = {6, 7, 8, 9, 10};
    s3.setNd(failo_nd);
    s3.setEgzas(8);
    std::cout << s3 << "\n\n";
    
    std::cout << "4. IŠVESTIS Į FAILĄ (SIMULIACIJA):\n";
    std::cout << "Studentas būtų išvestas į failą:\n";
    std::cout << s3 << "\n\n";
    
    std::cout << " I/O OPERATORIŲ DEMONSTRAVIMAS BAIGTAS!\n";
}
