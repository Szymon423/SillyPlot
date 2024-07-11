#include "yapl.hpp"
#include <cairo.h>
#include <cairo-svg.h>
#include <stdexcept>

namespace yapl {
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
            cairo_move_to(cr, 50 + plot._x[i][0], height - 50 - plot._y[i][0]);
            for (size_t j = 1; j < plot._x[i].size(); ++j) {
                cairo_line_to(cr, 50 + plot._x[i][j], height - 50 - plot._y[i][j]);
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