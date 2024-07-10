#include "SillyPlot/plot.hpp"


SillyPlot::Plot::Plot(int width, int height) : width(width), height(height) {
    std::cout << "Constructor" << std::endl;
}

void SillyPlot::Plot::add_data(const std::vector<double>& x, const std::vector<double>& y) {
    std::cout << "Adding data" << std::endl;
    dataX.push_back(x);
    dataY.push_back(y);
}

void SillyPlot::Plot::save(const std::string& filename) {
    std::cout << "Saving" << std::endl;
    std::vector<unsigned char> image(width * height * 3, 255); // Biały obraz

    // Prosty przykład rysowania wykresu
    for (size_t i = 0; i < dataX.size(); ++i) {
        for (size_t j = 0; j < dataX[i].size(); ++j) {
            int x = static_cast<int>(dataX[i][j] * width);
            int y = static_cast<int>(dataY[i][j] * height);
            if (x >= 0 && x < width && y >= 0 && y < height) {
                image[(y * width + x) * 3 + 0] = 255; // R
                image[(y * width + x) * 3 + 1] = 0;   // G
                image[(y * width + x) * 3 + 2] = 0;   // B
            }
        }
    }
}
