#ifndef SVG_H_INCLUDED
#define SVG_H_INCLUDED
#include <iostream>
#include <vector>
#include <string>

using namespace std;

    //Input check
    const auto MIN_IMAGE_WIDTH = 70;
    const auto MAX_IMAGE_WIDTH = 800;
    const auto MIN_NUMBERS_RATIO = 1/3;
    //Histogramm print
    //const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    const auto RECT_STROKE = "red";
    const auto RECT_FILL = "#ffcccc";

bool input_check_histogram_width(size_t width, size_t numbers_count);
void svg_begin(double width, double height);
void svg_text(double left, double baseline, string text);
void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black");
void svg_end();
void show_histogramm_svg(const vector<size_t>& bins, size_t image_width);

#endif // SVG_H_INCLUDED
