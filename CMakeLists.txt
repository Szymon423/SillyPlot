cmake_minimum_required(VERSION 3.10)
project(SillyPlot)

# Ustawienie ścieżki do vcpkg
set(CMAKE_TOOLCHAIN_FILE /path/to/vcpkg/scripts/buildsystems/vcpkg.cmake)

# Dodanie plików źródłowych
add_library(SillyPlot
    src/Plot.cpp
    src/PNGWriter.cpp
)

# Ustawienie katalogu nagłówków
target_include_directories(SillyPlot PUBLIC include)

# Dodanie przykładu
add_executable(example examples/basic_plot.cpp)
target_link_libraries(example SillyPlot)

# Dodanie testów (opcjonalnie)
enable_testing()
add_executable(test_plot tests/test_plot.cpp)
target_link_libraries(test_plot SillyPlot)
add_test(NAME TestPlot COMMAND test_plot)
