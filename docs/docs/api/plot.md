# Plot
`Plot` is class responsible for drawing linear plots.

## addData
Function to add data to plot.
### Version with two vectors
```cpp
void addData(const std::vector<double>& x, const std::vector<double>& y)
```

**Parameters:**

- `x` (`const std::vector<double>&`): values on x axis 
- `y` (`const std::vector<double>&`): values on y axis 

**Przykład:**

```cpp
yapl::Plot plt;
std::vector<double> x = {1, 2, 3};
std::vector<double> y = {1, 2, 3};
plt.addData(x, y);
```

### Version with vector of pairs
```cpp
void addData(const std::vector<std::pair<double, double>>& data)
```

**Parameters:**

- `data` (`const std::vector<std::pair<double, double>>&`): vector of `<X,Y>`

**Przykład:**

```cpp
yapl::Plot plt;
std::vector<std::pair<double, double>> data = {{1, 1}, {2, 2}, {3, 3}};
plt.addData(data);
```


## xLabel
Function to set x label.
```cpp
void xLabel(const std::string& label)
```

**Parameters:**

- `label` (`const std::string&`): label to be displayed below x axis

**Przykład:**

```cpp
yapl::Plot plt;
plt.xLabel("Timestamps");
```


## yLabel
Function to set y label.
```cpp
void yLabel(const std::string& label)
```

**Parameters:**

- `label` (`const std::string&`): label to be displayed next to y axis

**Przykład:**

```cpp
yapl::Plot plt;
plt.yLabel("Values");
```


## title
Function to set title.
```cpp
void title(const std::string& label)
```

**Parameters:**

- `label` (`const std::string&`): title to be displayed above plot

**Przykład:**

```cpp
yapl::Plot plt;
plt.title("Plot title");
```


## legend
Function to set legend.
```cpp
void legend(const std::vector<std::string>& legend, 
    const LegendPosition legend_position = LegendPosition::TOP_RIGHT)
```

**Parameters:**

- `legend` (`const std::vector<std::string>&`): vector of strings displayed with proper colors determining legend for plot. Legend items count must be equal to datasets count.
- `legend_position` (`const LegendPosition`): legend position 

**Przykład:**

```cpp
yapl::Plot plt;
plt.addData({{1, 1}, {2, 2}, {3, 3}});
plt.addData({{4, 4}, {5, 5}, {6, 6}});
plt.legend({"first set", "second set"});
```


## save
Function to save plot as image.
```cpp
void save(const std::filesystem::path& path, const uint16_t width = 800, const uint16_t height = 600)
```

**Parameters:**

- `path` (`const std::filesystem::path&`): path under which plot will be saved.
- `width` (`const uint16_t`): pixel number terermining width, default value is 800px.
- `height` (`const uint16_t`): pixel number terermining height, default value is 600px.

**Przykład:**

```cpp
yapl::Plot plt;
plt.addData({{1, 1}, {2, 2}, {3, 3}});
plt.save("./example.png");
```


## xLim
Function to set x axis limits.
```cpp
void xLim(const double lower_bound, const double higher_bound)
```

**Parameters:**

- `lower_bound` (`const double`): min x value to be visible on plot.
- `higher_bound` (`const double`): max x value to be visible on plot.

**Przykład:**

```cpp
yapl::Plot plt;
plt.addData({{1, 1}, {2, 2}, {3, 3}});
plt.xLim(1.5, 3.5);
```


## yLim
Function to set y axis limits.
```cpp
void yLim(const double lower_bound, const double higher_bound)
```

**Parameters:**

- `lower_bound` (`const double`): min y value to be visible on plot.
- `higher_bound` (`const double`): max y value to be visible on plot.

**Przykład:**

```cpp
yapl::Plot plt;
plt.addData({{1, 1}, {2, 2}, {3, 3}});
plt.yLim(1.5, 3.5);
```


## grid
Function to configure grid.
```cpp
void grid(const bool state)
```

**Parameters:**

- `state` (`const bool`): when set to true, grid is created, when set to false no grid is created.

**Przykład:**

```cpp
yapl::Plot plt;
plt.addData({{1, 1}, {2, 2}, {3, 3}});
plt.grid(true);
```


## setGridColor
Function to set grid color.
```cpp
void setGridColor(Color grid_color)
```

**Parameters:**

- `grid_color` (`Color`): desired color of grid.

**Przykład:**

```cpp
yapl::Plot plt;
plt.addData({{1, 1}, {2, 2}, {3, 3}});
plt.grid(true);
plt.setGridColor({.r = 0.5, .g = 0.2, .b = 0.1});
```


## setLabelMaker
Function to set label maker function defining how user want them to look like.
```cpp
void setLabelMaker(std::function<std::string(double)> label_maker)
```

**Parameters:**

- `label_maker` (`std::function<std::string(double)>`): function like std::string label_maker(double) which makes labels.

**Przykład:**

```cpp
yapl::Plot plt;
plt.addData({{1, 1}, {2, 2}, {3, 3}});
plt.setLabelMaker([](double val) -> std::string {
    return "x: " + std::to_string(val);
});
```


## setColorMaker
Function to set color maker function defining data on plot should be colored
```cpp
void setColorMaker(std::function<Color(double, double)> color_maker)
```

**Parameters:**

- `color_maker` (`std::function<Color(double, double)>`): function like yapl::Color color_maker(double x, double y) generates color based on coordinates.

**Przykład:**

```cpp
yapl::Plot plt;
plt.addData({{1, 1}, {2, 2}, {3, 3}});
plot.setColorMaker([](double x, double y) -> yapl::Color {
    if (y >= 3) return yapl::Color(1.0, 0.0, 0.0);
    if (y >= 2) return yapl::Color(1.0, 0.8, 0.0);
    return yapl::Color(0.0, 0.0, 1.0);
});
```


## setXTickSpacing
Function to set spacing between ticks on X axis.
```cpp
void setXTickSpacing(const double tick_spacing)
```

**Parameters:**

- `tick_spacing` (`const double`): spacing between ticks on X axis, must be greater than 0.0

**Przykład:**

```cpp
yapl::Plot plt;
plt.addData({{1, 1}, {2, 2}, {3, 3}});
plt.setXTickSpacing(1.0);
```


## setYTickSpacing
Function to set spacing between ticks on Y axis.
```cpp
void setYTickSpacing(const double tick_spacing)
```

**Parameters:**

- `tick_spacing` (`const double`): spacing between ticks on Y axis, must be greater than 0.0

**Przykład:**

```cpp
yapl::Plot plt;
plt.addData({{1, 1}, {2, 2}, {3, 3}});
plt.setYTickSpacing(1.0);
```