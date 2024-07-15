#include "yapl.hpp"
#include <cassert>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <iostream>

void test_basic_plot() {
    try {
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
    catch (yapl::Exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void test_time_plot() {
    try {
        yapl::Plot plot;
        std::vector<double> x, y;
        for (int i = 0; i < 1000; i++) {
            x.push_back(i);
            y.push_back(time(nullptr));
        }
        plot.addData(x, y);
        plot.xLabel("time");
        plot.yLabel("value");
        plot.title("Value in time");
        plot.grid(true);
        plot.setColorMaker([](double x, double y) -> yapl::Color {
            if (y >= 0.7) return yapl::Color(1.0, 0.0, 0.0);
            if (y >= 0.5) return yapl::Color(1.0, 1.0, 0.0);
            return yapl::Color(0.0, 0.0, 1.0);
        });
        plot.setLabelMaker([](double val) -> std::string {
            time_t t = val;
            std::tm *tm_ptr = std::localtime(&t);
            std::stringstream ss;
            ss << std::put_time(tm_ptr, "%Y-%m-%d %H:%M:%S");
            return ss.str();
        });
        plot.save("/YAPL/img/test/test_time_output.png");
    }
    catch (yapl::Exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

int main() {
    test_basic_plot();
    test_time_plot();
    return 0;
}