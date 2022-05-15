#include "histogram.h"

using namespace std;

void find_minmax(const vector<double>& numbers, double& min, double& max)
{
    if(numbers.size() == 0)
    {
        return;
    }

    min = max = numbers[0];
    for(double number : numbers)
    {
        if (min > number)
        {
            min = number;
        }
        if (max < number)
        {
            max = number;
        }
    }
}


vector<size_t> make_histogramm(Input data)
{
    const vector<double>& numbers = data.numbers;
    size_t& bin_count = data.bin_count;

    double min, max;
    find_minmax(numbers, min, max);

    vector<size_t> bins(bin_count, 0);
    double bin_size = (max - min) / bin_count;
    for (size_t i = 0; i < numbers.size(); i++)
    {
        bool found = false;
        for(size_t j = 0; j < (bin_count - 1) && !found; j++)
        {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;
            if (lo <= numbers[i] && numbers[i] < hi)
            {
                bins[j]++;
                found = true;
            }
        }
        if (!found)
        {
            bins[bin_count - 1]++;
        }
    }
    return bins;
}


void show_histogramm_text(const vector<size_t>& bins)
{
    size_t SCREEN_WIDTH = 80;
    const size_t max_asterix = SCREEN_WIDTH - 3 - 1;

    size_t max_bin = bins[0];
    for (size_t bin: bins)
    {
        if (max_bin < bin)
        {
            max_bin = bin;
        }
    }

    for(size_t bin: bins)
    {
        size_t height = bin;

        //Проверка, нужно ли масштабировать столбцы
        if (max_bin > max_asterix)
        {
            height = max_asterix * (static_cast<double>(bin) / max_bin);
        }

        if (bin < 100)
        {
            cout << ' ';
        }
        if (bin < 10)
        {
            cout << ' ';
        }
        cout << bin << "|";
        for (size_t i = 0; i < height; i++)
        {
            cout << "*";
        }
        cout << endl;
    }
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
          cerr << "Time spent to load: " << total_time << " seconds\n";
      }
      curl_easy_cleanup(curl);
    }

    return read_input(buffer, false);
}

vector<double> input_numbers(istream& in, size_t count)
{
    vector<double> result(count);
    for(size_t i = 0; i < count; i++)
    {
        in >> result[i];
    }
    return result;
}

bool input_check_histogram_width(size_t width, size_t numbers_count)
{
    if( (MIN_IMAGE_WIDTH <= width && width <= MAX_IMAGE_WIDTH) && width > MIN_NUMBERS_RATIO * numbers_count * BLOCK_WIDTH)
    {
        return true;
    }
    else
    {
        return false;
    }
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


