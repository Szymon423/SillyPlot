#include "yapl.hpp"

namespace yapl {
    Plot::Plot() : _grid(false), 
        _draw_x_ticks(true), 
        _draw_y_ticks(true),
        _grid_color(0.8, 0.8, 0.8) {

    }

    void Plot::addData(const std::vector<double>& x, const std::vector<double>& y) {
        // check if sizes fit eachother
        if (x.size() != y.size()) {
            throw Exception("Provided X data size differs Y data size");
        }

        // add actual data
        _x.push_back(x);
        _y.push_back(y);
    }

    void Plot::addData(const std::vector<std::pair<double, double>>& data) {
        // prepare individual vectors
        std::vector<double> x(data.size()); 
        std::vector<double> y(data.size());
        
        for (int i = 0; i < data.size(); i++) {
            x.at(i) = std::get<0>(data.at(i));
            y.at(i) = std::get<1>(data.at(i));
        }

        _x.push_back(x);
        _y.push_back(y);
    }

    void Plot::xLabel(const std::string& label) {
        _x_label = label;
    }

    void Plot::yLabel(const std::string& label) {
        _y_label = label;
    }

    void Plot::title(const std::string& label) {
        _title = label;
    }

    void Plot::legend(const std::vector<std::string>& legend) {
        if (legend.size() != _x.size()) {
            throw Exception("Legend size does not metch data size");
        }

        _legend = legend;
    }

    void Plot::save(const std::filesystem::path& path, const uint16_t width, const uint16_t height) {
        drawPlot(*this, path, width, height);
    }

    void Plot::xLim(const double lower_bound, const double higher_bound) {
        _x_lim_min = lower_bound;
        _x_lim_max = higher_bound;
    }

    void Plot::yLim(const double lower_bound, const double higher_bound) {
        _y_lim_min = lower_bound;
        _y_lim_max = higher_bound;
    }

    void Plot::grid(const bool state) {
        _grid = state;
    }
}