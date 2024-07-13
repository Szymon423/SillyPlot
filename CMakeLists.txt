cmake_minimum_required(VERSION 3.10)
project(YAPL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Search for cario with pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(CAIRO REQUIRED cairo)

# Add source files
add_library(YAPL
    src/plot.cpp
    src/exception.cpp
    src/painter.cpp
    src/color.cpp
)

# Set include directory
target_include_directories(YAPL PUBLIC include ${CAIRO_INCLUDE_DIRS})

# Linkowanie biblioteki Cairo do YAPL
target_link_libraries(YAPL PRIVATE ${CAIRO_LIBRARIES})

# Add basic example
add_executable(example examples/basic_plot.cpp)
target_link_libraries(example YAPL)

# Add tests
enable_testing()
add_executable(test_plot tests/test_plot.cpp)
target_link_libraries(test_plot YAPL)
add_test(NAME TestPlot COMMAND test_plot)