echo "OPTIMIZAVIMO FLAG'Ų TESTAVIMAS"

for opt_level in O0 O1 O2 O3; do
    echo "Kompiliuojama su -$opt_level..."
    g++ -std=c++17 -${opt_level} -o test_${opt_level} test_struct_vs_class.cpp *.cpp
    
    echo "Testuojama su $opt_level:"
    ./test_${opt_level}
    echo "EXE dydis: $(ls -lh test_${opt_level} | awk '{print $5}')"
    echo "---"
done
