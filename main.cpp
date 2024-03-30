#include <iostream>
#include <vector>
#include <curl/curl.h>
#include "histogram.h"
#include "text.h"
#include "svg.h"
#include <sstream>
#include <string>



using namespace std;

 struct Input {
        vector<double> numbers;
        size_t bin_count{};
        size_t number_count;

};

Input
input_data(istream& in, bool prompt){  //& тк нельз€ скопировать поток ввода   istream управл€ет извлечением объектов

    setlocale(LC_ALL, "RUSSIAN");

    Input in2;

    //bool prompt = true;
    if (prompt) cerr << "¬ведите количество чисел: ";
    in >> in2.number_count;



    in2.numbers.resize(in2.number_count);

    if (prompt) cerr << "¬ведите через пробел элементы массива: ";

    vector<double> numbers(in2.number_count);
    for (size_t i = 0; i < in2.number_count; i++) {
        in >> in2.numbers[i];
    }

    if (prompt) cerr << "¬ведите количество корзин: ";
    in >> in2.bin_count;

    return in2;
};

size_t
write_data(void* items, size_t item_size, size_t item_count, void* ctx) {

    size_t data_size = item_size * item_count;

    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    buffer->write(reinterpret_cast<const char*>(items), data_size);

    return data_size;
}


Input
download(const string& address) {
    stringstream buffer;

    CURL* curl = curl_easy_init();

    if(curl) {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

        res = curl_easy_perform(curl);

        if(!res){
            curl_off_t speed;
            res = curl_easy_getinfo(curl, CURLINFO_SPEED_DOWNLOAD_T, &speed);
            if(!res){
                cerr << "Download speed " << speed << endl;
            }
        }

        if(res != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            exit(1);
        }
        curl_easy_cleanup(curl);
    }

    return input_data(buffer, false);
}


int
main(int argc, char* argv[]) {

    Input input;

    if (argc > 1) {
        input = download(argv[1]);
    } else {
        input = input_data(cin, true);
    }

    const auto bins = make_histogram(input.numbers, input.bin_count);
    show_histogram_text(bins, input.number_count, input.bin_count);
    return 0;
}


    //curl_global_init(CURL_GLOBAL_ALL);
    //auto in = input_data(cin);
    //auto bins = make_histogram(in.numbers, in.bin_count);
    //show_histogram_text(bins, in.number_count, in.bin_count);

// cin - переменна€ котора€ представл€ет поток
