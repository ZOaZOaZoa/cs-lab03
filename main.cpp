#include <iostream>
#include <vector>
#include "histogram.h"

vector<double> input_numbers(size_t count)
{
    vector<double> result(count);
    for(size_t i = 0; i < count; i++)
    {
        cin >> result[i];
    }
    return result;
}

vector<size_t> make_histogramm(const vector<double>& numbers, size_t bin_count)
{
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



int main()
{
    //Ввод данных
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;
    if(number_count == 0)
    {
        cerr << "There is nothing to compute\n";
        return 0;
    }


    cerr << "Enter numbers: ";
    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    cerr << "Enter bin count: ";
    cin >> bin_count;


    //Расчет гистограммы
    const auto bins = make_histogramm(numbers, bin_count);

    //Вывод гистограммы
    show_histogramm_svg(bins);

    return 0;
}
