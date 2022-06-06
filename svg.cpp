#include "svg.h"
#define INFO_BUFFER_SIZE 50
#include "SVG.h"


void svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_text(double left, double baseline, string text)
{
    //cout << "<text x='" << left << "' y='35'>anything you want</text>";
    cout << "<text x='" << left << "' y='"<< baseline << "'>"<< text <<"</text>" <<endl;

}
string
make_info_text(char T) {
    stringstream buffer;
    if(T == 1){
        DWORD info = GetVersion();
        DWORD mask = 0x0000ffff;
        DWORD version = info & mask;
        DWORD platform = info >> 16;
        DWORD version_minor = version >> 8;
        DWORD version_major = version & 0x0000ff;
        printf("Windows v%u.%u", version_major, version_minor);
        if ((info & 0x40000000) == 0) {
            DWORD build = platform;
            printf(" (build %u)\n", build);
            buffer<<"Windows v" <<version_major<<"."<<version_minor<<" (build "<<build<<")";
        }
    }
       else if(T == 2){
        char  infoBuf[INFO_BUFFER_SIZE];
        DWORD  bufCharCount = INFO_BUFFER_SIZE;
        GetComputerNameA(infoBuf, &bufCharCount);
        printf("Computer name: %s", infoBuf);
        buffer << "Computer name: " << infoBuf;
    }
    return buffer.str();
}

void svg_rect(double x, double y, double width, double height,string stroke, string fill){
    //cout<<"<rect x='0' y='0' width='100' height='200' />";
    //cout<<"<rect x='50' y='0' width='30' height='30' stroke='red' fill='#ffeeee'/>";
    cout<<"<rect x='" << x <<"' y='"<< y <<"' width='"<< width <<"' height='"<< height <<"' stroke='"<<stroke<<"' fill='"<<fill<<"' />" <<endl;
}

void svg_end() {
    cout << "</svg>\n";
}


/*void
show_histogram_svg(const vector<double>& bins)
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

}*/

void show_histogram_svg(const vector<double>& bins) {


    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 370;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 0;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    const string stroke = "black";
    const string fill = "#3CB371";
    const auto MAX_ASTERISK = IMAGE_WIDTH - TEXT_WIDTH;
    size_t max_count = 0;
    for (size_t bin : bins)
    {
        if (bin * BLOCK_WIDTH > max_count)
        {
            max_count = bin * BLOCK_WIDTH;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;
    svg_begin(IMAGE_WIDTH,IMAGE_HEIGHT);
    double top = 0;
    for (size_t bin : bins)
    {
        size_t bin_scale = bin;
        if (scaling_needed)
        {
            const double scaling_factor = (double)MAX_ASTERISK / max_count;
            bin_scale = (size_t)(bin * scaling_factor);
        }

        const double bin_width = BLOCK_WIDTH * bin_scale;

        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT,"black", "#3CB371");
        top += BIN_HEIGHT;


    }
    svg_text(0, top + TEXT_BASELINE+30, make_info_text(1));
    svg_text(0, top + TEXT_BASELINE+50, make_info_text(2));
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
