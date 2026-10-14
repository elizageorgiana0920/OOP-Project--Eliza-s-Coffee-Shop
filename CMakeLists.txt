
cmake_minimum_required(VERSION 3.14)

project(cafenea_tema_3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main application
add_executable(cafenea_tema_3
        main.cpp
        Ingredient.cpp
        Produs.cpp
        Bautura.cpp
        Patiserie.cpp
        Gestiune.cpp
        Comanda.cpp
        Autentificare.cpp
        Sandwich.cpp
)

# Download and configure GoogleTest
include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# Enable automated testing
enable_testing()

# Test executable
add_executable(coffee_shop_tests
        tests/test_strategie_pret.cpp
        tests/test_depozit.cpp
        tests/test_ingredient.cpp
        Ingredient.cpp
)



target_include_directories(coffee_shop_tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(coffee_shop_tests
        PRIVATE GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(coffee_shop_tests)
