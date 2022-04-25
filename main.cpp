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

Input read_input(istream& in)
{
    Input data;

    size_t number_count;
    cerr << "Enter number count: ";
    in >> number_count;

    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    cerr << "Enter bin count: ";
    in >> data.bin_count;

    return data;
}


int main()
{
    //Ввод данных
    Input data;
    data = read_input(cin);



    //Расчет гистограммы
    const auto bins = make_histogramm(data);

    //Вывод гистограммы
    show_histogramm_svg(bins);

    return 0;
}
