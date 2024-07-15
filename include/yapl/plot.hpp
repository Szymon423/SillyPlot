#pragma once

#include <vector>
#include <string>
#include <filesystem>
#include <utility>
#include <optional>
#include <functional>

namespace yapl {
    class Plot {
    public:
        /// @brief Default constructor
        Plot();

        /// @brief Function to add data as two independent vector
        /// @param x values on x axis 
        /// @param y values on y axis 
        void addData(const std::vector<double>& x, const std::vector<double>& y);

        /// @brief Function to add data as vector of <X,Y>
        /// @param data vector of <X,Y>
        void addData(const std::vector<std::pair<double, double>>& data);
        
        /// @brief Function to set x label
        /// @param label x label 
        void xLabel(const std::string& label);
        
        /// @brief Function to set y label
        /// @param label y label 
        void yLabel(const std::string& label);

        /// @brief Function to set title
        /// @param label plot title 
        void title(const std::string& label);

        /// @brief Function to set legend
        /// @param label plot title 
        void legend(const std::vector<std::string>& legend, const LegendPosition _legend_position = LegendPosition::TOP_RIGHT);
        
        /// @brief Function to save plot as image
        /// @param path path under which save image
        /// @param width width in pixels of image
        /// @param height height in pixels of image
        void save(const std::filesystem::path& path, const uint16_t width = 800, const uint16_t height = 600);

        /// @brief Function to set x axis limits
        /// @param lower_bound lower value
        /// @param higher_bound higher value
        void xLim(const double lower_bound, const double higher_bound);

        /// @brief Function to set y axis limits
        /// @param lower_bound lower value
        /// @param higher_bound higher value
        void yLim(const double lower_bound, const double higher_bound);

        /// @brief Function to configure grid
        /// @param state true - grid visible, false - grid invisible
        void grid(const bool state);

        /// @brief Function to set grid color
        /// @param grid_color desired color of grid
        void setGridColor(Color grid_color);

        /// @brief Function to set label maker function defining how user want them to look like
        /// @param label_maker function like std::string label_maker(double) which makes labels 
        void setLabelMaker(std::function<std::string(double)> label_maker);

        /// @brief Function to set color maker function defining data on plot should be colored
        /// @param color_maker function like Color color_maker(double, double) which defines data color on plot
        void setColorMaker(std::function<Color(double, double)> color_maker);

        /// @brief Function to draw plot with cario
        /// @param plot refference to paint object
        /// @param path 
        /// @param width 
        /// @param height 
        friend void drawPlot(const Plot& plot, const std::filesystem::path& path, const uint16_t width, const uint16_t height);

    private:
        std::vector<std::vector<double>> _x;
        std::vector<std::vector<double>> _y;
        std::optional<std::string> _x_label;
        std::optional<std::string> _y_label;
        std::optional<std::string> _title;
        std::optional<std::vector<std::string>> _legend;
        std::optional<double> _x_lim_min;
        std::optional<double> _x_lim_max;
        std::optional<double> _y_lim_min;
        std::optional<double> _y_lim_max;
        bool _grid;
        bool _draw_x_ticks;
        bool _draw_y_ticks;
        std::optional<std::function<std::string(double)>> _label_maker;
        std::optional<std::function<Color(double, double)>> _color_maker;
        Color _grid_color;
        LegendPosition _legend_position;
    };
}