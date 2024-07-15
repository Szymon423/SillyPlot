# Examples

## Basic plot

```cpp
#include "yapl.hpp"
#include <iostream>

int main() {
    try {
        yapl::Plot plot;
        plot.addData({10, 20, 30, 40, 50}, {100, 200, 300, 400, 500});
        plot.grid(true);
        plot.xLabel("X value");
        plot.yLabel("Y value");
        plot.title("Yet Another Plot Library");
        plot.save("basic_plot.png", 800, 600);
    }
    catch (const yapl::Exception& e) {
        std::cout << "Caught error during plot generation" << std::endl;
    }
    return 0;
}
```

## Custom `X` labels

```cpp
#include "yapl.hpp"
#include <iostream>

int main() {
    try {
        yapl::Plot plot;
        plot.addData({10, 20, 30, 40, 50}, {100, 200, 300, 400, 500});
        plot.grid(true);
        plot.xLabel("X value");
        plot.yLabel("Y value");
        plot.title("Yet Another Plot Library");
        plot.setLabelMaker([](double val) -> std::string {
            return "X: " + std::to_string(val);
        });
        plot.save("/YAPL/img/test/example_plot.png", 800, 600);
    }
    catch (const yapl::Exception& e) {
        std::cout << "Caught error during plot generation" << std::endl;
    }
    return 0;
}
```

## Coloring

```cpp
#include "yapl.hpp"
#include <iostream>

int main() {
    try {
        yapl::Plot plot;
        plot.addData({10, 20, 30, 40, 50}, {100, 200, 300, 400, 500});
        plot.grid(true);
        plot.setGridColor({.r = 1.0, .g = 0.5, .b = 0.7});
        plot.xLabel("X value");
        plot.yLabel("Y value");
        plot.title("Yet Another Plot Library");
        plot.save("basic_plot.png", 800, 600);
    }
    catch (const yapl::Exception& e) {
        std::cout << "Caught error during plot generation" << std::endl;
    }
    return 0;
}
```

## Legend

```cpp
#include "yapl.hpp"
#include <iostream>

int main() {
    try {
        yapl::Plot plot;
        plot.addData({10, 20, 30, 40, 50}, {100, 200, 300, 400, 500});
        plot.grid(true);
        plot.xLabel("X value");
        plot.yLabel("Y value");
        plot.title("Yet Another Plot Library");
        plot.legend({"My data"}, LegendPosition::BOTTOM_RIGHT);
        plot.save("basic_plot.png", 800, 600);
    }
    catch (const yapl::Exception& e) {
        std::cout << "Caught error during plot generation" << std::endl;
    }
    return 0;
}
```