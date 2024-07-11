#include "yapl.hpp"
#include <iostream>

int main() {
    std::cout << "Line plot example" << std::endl;
    yapl::Plot plot;
    plot.addData({0.1, 0.2, 0.3, 0.4}, {0.1, 0.4, 0.9, 1.6});
    plot.addData({0.1, 0.2, 0.3, 0.4}, {1.6, 0.9, 0.4, 0.1});
    plot.xLabel("X values");
    plot.yLabel("Y values");
    plot.title("plot title");
    plot.legend({"first set", "second set"});
    std::cout << "Saving plot" << std::endl;
    plot.save("/YAPL/img/test/example_plot.png");
    return 0;
}