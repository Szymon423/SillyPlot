#include "yapl.hpp"
#include <iostream>

int main() {
    try {
        yapl::Plot plot;
        plot.addData({10, 50, 30, 10}, {10, 90, 50, 90});
        plot.addData({80, 120, 160, 140, 100}, {10, 90, 10, 50, 50});
        plot.addData({190, 190, 240, 240, 190}, {10, 90, 90, 50, 50});
        plot.addData({270, 270, 320}, {90, 10, 10});
        plot.grid(true);
        plot.xLabel("X value");
        plot.yLabel("Y value");
        plot.title("Yet Another Plot Library");
        plot.legend({"Yet", "Another", "Plot", "Library"});
        plot.setLabelMaker([](double val) -> std::string {
            return "X: " + std::to_string((int)val);
        });
        std::cout << "Saving plot" << std::endl;
        plot.save("/YAPL/img/test/example_plot.png", 800, 600);
    }
    catch (const yapl::Exception& e) {
        std::cout << "Caught error during plot generation" << std::endl;
    }
    return 0;
}