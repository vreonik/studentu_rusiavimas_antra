#pragma once
#include <string>
#include <vector>
#include <list>
#include "studentas.h"
#include "studentas_struct.h"

std::vector<Studentas> nuskaityti(const std::string& failas);
std::list<Studentas> nuskaityti_i_list(const std::string& failas);

std::vector<StudentasStruct> nuskaityti_struct(const std::string& failas);
std::list<StudentasStruct> nuskaityti_i_list_struct(const std::string& failas);
