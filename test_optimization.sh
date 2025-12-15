echo "OPTIMIZAVIMO FLAG'Ų TESTAVIMAS"

cat > temp_test.cpp << 'EOF'
#include <iostream>
#include <vector>
#include <chrono>
#include "studentas.h"
#include "studentas_struct.h"
#include "failu_generavimas.h"
#include "nuskaityti.h"
#include "strategijos.h"

void testas_su_dydziu(int dydis) {
    std::cout << "=== Testas su " << dydis << " studentų ===\n";
    
    std::string failo_vardas = "optim_test_" + std::to_string(dydis) + ".txt";
    
    std::cout << "Generuojamas failas... ";
    generuoti_faila(dydis, failo_vardas, 5);
    std::cout << "baigta\n";
    
    auto start_struct = std::chrono::high_resolution_clock::now();
    auto studentai_struct = nuskaityti_struct(failo_vardas);
    std::vector<StudentasStruct> vargsiukai_struct;
    auto rez_struct = strategija_3_struct(studentai_struct, vargsiukai_struct, 'v');
    auto end_struct = std::chrono::high_resolution_clock::now();
    
    auto start_class = std::chrono::high_resolution_clock::now();
    auto studentai_class = nuskaityti(failo_vardas);
    std::vector<Studentas> vargsiukai_class;
    auto rez_class = strategija_3(studentai_class, vargsiukai_class, 'v');
    auto end_class = std::chrono::high_resolution_clock::now();
    
    auto struct_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_struct - start_struct).count();
    auto class_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_class - start_class).count();
    
    std::cout << "Struct: " << struct_time << "ms, Vargsiukai: " << vargsiukai_struct.size() << "\n";
    std::cout << "Class:  " << class_time << "ms, Vargsiukai: " << vargsiukai_class.size() << "\n";
    
    if (struct_time > 0) {
        double skirtumas_procentais = ((double)(class_time - struct_time) / struct_time * 100);
        std::cout << "Skirtumas: " << (class_time - struct_time) << "ms ("
                  << skirtumas_procentais << "%)\n";
    }
    std::cout << std::endl;
}

int main() {
    testas_su_dydziu(100000);
    testas_su_dydziu(1000000);
    
    return 0;
}
EOF

for opt_level in O0 O1 O2 O3; do
    echo "Kompiliuojama su -$opt_level..."
    
    g++ -std=c++17 -${opt_level} -o test_${opt_level} temp_test.cpp \
        studentas.cpp studentas_struct.cpp failu_generavimas.cpp \
        nuskaityti.cpp strategijos.cpp util.cpp
    
    if [ $? -eq 0 ]; then
        echo "Testuojama su $opt_level:"
        ./test_${opt_level}
        echo "EXE dydis: $(ls -lh test_${opt_level} | awk '{print $5}')"
    else
        echo "Kompiliavimo klaida su -$opt_level"
    fi
    echo "---"
done

rm -f temp_test.cpp optim_test_*.txt
