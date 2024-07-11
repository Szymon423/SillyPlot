#include "yapl.hpp"


yapl::Plot::Plot() {

}

void yapl::Plot::addData(const std::vector<double>& x, const std::vector<double>& y) {
    // check if sizes fit eachother
    if (x.size() != y.size()) {
        throw yapl::Exception("Provided X data size differs Y data size");
    }

    // add actual data
    _x.push_back(x);
    _y.push_back(y);
}

void yapl::Plot::addData(const std::vector<std::pair<double, double>>& data) {
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

void yapl::Plot::xLabel(const std::string& label) {
    _x_label = label;
}

void yapl::Plot::yLabel(const std::string& label) {
    _y_label = label;
}

void yapl::Plot::title(const std::string& label) {
    _title = label;
}

void yapl::Plot::legend(const std::vector<std::string>& legend) {
    if (legend.size() != _x.size()) {
        throw yapl::Exception("Legend size does not metch data size");
    }

    _legend = legend;
}

void yapl::Plot::save(const std::filesystem::path& path, const uint16_t width, const uint16_t height) {

}