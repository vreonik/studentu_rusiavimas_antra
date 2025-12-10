cmake_minimum_required(VERSION 3.10)
project(StudentuRusiavimas VERSION 2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

#Main program
add_executable(studentu_rusiavimas
    main.cpp
    studentas.cpp
    studentas_struct.cpp
    nuskaityti.cpp
    apdorojimas.cpp
    failu_generavimas.cpp
    konteineriu_testavimas.cpp
    strategijos.cpp
    util.cpp
    zmogus.cpp
    test_struct_vs_class.cpp
)

target_include_directories(studentu_rusiavimas PRIVATE .)

#Unit tests
add_executable(unit_tests
    tests/unit_tests.cpp
    studentas.cpp
    studentas_struct.cpp
    strategijos.cpp
    nuskaityti.cpp
    apdorojimas.cpp
    util.cpp
    zmogus.cpp
)

target_include_directories(unit_tests PRIVATE .)
target_link_libraries(unit_tests GTest::gtest GTest::gtest_main Threads::Threads)

enable_testing()
add_test(NAME UnitTests COMMAND unit_tests)

install(TARGETS studentu_rusiavimas DESTINATION bin)
install(TARGETS unit_tests DESTINATION bin)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
    install(FILES README.md DESTINATION docs)
endif()