#include "yapl/plot.hpp"
#include <cassert>

void test_plot() {
    yapl::Figure plot(800, 600);
    plot.add_data({0.1, 0.2, 0.3, 0.4}, {0.1, 0.4, 0.9, 1.6});
    plot.save("test_plot.png");
}

int main() {
    test_plot();
    return 0;
}