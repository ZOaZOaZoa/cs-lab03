#include "histogram.h"

#include <cassert>

//input_check_histogram_width(size_t width, size_t numbers_count)
void test_normal()
{
    bool passed_test = false;
    passed_test = input_check_histogram_width(400, 10);
    assert(passed_test == true);
}

void test_small_width()
{
    bool passed_test = false;
    passed_test = input_check_histogram_width(50, 15);
    assert(passed_test == false);
}

void test_big_width()
{
    bool passed_test = false;
    passed_test = input_check_histogram_width(1500, 60);
    assert(passed_test == false);
}

void test_wrong_ratio()
{
    bool passed_test = false;
    passed_test = input_check_histogram_width(200, 100);
    assert(passed_test == false);
}

//find_minmax(const vector<double>& numbers, double& min, double& max)
void test_positive()
{
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}

void test_negative()
{
    double min = 0;
    double max = 0;
    find_minmax({-2, -1, -3}, min, max);
    assert(min == -3);
    assert(max == -1);
}

void test_equal()
{
    double min = 0;
    double max = 0;
    find_minmax({3, 3, 3}, min, max);
    assert(min == 3);
    assert(max == 3);
}

void test_one_num()
{
    double min = 0;
    double max = 0;
    find_minmax({9}, min, max);
    assert(min == 9);
    assert(max == 9);
}

void test_empty()
{
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    assert(min == 0);
    assert(max == 0);
}


int main()
{
    //input_check_histogram_width()
    test_normal();
    test_small_width();
    test_big_width();

    //find_minmax()
    test_positive();
    test_negative();
    test_equal();
    test_one_num();
    test_empty();
    return 0;
}
