#include "svg.h"




string get_system_info()
{
    string result;
    const size_t MAX_LEN = 256;
    char str_info[MAX_LEN];

    DWORD info = GetVersion();
    DWORD mask =0x0000ffff;
    DWORD version = info & mask;
    DWORD version_major = version & 0x00ff;
    DWORD version_minor = version & 0xff00;
    sprintf(str_info, "Windows v%u.%u", version_major, version_minor);
    result = str_info;
    if((info & 0x8000'0000) == 0)
    {
        DWORD build = info >> 16;
        sprintf(str_info, " (build %u)\n", build);
        result += str_info;
    }

    return result;
}

string get_computer_name()
{
    DWORD max_len = MAX_COMPUTERNAME_LENGTH + 1;
    char computer_name[max_len];
    GetComputerNameA(computer_name, &max_len);
    string result = computer_name;

    return result;
}

void svg_begin(double width, double height)
{
    cout << "<?xml version = '1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewbox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_text(double left, double baseline, string text)
{
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>\n";
}

void svg_rect(double x, double y, double width, double height, string stroke, string fill)
{
    //<rect x='0' y='0' width='100' height='200' />
    cout << "<rect x='" << x << "' y='" << y
        << "' width='" << width << "' height='" << height
        << "' stroke='" << stroke << "' fill='" << fill << "'/>\n";
}

void svg_end()
{
    cout << "</svg>\n";
}

void show_histogramm_svg(const vector<size_t>& bins, size_t image_width)
{
    size_t max_bin = bins[0];
    for (size_t bin : bins)
    {
        if(bin > max_bin)
        {
            max_bin = bin;
        }
    }
    auto max_bin_width = BLOCK_WIDTH * max_bin;
    const auto MAX_BIN_WIDTH = image_width - TEXT_WIDTH;

    svg_begin(image_width, IMAGE_HEIGHT);

    double top = 0;
    for(size_t bin : bins)
    {
        double bin_width = BLOCK_WIDTH * bin;
        if(MAX_BIN_WIDTH < max_bin_width)
        {
            bin_width = static_cast<double>(bin_width) / max_bin_width * MAX_BIN_WIDTH;
        }
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, RECT_STROKE, RECT_FILL);
        top += BIN_HEIGHT;
    }

    string system_info = get_system_info();
    string computer_name = get_computer_name();
    svg_text(SYS_INFO_LEFT, BIN_HEIGHT * bins.size() + TEXT_BASELINE, system_info);
    svg_text(SYS_INFO_LEFT, BIN_HEIGHT * bins.size() + 2 * TEXT_BASELINE, computer_name);


    svg_end();
}
