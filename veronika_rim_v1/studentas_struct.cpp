#include "studentas_struct.h"
#include <algorithm>
#include <numeric>

double StudentasStruct::skaiciuotiVidurki() const {
    if(nd.empty()) return 0;
    double sum = std::accumulate(nd.begin(), nd.end(), 0.0);
    return sum / nd.size();
}

double StudentasStruct::skaiciuotiMediana() const {
    if(nd.empty()) return 0;
    std::vector<int> temp_nd = nd;
    std::sort(temp_nd.begin(), temp_nd.end());
    size_t size = temp_nd.size();
    if(size % 2 == 0)
        return (temp_nd[size/2 - 1] + temp_nd[size/2]) / 2.0;
    else
        return temp_nd[size/2];
}

std::pair<double, double> StudentasStruct::skaiciuotiGalutinius() const {
    double vidurkis = skaiciuotiVidurki();
    double mediana = skaiciuotiMediana();
    double galutinis_vid = 0.4 * vidurkis + 0.6 * egzas;
    double galutinis_med = 0.4 * mediana + 0.6 * egzas;
    return {galutinis_vid, galutinis_med};
}

std::istream& operator>>(std::istream& is, StudentasStruct& studentas) {
    is >> studentas.vardas >> studentas.pavarde;
    
    studentas.nd.clear();
    int pazymys;
    while (is >> pazymys) {
        studentas.nd.push_back(pazymys);
    }
    is.clear();
    
    if (!studentas.nd.empty()) {
        studentas.egzas = studentas.nd.back();
        studentas.nd.pop_back();
    }
    
    return is;
}

std::ostream& operator<<(std::ostream& os, const StudentasStruct& studentas) {
    os << studentas.vardas << " " << studentas.pavarde;
    for (int pazymys : studentas.nd) {
        os << " " << pazymys;
    }
    os << " " << studentas.egzas;
    return os;
}
