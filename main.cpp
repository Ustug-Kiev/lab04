#include <iostream>
#include <math.h>
#include <conio.h>
#include <string.h>
#include <vector>
#include<windows.h>
#pragma hdrstop
#include "test.h"
#include "svg.h"
#include <sstream>
#include <string>
#include <curl/curl.h>

using namespace std;


vector <double>
input_numbers(istream& in, size_t count)
{
    vector <double> result(count);
    for (size_t i=0; i<count; i++)
    {
        cerr << i << ")";
        in >> result[i];
    }
    return result;
}




void show_gistogram (const auto bins, size_t number_count)
{
    size_t screen_width;
    cerr << "Enter screen width" << endl;
    cin >> screen_width;
    while (screen_width < 7 || screen_width > 80000 || screen_width < number_count/3)
    {
        if (screen_width < 7)
        {
            cerr << "Too less screen width" << endl;
        }
        if (screen_width >80)
        {
            cerr << "Too large screen width" << endl;
        }
        if (screen_width < number_count/3)
        {
            cerr << "its nessesary to be more then 1/3 of number count" << endl;
        }
        cerr << endl;
        cin >> screen_width;

    }


    const size_t max_aster = screen_width - 3 -1;
    size_t max_bin = bins[0];
    for (size_t bin:bins)
    {
        if (max_bin<bin)
        {
            max_bin = bin;
        }
    }



    for (size_t bin : bins)
    {
        size_t hei = bin;
        // нужно ли масштабировать
        if (max_bin > max_aster)
        {
            hei = max_aster * (static_cast<double> (bin) / max_bin);
        }
        if(bin<100)
        {
            cout << " ";
        }
        if (bin<10)
        {
            cout << " ";
        }
        cout << bin << "|";
        for (size_t i = 0; i < hei; i++)
        {
            cout << "*";
        }
        cout << endl;
    }

}

vector<double>
make_histogram(Input data)
{
    double min,max;
    find_minmax(data.numbers,min,max);
    vector<double> bins(data.bin_count,0);
    double bin_size = (max - min) / data.bin_count;
    for(size_t i=0; i<data.numbers.size(); i++)
    {
        bool found=false;
        for(size_t j=0; j<(data.bin_count-1) && !found; j++)
        {
            auto lo = min + j*bin_size;
            auto hi = min + (j + 1)*bin_size;
            if((lo <= data.numbers[i]) && (data.numbers[i]<hi))
            {
                bins[j]++;
                found =true;
            }
        }
        if(!found)
        {
            bins[data.bin_count-1]++;
        }
    }
    return bins;
}


Input
read_input(istream& in, bool promt)
 {
    Input data;

    if (promt)
    {
        cerr << "Enter number count: ";
    }
    size_t number_count;
    in >> number_count;

    if (promt)
    {
        cerr << "Enter numbers: ";
    }

    data.numbers = input_numbers(in, number_count);

    // ...
    if (promt)
    {
        cerr << "Enter bin count: ";
    }

    in >> data.bin_count;


    return data;
}

size_t
write_data(void* items, size_t item_size, size_t item_count, void* ctx)
 {
    size_t data_size = item_size * item_count;
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    buffer->write(reinterpret_cast<char*>(items), data_size);
    return data_size;
}

Input
download(const string& address)
{
    curl_global_init(CURL_GLOBAL_ALL);
    stringstream buffer;
    CURL *curl = curl_easy_init();
    if(curl)
    {
        double total;

        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
            exit(1);
        }

        curl_easy_cleanup(curl);
        curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &total);
        cerr << "total time = " << total << endl;

    }

    return read_input(buffer, false);
}




int main(int argc, char* argv[])
{
    Input input;


    if (argc > 1)
    {
        input = download(argv[1]);
    }
    else
    {
        input = read_input(cin, true);
    }




    const auto bins = make_histogram(input);
    show_histogram_svg(bins);


    return 0;
}
