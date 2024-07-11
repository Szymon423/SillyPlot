#pragma once

#include "yapl.hpp"

namespace yapl {
    /// @brief Function to interpolate data from given X and Y on to desired pixels vectors
    /// @param x_from 
    /// @param y_from 
    /// @param x_to 
    /// @param y_to 
    void interpolate_data_over_pixels(const std::vector<double>& x_from, 
        const std::vector<double>& y_from, 
        const std::vector<uint16_t>& x_to, 
        std::vector<uint16_t>& y_to);
        
    /// @brief Function responsible for drawing plot 
    /// @param plot Plot object
    /// @param path path to save plot 
    /// @param width pixel number for width
    /// @param height pixel number for height
    void drawPlot(const Plot& plot, const std::filesystem::path& path, const uint16_t width = 800, const uint16_t height = 600);
}
