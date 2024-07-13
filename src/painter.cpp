#include "yapl.hpp"
#include <cairo.h>
#include <cairo-svg.h>
#include <stdexcept>
#include <algorithm>
#include <limits>
#include <execution>
#include <functional>
#include <iostream>


namespace yapl {
    double scale_value(const double& val, 
        const double& val_low_bound, 
        const double& val_high_bound,
        const double& output_low_bound,
        const double& output_high_bound) {
        // check if we are not dividing by 0
        if (val_high_bound == val_low_bound) {
            throw Exception("Scalling impossible");
        }
        // scalling time    
        return (val - val_low_bound) * output_high_bound / (val_high_bound - val_low_bound) + output_low_bound;
    }
    
    void drawPlot(const Plot& plot, const std::filesystem::path& path, const uint16_t width, const uint16_t height) {
        constexpr uint16_t border_top_offset = 60;
        constexpr uint16_t border_bottom_offset = 60;
        constexpr uint16_t border_left_offset = 80;
        constexpr uint16_t border_right_offset = 80;
        constexpr uint16_t internal_border_offset = 10;
        constexpr uint16_t title_font_size = 20;
        constexpr uint16_t label_font_size = 14;
        cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
        cairo_t* cr = cairo_create(surface);

        // Background
        cairo_set_source_rgb(cr, 1, 1, 1);
        cairo_paint(cr);

        // Draw frame
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_set_line_width(cr, 1.0);

        // bottom
        cairo_move_to(cr, border_left_offset, height - border_bottom_offset);
        cairo_line_to(cr, width - border_right_offset, height - border_bottom_offset);
        cairo_stroke(cr);

        // right
        cairo_move_to(cr, width - border_right_offset, height - border_bottom_offset);
        cairo_line_to(cr, width - border_right_offset, border_top_offset);
        cairo_stroke(cr);

        // top
        cairo_move_to(cr, width - border_right_offset, border_top_offset);
        cairo_line_to(cr, border_left_offset, border_top_offset);
        cairo_stroke(cr);

        // left
        cairo_move_to(cr, border_left_offset, border_top_offset);
        cairo_line_to(cr, border_left_offset, height - border_bottom_offset);
        cairo_stroke(cr);

        // Draw data
        cairo_set_line_width(cr, 1.5);
        
        if (plot._x.empty()) {
            throw Exception("No data to plot.");
        }

        // Searching for min and max values on plot
        double x_min = std::numeric_limits<double>::max();
        double x_max = std::numeric_limits<double>::lowest();
        double y_min = std::numeric_limits<double>::max();
        double y_max = std::numeric_limits<double>::lowest();
        
        // Searching for X
        for (auto& data: plot._x) {
            const auto [min, max] = std::minmax_element(data.begin(), data.end());
            x_min = std::min(x_min, *min);
            x_max = std::max(x_max, *max);
        }

        // Searching for Y
        for (auto& data: plot._y) {
            const auto [min, max] = std::minmax_element(data.begin(), data.end());
            y_min = std::min(y_min, *min);
            y_max = std::max(y_max, *max);
        }

        // Workout scalling data for each dataset
        for (size_t i = 0; i < plot._x.size(); ++i) {
            // Prepare length value
            const size_t length = plot._x[i].size();

            // Prepare area size for plots
            double plot_x_start = border_left_offset + internal_border_offset;
            double plot_x_end = width - plot_x_start - border_right_offset - internal_border_offset;
            double plot_y_start = border_bottom_offset + internal_border_offset;
            double plot_y_end = height - plot_y_start - border_top_offset - internal_border_offset;
            // Prepare scalled vector for X
            auto& x = plot._x[i];
            std::vector<double> x_scalled(length);
            
            // Binding data to scale function 
            auto scale_x_value_bound = std::bind(scale_value, std::placeholders::_1, x_min, x_max, plot_x_start, plot_x_end);
            
            // Now we applay scale function to each point, but parallel and unsequentially
            std::transform(std::execution::par_unseq, x.begin(), x.end(), x_scalled.begin(), scale_x_value_bound);

            // Prepare scalled vector for Y
            auto& y = plot._y[i];
            std::vector<double> y_scalled(length);
            
            // Binding data to scale function 
            auto scale_y_value_bound = std::bind(scale_value, std::placeholders::_1, y_min, y_max, plot_y_start, plot_y_end);

            // Now we applay scale function to each point, but parallel and unsequentially
            std::transform(std::execution::par_unseq, y.begin(), y.end(), y_scalled.begin(), scale_y_value_bound);
            
            // Blue color for lines
            cairo_set_source_rgb(cr, 0, 0, 1); 
            
            // Rysowanie interpolowanych danych
            cairo_move_to(cr, x_scalled[0], height - y_scalled[0]);
            for (size_t j = 1; j < x_scalled.size(); ++j) {
                cairo_line_to(cr, (uint16_t)x_scalled[j], height - (uint16_t)y_scalled[j]);
            }
            cairo_stroke(cr);
        }

        // Add title if there is title provided
        if (plot._title.has_value()) {
            cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
            cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
            cairo_set_font_size(cr, title_font_size);
            
            // Title params
            cairo_text_extents_t extents;
            cairo_text_extents(cr, plot._title.value().c_str(), &extents);

            // Calculate the position to start drawing the text
            double title_x = (width - extents.width) / 2 - extents.x_bearing;
            double title_y = (border_top_offset + title_font_size) / 2;

            // Move to the calculated position and show the text
            cairo_move_to(cr, title_x, title_y);
            cairo_show_text(cr, plot._title.value().c_str());
        }

        if (plot._x_label.has_value()) {
            // Set font to Sans, blac, proper size
            cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
            cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
            cairo_set_font_size(cr, label_font_size);

            // x_label params
            cairo_text_extents_t extents;
            cairo_text_extents(cr, plot._x_label.value().c_str(), &extents);

            // Calculate the position to start drawing the text
            double x_label_x = (width - extents.width) / 2 - extents.x_bearing;
            double x_label_y = height - border_bottom_offset / 2;
            
            cairo_move_to(cr, x_label_x, x_label_y);
            cairo_show_text(cr, plot._x_label.value().c_str());
        }
        
        if (plot._y_label.has_value()) {
            // Set font to Sans, blac, proper size
            cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
            cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
            cairo_set_font_size(cr, label_font_size);

            // y_label params
            cairo_text_extents_t extents;
            cairo_text_extents(cr, plot._y_label.value().c_str(), &extents);

            // Calculate the position to start drawing the text
            double y_label_x = (border_left_offset - extents.width) / 2 - extents.x_bearing;
            double y_label_y = (height + title_font_size) / 2;
            
            cairo_move_to(cr, y_label_x, y_label_y);
            cairo_show_text(cr, plot._y_label.value().c_str());
        }

        cairo_destroy(cr);
        cairo_surface_write_to_png(surface, path.c_str());
        cairo_surface_destroy(surface);
    }
}