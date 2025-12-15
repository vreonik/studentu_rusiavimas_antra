cmake_minimum_required(VERSION 3.20)
project(StudentuRusiavimoSistema VERSION 3.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Windows specific settings
if(WIN32)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS UNICODE _UNICODE)
    add_compile_options(/W4 /WX)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")
endif()

add_executable(studentu-rusiavimo-sistema
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

target_include_directories(studentu-rusiavimo-sistema PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_target_properties(studentu-rusiavimo-sistema PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin"
)

option(BUILD_TESTS "Build unit tests" ON)

if(BUILD_TESTS)
    find_package(GTest QUIET)
    
    if(GTest_FOUND)
        message(STATUS "Google Test found, building tests")
        
        add_executable(unit_tests
            tests/unit_tests.cpp
            studentas.cpp
            studentas_struct.cpp
            strategijos.cpp
            nuskaityti.cpp
            apdorojimas.cpp
            util.cpp
            zmogus.cpp
            failu_generavimas.cpp
        )
        
        target_include_directories(unit_tests PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}/include
        )
        
        target_link_libraries(unit_tests GTest::gtest GTest::gtest_main)
        
        add_test(NAME UnitTests COMMAND unit_tests)
        
        set_target_properties(unit_tests PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        )
        
    else()
        message(WARNING "Google Test not found, skipping tests")
    endif()
endif()