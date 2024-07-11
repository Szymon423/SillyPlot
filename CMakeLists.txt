cmake_minimum_required(VERSION 3.10)
project(YAPL)

# Ustawienie ścieżki do vcpkg
set(CMAKE_TOOLCHAIN_FILE /usr/local/vcpkg/scripts/buildsystems/vcpkg.cmake)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Dodanie plików źródłowych
add_library(YAPL
    src/plot.cpp
    src/exception.cpp
)

# Ustawienie katalogu nagłówków
target_include_directories(YAPL PUBLIC include)

# Dodanie przykładu
add_executable(example examples/basic_plot.cpp)
target_link_libraries(example YAPL)

# Dodanie testów (opcjonalnie)
enable_testing()
add_executable(test_plot tests/test_plot.cpp)
target_link_libraries(test_plot YAPL)
add_test(NAME TestPlot COMMAND test_plot)
