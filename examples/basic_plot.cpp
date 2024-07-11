#include "yapl.hpp"

int main() {
    yapl::Plot plot;
    plot.addData({0.1, 0.2, 0.3, 0.4}, {0.1, 0.4, 0.9, 1.6});
    plot.save("example_plot.png");
    return 0;
}