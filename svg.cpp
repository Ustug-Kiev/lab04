#include "svg.h"


void
svg_begin(double width, double height)
 {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout  << "<svg ";
    cout  << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout  << "viewBox='0 0 " << width << " " << height << "' ";
    cout  << "xmlns='http://www.w3.org/2000/svg'>\n";
}


void
svg_text(double left, double baseline, string text)
{
    cout  << "<text x='" << left << "' y='"<< baseline << "'>"<< text <<"</text>" <<endl;
}

void
svg_end()
{
    cout  << "</svg>\n";
}


void svg_rect(double x, double y, double width, double height,string stroke, string fill){

    cout <<"<rect x='" << x <<"' y='"<< y <<"' width='"<< width <<"' height='"<< height <<"' stroke='"<<stroke<<"' fill='"<<fill<<"' />" <<endl;
}


void
show_histogram_svg(const vector<double> bins)
{
    const auto BLOCK_WIDTH = 10;

    double gistogram_width;
    cerr << "Enter gistogram width : ";
    cin >> gistogram_width;
    while (check(sizeof(bins), gistogram_width) == false)
    {
        cerr << "There is erorr" << endl;
        cin >> gistogram_width;
    }
    double IMAGE_WIDTH;


    IMAGE_WIDTH = gistogram_width;


    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;

    const string stroke = "black";
    const string fill = "#3CB371";
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    for (size_t bin : bins)
    {
        const double bin_width = BLOCK_WIDTH * bin;
        const double text_wid= IMAGE_WIDTH-bin_width-30;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT,"black", "#FFA500");
        top += BIN_HEIGHT;
    }
    svg_text(TEXT_LEFT, TEXT_BASELINE, to_string(bins[0]));
    svg_end();

}

bool check(size_t count, double gistogram_width)
{
    bool f = true;
    if (gistogram_width < 70 || gistogram_width > 800 || gistogram_width< count/3.0 * 10)
    {
        f = false;
    }
    return f;
}
