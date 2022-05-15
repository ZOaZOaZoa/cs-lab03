#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg.h"

using namespace std;

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
