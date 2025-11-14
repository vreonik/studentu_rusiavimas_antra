#include "util.h"
#include <algorithm>

std::string be_priesdelio(const std::string &kelias){
    auto pos = kelias.find_last_of("/\\");
    std::string vardas = (pos == std::string::npos) ? kelias : kelias.substr(pos + 1);
    auto taskas = vardas.find_last_of('.');
    if (taskas == std::string::npos) return vardas;
    return vardas.substr(0, taskas);
}

std::pair<double, double> skaiciuoti_galutinius(const Studentas &s){
    return s.skaiciuotiGalutinius();
}
