#pragma once

#include <vector>
#include <string>
#include <filesystem>
#include <utility>

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

        /// @brief Function to set title
        /// @param label plot title 
        void legend(const std::vector<std::string>& legend);
        
        /// @brief Function to save plot as image
        /// @param path path under which save image
        /// @param width width in pixels of image
        /// @param height height in pixels of image
        void save(const std::filesystem::path& path, const uint16_t width = 800, const uint16_t height = 600);

        /// @brief Function to draw plot with cario
        /// @param plot refference to paint object
        /// @param path 
        /// @param width 
        /// @param height 
        friend void drawPlot(const Plot& plot, const std::filesystem::path& path, const uint16_t width, const uint16_t height);

    private:
        std::vector<std::vector<double>> _x;
        std::vector<std::vector<double>> _y;
        std::string _x_label;
        std::string _y_label;
        std::string _title;
        std::vector<std::string> _legend;
    };
}