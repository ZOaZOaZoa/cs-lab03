#ifndef HISTOGRAM_H_INCLUDED
#define HISTOGRAM_H_INCLUDED
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void find_minmax(const vector<double>& numbers, double& min, double& max);
void svg_begin(double width, double height);
void svg_text(double left, double baseline, string text);
void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black");
void svg_end();
void show_histogramm_svg(const vector<size_t>& bins);

#endif // HISTOGRAM_H_INCLUDED
