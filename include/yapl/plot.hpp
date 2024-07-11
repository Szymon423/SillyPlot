#pragma once

#include <vector>
#include <string>
#include <filesystem>
#include <iostream>

namespace yaml {
    class Figure {
    public:
        Figure(int width, int height);
        void add_data(const std::vector<double>& x, const std::vector<double>& y);
        void save(const std::string& filename);

    private:
        int width;
        int height;
        std::vector<std::vector<double>> dataX;
        std::vector<std::vector<double>> dataY;
    };
};