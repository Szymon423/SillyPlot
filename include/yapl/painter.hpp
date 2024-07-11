#pragma once

#include "yapl.hpp"

namespace yapl {
    void drawPlot(const Plot& plot, const std::filesystem::path& path, const uint16_t width = 800, const uint16_t height = 600);
}
