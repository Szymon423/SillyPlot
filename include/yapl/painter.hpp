#pragma once

#include "yapl.hpp"
#include <cairo.h>
#include <cairo-svg.h>

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
    
    /// @brief Function to calculate nice numbers for ticks
    /// @param range The range of the data to be divided into ticks
    /// @param round A boolean indicating whether to round the result to the nearest nice number
    /// @return A "nice" number that can be used as a tick interval
    double nice_numbers(double range, bool round);

    /// @brief Function to convert a double to a nicely formatted string
    /// @param value The double value to be converted
    /// @param precision The precision to be used for the conversion
    /// @return A string representation of the double value
    std::string double_to_nice_string(double value, int precision = 6);

    /// @brief Draws a rounded rectangle on the given Cairo context.
    /// @param cr The Cairo drawing context.
    /// @param x The X coordinate of the top-left corner of the rectangle.
    /// @param y The Y coordinate of the top-left corner of the rectangle.
    /// @param width The width of the rectangle.
    /// @param height The height of the rectangle.
    /// @param radius The radius of the rounded corners.
    /// @param fill true - fills rectangle, false does not
    void draw_rounded_rectangle(cairo_t* cr, double x, double y, double width, double height, double radius, bool fill = false);

    /// @brief Function responsible for drawing plot 
    /// @param plot Plot object
    /// @param path path to save plot 
    /// @param width pixel number for width
    /// @param height pixel number for height
    void drawPlot(const Plot& plot, const std::filesystem::path& path, const uint16_t width = 800, const uint16_t height = 600);
}
