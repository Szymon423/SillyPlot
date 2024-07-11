#include "yapl.hpp"
#include <cairo.h>
#include <cairo-svg.h>
#include <stdexcept>

namespace yapl {
    void interpolate_data_over_pixels(const std::vector<double>& x_from, 
        const std::vector<double>& y_from, 
        const std::vector<uint16_t>& x_to, 
        std::vector<uint16_t>& y_to) {
        // code for implementation
        if (x_from.size() != y_from.size()) {
            throw Exception("x_from and y_from must have the same size");
        }

        y_to.clear();
        y_to.reserve(x_to.size());

        for (const auto& x : x_to) {
            // Find the interval [x_from[i], x_from[i+1]] that contains x
            auto it = std::lower_bound(x_from.begin(), x_from.end(), x);
            
            if (it == x_from.end()) {
                // If x is beyond the last element of x_from, use the last interval
                it = x_from.end() - 1;
            } 
            else if (it != x_from.begin() && *it != x) {
                // If x is not exactly equal to an element in x_from, use the previous interval
                --it;
            }

            size_t i = std::distance(x_from.begin(), it);
            
            // Linear interpolation
            if (i + 1 < x_from.size()) {
                double x0 = x_from[i];
                double y0 = y_from[i];
                double x1 = x_from[i + 1];
                double y1 = y_from[i + 1];

                double y = y0 + (x - x0) * (y1 - y0) / (x1 - x0);
                y_to.push_back(static_cast<uint16_t>(y));
            } 
            else {
                // If we are at the last element, just use the last y value
                y_to.push_back(static_cast<uint16_t>(y_from[i]));
            }
        }
    }
    
    void drawPlot(const Plot& plot, const std::filesystem::path& path, const uint16_t width, const uint16_t height) {
        cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
        cairo_t* cr = cairo_create(surface);

        // Background
        cairo_set_source_rgb(cr, 1, 1, 1);
        cairo_paint(cr);

        // Draw axes
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_set_line_width(cr, 2.0);

        // X axis
        cairo_move_to(cr, 50, height - 50);
        cairo_line_to(cr, width - 50, height - 50);
        cairo_stroke(cr);

        // Y axis
        cairo_move_to(cr, 50, height - 50);
        cairo_line_to(cr, 50, 50);
        cairo_stroke(cr);

        // Draw data
        cairo_set_line_width(cr, 1.5);
        for (size_t i = 0; i < plot._x.size(); ++i) {
            cairo_set_source_rgb(cr, 0, 0, 1); // Blue color for lines
            
            // Interpolacja danych
            std::vector<uint16_t> x_pixels;
            std::vector<uint16_t> y_pixels;
            for (double x_val : plot._x[i]) {
                x_pixels.push_back(static_cast<uint16_t>(50 + x_val));
            }
            interpolate_data_over_pixels(plot._x[i], plot._y[i], x_pixels, y_pixels);

            // Rysowanie interpolowanych danych
            cairo_move_to(cr, x_pixels[0], height - 50 - y_pixels[0]);
            for (size_t j = 1; j < x_pixels.size(); ++j) {
                cairo_line_to(cr, x_pixels[j], height - 50 - y_pixels[j]);
            }
            cairo_stroke(cr);
        }

        // Add labels and title
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size(cr, 20);
        cairo_move_to(cr, width / 2 - 50, 30);
        cairo_show_text(cr, plot._title.c_str());

        cairo_set_font_size(cr, 15);
        cairo_move_to(cr, width / 2 - 50, height - 20);
        cairo_show_text(cr, plot._x_label.c_str());

        cairo_move_to(cr, 10, height / 2);
        cairo_show_text(cr, plot._y_label.c_str());

        cairo_destroy(cr);
        cairo_surface_write_to_png(surface, path.c_str());
        cairo_surface_destroy(surface);
    }
}