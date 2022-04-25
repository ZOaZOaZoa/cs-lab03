#include <iostream>
#include <vector>
#include <istream>
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


int main()
{
    //Ввод данных
    Input data;
    data = read_input(cin, 1);

    //Расчет гистограммы
    const auto bins = make_histogramm(data);

    //Вывод гистограммы
    show_histogramm_svg(bins);

    return 0;
}
