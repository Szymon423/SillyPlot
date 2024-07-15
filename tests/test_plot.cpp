#include "yapl.hpp"
#include <cassert>
#include <cmath>

void test_plot() {
    yapl::Plot plot;
    std::vector<double> x, y;
    for (int i = 0; i < 1000; i++) {
        x.push_back(i / 100.0);
        y.push_back(1.0 + std::sin(i / 100.0));
    }
    plot.addData(x, y);
    plot.xLabel("x");
    plot.yLabel("sin(x)");
    plot.title("plot title");
    plot.grid(true);
    plot.legend({"first set"});
    plot.setColorMaker([](double x, double y) -> yapl::Color {
        if (y >= 0.7) return yapl::Color(1.0, 0.0, 0.0);
        if (y >= 0.5) return yapl::Color(1.0, 1.0, 0.0);
        return yapl::Color(0.0, 0.0, 1.0);
    });
    plot.save("/YAPL/img/test/test_output.png");
}

int main() {
    test_plot();
    return 0;
}