#ifndef HISTOGRAM_H_INCLUDED
#define HISTOGRAM_H_INCLUDED
#include <vector>
#include <iostream>
#include <sstream>
#include <curl/curl.h>
#include "svg.h"

using namespace std;

struct Input
{
    vector<double> numbers;
    size_t bin_count;
    size_t image_width;
};

void find_minmax(const vector<double>& numbers, double& min, double& max);
vector<size_t> make_histogramm(Input data);
void show_histogramm_text(const vector<size_t>& bins);
Input download(const string& address);
size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx);
vector<double> input_numbers(istream& in, size_t count);
bool input_check_histogram_width(size_t width, size_t numbers_count);
Input read_input(istream& in, bool prompt);

#endif // HISTOGRAM_H_INCLUDED
