#include "studentas.h"
#include <algorithm>
#include <numeric>
#include <sstream>
#include <random>
#include <limits>
#include <fstream>

//Konstruktoriai
Studentas::Studentas() : vardas_(""), pavarde_(""), egzas_(0) {
    DEBUG_LOG("Iškviestas default konstruktorius (" << this << ")");
}

Studentas::Studentas(const std::string& vardas, const std::string& pavarde)
    : vardas_(vardas), pavarde_(pavarde), egzas_(0) {
    DEBUG_LOG("Iškviestas parametrizuotas konstruktorius (" << this << ")");
}

Studentas::Studentas(const std::string& vardas, const std::string& pavarde,
                     const std::vector<int>& nd, int egzas)
    : vardas_(vardas), pavarde_(pavarde), nd_(nd), egzas_(egzas) {
    DEBUG_LOG("Iškviestas pilnas konstruktorius (" << this << ")");
}

//Rule of five
Studentas::Studentas(const Studentas& other)
    : vardas_(other.vardas_), pavarde_(other.pavarde_),
      nd_(other.nd_), egzas_(other.egzas_),
      galutinis_vid_(other.galutinis_vid_),
      galutinis_med_(other.galutinis_med_) {
    DEBUG_LOG("Iškviestas COPY konstruktorius (" << this << " iš " << &other << ")");
}

Studentas::Studentas(Studentas&& other) noexcept
    : vardas_(std::move(other.vardas_)),
      pavarde_(std::move(other.pavarde_)),
      nd_(std::move(other.nd_)),
      egzas_(other.egzas_),
      galutinis_vid_(other.galutinis_vid_),
      galutinis_med_(other.galutinis_med_) {
    other.egzas_ = 0;
    other.galutinis_vid_ = -1.0;
    other.galutinis_med_ = -1.0;
    other.vardas_.clear();
    other.pavarde_.clear();
    DEBUG_LOG("Iškviestas MOVE konstruktorius (" << this << " iš " << &other << ")");
}

Studentas& Studentas::operator=(const Studentas& other) {
    if (this != &other) {
        DEBUG_LOG("Iškviestas COPY assignment (" << this << " = " << &other << ")");
        vardas_ = other.vardas_;
        pavarde_ = other.pavarde_;
        nd_ = other.nd_;
        egzas_ = other.egzas_;
        galutinis_vid_ = other.galutinis_vid_;
        galutinis_med_ = other.galutinis_med_;
    }
    return *this;
}

Studentas& Studentas::operator=(Studentas&& other) noexcept {
    if (this != &other) {
        DEBUG_LOG("Iškviestas MOVE assignment (" << this << " = " << &other << ")");
        vardas_ = std::move(other.vardas_);
        pavarde_ = std::move(other.pavarde_);
        nd_ = std::move(other.nd_);
        egzas_ = other.egzas_;
        galutinis_vid_ = other.galutinis_vid_;
        galutinis_med_ = other.galutinis_med_;
        
        other.egzas_ = 0;
        other.galutinis_vid_ = -1.0;
        other.galutinis_med_ = -1.0;
        other.vardas_.clear();
        other.pavarde_.clear();
    }
    return *this;
}

Studentas::~Studentas() {
    DEBUG_LOG("Iškviestas destruktorius (" << this << ")");
}

//Skaiciavimo metodai
double Studentas::skaiciuotiVidurki() const {
    if(nd_.empty()) return 0.0;
    double sum = std::accumulate(nd_.begin(), nd_.end(), 0.0);
    return sum / nd_.size();
}

double Studentas::skaiciuotiMediana() const {
    if(nd_.empty()) return 0.0;
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

//caching metodai, optimizuojame ofc!
double Studentas::gautiGalutiniVidurki() const {
    if (galutinis_vid_ < 0) {
        double vidurkis = skaiciuotiVidurki();
        galutinis_vid_ = 0.4 * vidurkis + 0.6 * egzas_;
    }
    return galutinis_vid_;
}

double Studentas::gautiGalutiniMediana() const {
    if (galutinis_med_ < 0) {
        double mediana = skaiciuotiMediana();
        galutinis_med_ = 0.4 * mediana + 0.6 * egzas_;
    }
    return galutinis_med_;
}

//Operatoriai
bool Studentas::operator<(const Studentas& other) const {
    return gautiGalutiniVidurki() < other.gautiGalutiniVidurki();
}

bool Studentas::operator>(const Studentas& other) const {
    return gautiGalutiniVidurki() > other.gautiGalutiniVidurki();
}

bool Studentas::operator==(const Studentas& other) const {
    return vardas_ == other.vardas_ &&
           pavarde_ == other.pavarde_ &&
           egzas_ == other.egzas_ &&
           nd_ == other.nd_;
}

bool Studentas::operator!=(const Studentas& other) const {
    return !(*this == other);
}

//i/o operatoriai
std::istream& operator>>(std::istream& is, Studentas& studentas) {
    if (&is == &std::cin) {
        std::cout << "=== STUDENTO DUOMENŲ ĮVEDIMAS ===\n";
        std::cout << "Vardas: ";
    }
    
    is >> studentas.vardas_;
    
    if (&is == &std::cin) {
        std::cout << "Pavardė: ";
    }
    is >> studentas.pavarde_;
    
    studentas.nd_.clear();
    studentas.galutinis_vid_ = -1.0; //Reset cache
    studentas.galutinis_med_ = -1.0;
    
    if (&is == &std::cin) {
        std::cout << "Įveskite ND pažymius (baigti su 0): ";
    }
    
    int pazymys;
    while (is >> pazymys) {
        if (pazymys == 0) break;
        if (pazymys >= 1 && pazymys <= 10) {
            studentas.nd_.push_back(pazymys);
            if (&is == &std::cin) {
                std::cout << "Įvestas: " << pazymys << " (kitas arba 0 baigti): ";
            }
        } else {
            if (&is == &std::cin) {
                std::cout << "Netinkamas pažymys! Turi būti 1-10. Bandykite dar kartą: ";
            }
            continue;
        }
    }
    
    if (is.fail() && !is.eof()) {
        is.clear();
    }
    
    if (&is == &std::cin) {
        std::cout << "Egzamino pažymys: ";
        while (!(is >> studentas.egzas_) || studentas.egzas_ < 1 || studentas.egzas_ > 10) {
            std::cout << "Netinkamas pažymys! Turi būti 1-10. Bandykite dar kartą: ";
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        
        std::cout << "Studento duomenys sėkmingai įvesti!\n";
    } else {
        if (!studentas.nd_.empty()) {
            studentas.egzas_ = studentas.nd_.back();
            studentas.nd_.pop_back();
        }
    }
    
    return is;
}

std::ostream& operator<<(std::ostream& os, const Studentas& studentas) {
    auto vid = studentas.gautiGalutiniVidurki();
    auto med = studentas.gautiGalutiniMediana();
    
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

//Papildomi metodai
void Studentas::isvalytiDuomenis() {
    vardas_.clear();
    pavarde_.clear();
    nd_.clear();
    egzas_ = 0;
    galutinis_vid_ = -1.0;
    galutinis_med_ = -1.0;
    DEBUG_LOG("Studento duomenys išvalyti (" << this << ")");
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
    galutinis_vid_ = -1.0;
    galutinis_med_ = -1.0;
    
    DEBUG_LOG("Sugeneruoti " << nd_kiekis << " ND ir egzamino pažymiai (" << this << ")");
}

void Studentas::spausdintiInformacija() const {
    std::cout << *this << "\n";
}

//Debug LOG
void demonstruotiRuleOfThree() {
    std::cout << "\n ===== RULE OF THREE/FIVE DEMONSTRAVIMAS =====\n\n";
    
    std::cout << "1. SUKURIAMAS ORIGINALUS STUDENTAS:\n";
    Studentas s1("Jonas", "Jonaitis");
    std::vector<int> nd = {8, 9, 7, 10};
    s1.setNd(nd);
    s1.setEgzas(8);
    std::cout << s1 << "\n\n";
    
    std::cout << "2. COPY KONSTRUKTORIUS (s1 → s2):\n";
    Studentas s2 = s1;
    std::cout << s2 << "\n\n";
    
    std::cout << "3. COPY ASSIGNMENT (s2 → s3):\n";
    Studentas s3;
    s3 = s2;
    std::cout << s3 << "\n\n";
    
    std::cout << "4. MOVE KONSTRUKTORIUS (s1 → s4):\n";
    Studentas s4 = std::move(s1);
    std::cout << "s4 po move:\n" << s4 << "\n";
    std::cout << "s1 po move (turėtų būti tuščias):\n";
    std::cout << "Vardas: '" << s1.getVardas() << "', Pavardė: '" << s1.getPavarde()
              << "', Egzas: " << s1.getEgzas() << "\n\n";
    
    std::cout << "5. MOVE ASSIGNMENT (s4 → s5):\n";
    Studentas s5;
    s5 = std::move(s4);
    std::cout << "s5 po move:\n" << s5 << "\n";
    std::cout << "s4 po move (turėtų būti tuščias):\n";
    std::cout << "Vardas: '" << s4.getVardas() << "', Pavardė: '" << s4.getPavarde()
              << "', Egzas: " << s4.getEgzas() << "\n\n";
    
    std::cout << "6. PALYGINIMO OPERATORIAI:\n";
    std::cout << "s2 == s3: " << (s2 == s3 ? "TAIP" : "NE") << "\n";
    std::cout << "s2 != s5: " << (s2 != s5 ? "TAIP" : "NE") << "\n";
    std::cout << "s2 < s5:  " << (s2 < s5 ? "TAIP" : "NE") << "\n";
    std::cout << "s2 > s5:  " << (s2 > s5 ? "TAIP" : "NE") << "\n\n";
    
    std::cout << "RULE OF THREE/FIVE DEMONSTRAVIMAS BAIGTAS!\n";
}

void demonstruotiRankiniĮvedimą() {
    std::cout << "\n=== RANKINIS ĮVEDIMAS ===\n";
    
    Studentas studentas;
    std::cout << "Įveskite studento duomenis:\n";
    std::cin >> studentas;
    
    std::cout << "\nĮVESTAS STUDENTAS:\n";
    std::cout << studentas << "\n";
}

void demonstruotiAutomatiniGeneravimą() {
    std::cout << "\n=== AUTOMATINIS GENERAVIMAS ===\n";
    
    Studentas studentas("Generated", "Student");
    studentas.generuotiPazymius(5);
    
    std::cout << "SUGENERUOTAS STUDENTAS:\n";
    std::cout << studentas << "\n";
}

void demonstruotiĮvestįIšFailo() {
    std::cout << "\n=== ĮVESTIS IŠ FAILO ===\n";
    
    std::string failoVardas = "demo_studentai.txt";
    std::ofstream failas(failoVardas);
    
    failas << "Vardas Pavarde";
    for (int i = 1; i <= 5; i++) failas << " ND" << i;
    failas << " Egzaminas\n";
    
    failas << "Jonas Jonaitis 8 9 7 6 10 9\n";
    failas << "Ona Onaite 10 9 8 7 9 8\n";
    failas << "Petras Petraitis 7 6 8 9 10 7\n";
    failas.close();
    
    std::cout << " Sukurtas demonstracinis failas: " << failoVardas << "\n";
    
    std::vector<Studentas> studentai;
    
    std::ifstream skaitomasFailas(failoVardas);
    if (!skaitomasFailas) {
        std::cout << " Klaida: Nepavyko atidaryti failo!\n";
        return;
    }

    std::string eilute;
    std::getline(skaitomasFailas, eilute);
    
    int studentuSk = 0;
    while (std::getline(skaitomasFailas, eilute)) {
        if (eilute.empty()) continue;
        
        std::stringstream ss(eilute);
        Studentas s;
        std::string vardas, pavarde;
        
        ss >> vardas >> pavarde;
        s.setVardas(vardas);
        s.setPavarde(pavarde);
        
        std::vector<int> nd;
        int pazymys;
        while (ss >> pazymys) {
            nd.push_back(pazymys);
        }
        
        if (!nd.empty()) {
            s.setEgzas(nd.back());
            nd.pop_back();
            s.setNd(nd);
        }
        
        studentai.push_back(std::move(s));
        studentuSk++;
    }
    
    skaitomasFailas.close();
    
    std::cout << "Sėkmingai nuskaityta " << studentai.size() << " studentų:\n";
    for(size_t i = 0; i < studentai.size(); ++i) {
        std::cout << "Studentas " << i+1 << ":\n";
        std::cout << studentai[i] << "\n\n";
    }
    
    std::remove(failoVardas.c_str());
}

void demonstruotiIšvestįĮFailą() {
    std::cout << "\n=== IŠVESTIS Į FAILĄ ===\n";
    
    std::vector<Studentas> studentai;
    
    Studentas s1("Jonas", "Jonaitis");
    s1.setNd({8, 9, 7});
    s1.setEgzas(8);
    
    Studentas s2("Ona", "Onaite");
    s2.setNd({10, 9, 8});
    s2.setEgzas(9);
    
    Studentas s3("Petras", "Petraitis");
    s3.generuotiPazymius(4);
    
    studentai.push_back(std::move(s1));
    studentai.push_back(std::move(s2));
    studentai.push_back(std::move(s3));
    
    //Išvedame į failą
    std::string failoVardas = "studentu_rezultatai.txt";
    std::ofstream rezultatai(failoVardas);
    
    rezultatai << "STUDENTŲ REZULTATAI\n";
    rezultatai << "===================\n\n";
    
    for(size_t i = 0; i < studentai.size(); ++i) {
        rezultatai << "Studentas " << i+1 << ":\n";
        auto vid = studentai[i].gautiGalutiniVidurki();
        auto med = studentai[i].gautiGalutiniMediana();
        rezultatai << "Vardas: " << studentai[i].getVardas() << "\n";
        rezultatai << "Pavardė: " << studentai[i].getPavarde() << "\n";
        rezultatai << "ND pažymiai: ";
        
        for(size_t j = 0; j < studentai[i].getNd().size(); ++j) {
            rezultatai << studentai[i].getNd()[j];
            if (j < studentai[i].getNd().size() - 1) rezultatai << ", ";
        }
        
        rezultatai << "\nEgzamino pažymys: " << studentai[i].getEgzas() << "\n";
        rezultatai << "Galutinis balas: " << std::fixed << std::setprecision(2) << vid << " (vidurkis)\n";
        rezultatai << "Galutinis balas: " << med << " (mediana)\n";
        rezultatai << "------------------------\n\n";
    }
    
    rezultatai.close();
    
    std::cout << "Studentų duomenys sėkmingai išvesti į failą: " << failoVardas << "\n";
    
    std::cout << "Failo turinys:\n";
    std::ifstream skaitymas(failoVardas);
    std::string eilute;
    while(std::getline(skaitymas, eilute)) {
        std::cout << eilute << "\n";
    }
    skaitymas.close();
}

void paleistiVisusRežimus() {
    std::cout << "\n===== VISI REŽIMAI IŠ EILĖS =====\n";
    
    std::cout << "\n1. RULE OF THREE/FIVE:\n";
    demonstruotiRuleOfThree();
    
    std::cout << "\n2. RANKINIS ĮVEDIMAS:\n";
    demonstruotiRankiniĮvedimą();
    
    std::cout << "\n3. AUTOMATINIS GENERAVIMAS:\n";
    demonstruotiAutomatiniGeneravimą();
    
    std::cout << "\n4. ĮVESTIS IŠ FAILO:\n";
    demonstruotiĮvestįIšFailo();
    
    std::cout << "\n5. IŠVESTIS Į FAILĄ:\n";
    demonstruotiIšvestįĮFailą();
    
    std::cout << "\n VISI REŽIMAI SĖKMINGAI PABAIGTI!\n";
}

void demonstruotiVisusRežimus() {
    std::cout << "\n===== VISI ĮVEDIMO/IŠVEDIMO BŪDAI =====\n\n";
    
    int pasirinkimas;
    do {
        std::cout << "Pasirinkite demonstracinį režimą:\n";
        std::cout << "1 - Rule of Three/Five demonstracija\n";
        std::cout << "2 - Rankinis įvedimas\n";
        std::cout << "3 - Automatinis generavimas\n";
        std::cout << "4 - Įvestis iš failo\n";
        std::cout << "5 - Išvestis į failą\n";
        std::cout << "6 - Visi režimai iš eilės\n";
        std::cout << "0 - Grįžti į pagrindinį meniu\n";
        std::cout << "Pasirinkimas: ";
        
        std::cin >> pasirinkimas;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch(pasirinkimas) {
            case 1:
                demonstruotiRuleOfThree();
                break;
            case 2:
                demonstruotiRankiniĮvedimą();
                break;
            case 3:
                demonstruotiAutomatiniGeneravimą();
                break;
            case 4:
                demonstruotiĮvestįIšFailo();
                break;
            case 5:
                demonstruotiIšvestįĮFailą();
                break;
            case 6:
                paleistiVisusRežimus();
                break;
            case 0:
                std::cout << "Grįžtama į pagrindinį meniu...\n";
                break;
            default:
                std::cout << "Netinkamas pasirinkimas!\n";
        }
        std::cout << "\n";
    } while(pasirinkimas != 0);
}
