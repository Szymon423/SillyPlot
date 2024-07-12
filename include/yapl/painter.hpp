#pragma once

#include "yapl.hpp"

namespace yapl {
    /// @brief 
    /// @param val 
    /// @param val_low_bound 
    /// @param val_high_bound 
    /// @param output_low_bound 
    /// @param output_high_bound 
    /// @return 
    double scale_value(const double& val, 
        const double& val_low_bound, 
        const double& val_high_bound,
        const double& output_low_bound,
        const double& output_high_bound);

    /// @brief Function responsible for drawing plot 
    /// @param plot Plot object
    /// @param path path to save plot 
    /// @param width pixel number for width
    /// @param height pixel number for height
    void drawPlot(const Plot& plot, const std::filesystem::path& path, const uint16_t width = 800, const uint16_t height = 600);
}
