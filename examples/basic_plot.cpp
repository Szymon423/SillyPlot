#include "yapl.hpp"
#include <iostream>

int main() {
    try {
        yapl::Plot plot;
        plot.addData({10, 50}, {10, 90});
        plot.addData({10, 30}, {90, 50});
        plot.addData({80, 120, 160}, {10, 90, 10});
        plot.addData({100, 140}, {50, 50});
        plot.addData({190, 190, 240, 240, 190}, {10, 90, 90, 50, 50});
        plot.addData({270, 270, 320}, {90, 10, 10});
        plot.grid(true);
        plot.xLabel("X value");
        plot.yLabel("Y value");
        plot.title("Yet Another Plot Library");
        std::cout << "Saving plot" << std::endl;
        plot.save("/YAPL/img/test/example_plot.png", 800, 600);
    }
    catch (const yapl::Exception& e) {
        std::cout << "Caught error during plot generation" << std::endl;
    }
    return 0;
}