#include <iostream>
#include <vector>
#include <istream>
#include <sstream>
#include <curl/curl.h>
#include <windows.h>
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

    const size_t MAX_TRIES = 100;
    size_t try_counter = 0;
    bool passed_test = false;
    if(prompt)
    {
        cerr << "Enter image width: ";
    }
    do
    {
        in >> data.image_width;
        passed_test = input_check_histogram_width(data.image_width, number_count);

        if(!passed_test && prompt)
        {
            cerr << "Image width should be in range of 70 and 800 and be greater than 1/3 of numbers count multiplyed by 20\n";
        }

        if(!passed_test && try_counter > MAX_TRIES)
        {
            exit(1);
        }
        try_counter++;
    } while(!passed_test);

    return data;
}

size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx)
{
    size_t data_size = item_size * item_count;

    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    buffer->write(reinterpret_cast<char*>(items), data_size);

    return data_size;
}


Input download(const string& address)
{
    stringstream buffer;

    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl = curl_easy_init();
    if(curl)
    {
      CURLcode res;
      curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
      res = curl_easy_perform(curl);
      if (res != CURLE_OK)
      {
          cerr << "Error: " << curl_easy_strerror(res);
          exit(1);
      }
      double total_time;
      res = curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &total_time);
      if(res == CURLE_OK)
      {
          cerr << "Time spent: " << total_time << " seconds\n";
      }
      curl_easy_cleanup(curl);
    }

    return read_input(buffer, false);
}


int main(int argc, char* argv[])
{

    Input input;
    if(argc > 1)
    {
        input = download(argv[1]);
    }
    else
    {
        input = read_input(cin, true);
    }

    const auto bins = make_histogramm(input);
    show_histogramm_svg(bins, input.image_width);

    return 0;
}
