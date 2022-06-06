#include <iostream>
#include <vector>
#include <math.h>
#include <sstream>
#include <string>
#include "svg.h"

#include <curl/curl.h>
#include <ctime>
#include <windows.h>
#pragma once
using namespace std;

vector<double>
input_numbers( istream& in,size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        in >> result[i];
    }
    return result;
}

vector<double>
make_histogram(Input data,size_t nowbins,bool flag)
{
    if(flag)
    {
    double min,max;
    find_minmax(data.numbers,min,max);
    vector<double> bins(nowbins,0);
    double bin_size = (max - min) / nowbins;
    for(size_t i=0; i<data.numbers.size(); i++)
    {
        bool found=false;
        for(size_t j=0; j<(nowbins-1) && !found; j++)
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
            bins[nowbins-1]++;
        }
    }
    return bins;
    }
    else{
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
}

Input
read_input(istream& in,bool prompt) {
    Input data;
    if(prompt)
    cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;

    if(prompt)
    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in,number_count);

    if(prompt)
    cerr <<"Enter bin count:";
    in >> data.bin_count;

    return data;
}


void
show_histogram_text(const vector<double>bins)
{
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

    size_t max_bin = bins[0];
    for(size_t bin:bins)
    {
        if(max_bin<bin)
        {
            max_bin=bin;
        }
    }


    for(size_t bin:bins)
    {
        size_t height = bin;

        if (height > MAX_ASTERISK)
        {
            height = MAX_ASTERISK * (static_cast<double>(bin) /max_bin);
        }
        if(bin<100)
            for(size_t i=0; i<(MAX_ASTERISK-bin); i++)
            {
                cout<<" ";
            }
        for(size_t i=0; i< height; i++)
        {
            cout<<"*";

        }

        cout <<"|" << bin;
        cout << endl;
    }
}
size_t
write_data(void* items, size_t item_size, size_t item_count, void* ctx) {
    size_t data_size = item_size * item_count;
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    buffer->write(reinterpret_cast<char*>(items), data_size);
    return data_size;
}

Input
download(const string& address)
{
    stringstream buffer;
    CURL *curl = curl_easy_init();
    if(curl)
    {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
                    exit(1);
        }

        curl_easy_cleanup(curl);
    }

    return read_input(buffer, false);
}

int main(int argc, char* argv[])
{
    Input input;



    curl_global_init(CURL_GLOBAL_ALL);
    size_t newbins;
    bool flag;
    for(size_t i =0; i<argc ; i++)
    {
        if (strstr(argv[i], "-bins"))
        {
            newbins=i+1;
            if((argc - newbins) < 2 )
            {
                flag=false;
                cerr<<" No bins";
                return 0;
            }
            break;
        }
    }
    size_t nowbins = atoi(argv[newbins]);
    if (argc > 1)
    {
        size_t index;
        if(newbins==2)
        {
            flag=true;
            index=3;

        }
        else
        {
            index=1;
        }
        input = download(argv[index]);
    }
    else
    {
        input = read_input(cin, true);
    }


     const auto bins = make_histogram(input,nowbins,flag);

    show_histogram_svg(bins);
    return 0;
}

