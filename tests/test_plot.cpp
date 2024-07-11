#include "yapl.hpp"
#include <cassert>

void test_plot() {
    yapl::Plot plot;
    plot.addData({200, 300, 400, 500}, {100, 200, 300, 400});
    plot.xLabel("X values");
    plot.yLabel("Y values");
    plot.title("plot title");
    plot.legend({"first set"});
    plot.save("/YAPL/img/test/test_output.png");
}

int main() {
    test_plot();
    return 0;
}