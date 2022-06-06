#ifndef SVG_H_INCLUDED
#define SVG_H_INCLUDED
#include <vector>
#include <string>
#include <iostream>
using namespace std;
void svg_begin(double width, double height);
#include <iostream>
#include <sstream>
#include <vector>
#include <windows.h>
using namespace std;
void svg_begin(double width, double height);
string make_info_text(char T = '1');
size_t check_size(size_t text_size);
void svg_text(double left, double baseline, string text);
void svg_rect(double x, double y, double width, double height,string stroke, string fill);
void svg_end();
void show_histogram_svg(const vector<double>& bins);

struct Input
{
vector<double> numbers;
size_t bin_count;
};

void find_minmax(const vector<double> &numbers,double &min,double &max);

bool check(size_t count, double gistogram_width);



#endif // SVG_H_INCLUDED








