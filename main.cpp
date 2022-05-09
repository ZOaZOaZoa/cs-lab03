#include <iostream>
#include <vector>
#include <istream>
#include <sstream>
#include <curl/curl.h>
#include "histogram.h"
#include "svg.h"

using namespace std;

vector<double> input_numbers(istream& in, size_t count)
{
    vector<double> result(count);
    for(size_t i = 0; i < count; i++)
    {
        in >> result[i];
    }
    return result;
}

Input read_input(istream& in, bool prompt)
{
    Input data;

    size_t number_count;
    if (prompt)
    {
        cerr << "Enter number count: ";
    }
    in >> number_count;

    if(prompt)
    {
        cerr << "Enter numbers: ";
    }
    data.numbers = input_numbers(in, number_count);

    if(prompt)
    {
        cerr << "Enter bin count: ";
    }
    in >> data.bin_count;

    return data;
}


int main(int argc, char* argv[])
{
    if(argc > 1)
    {
        curl_global_init(CURL_GLOBAL_ALL);
        CURL *curl = curl_easy_init();
        if(curl) {
          CURLcode res;
          curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
          res = curl_easy_perform(curl);
          curl_easy_cleanup(curl);
        }
        return 0;
    }



    const auto data = read_input(cin, 1);
    const auto bins = make_histogramm(data);
    show_histogramm_svg(bins);

    return 0;
}
