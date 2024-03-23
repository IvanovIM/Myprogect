#include <iostream>
#include <vector>

#include "histogram.h"
#include "text.h"
#include "svg.h"


using namespace std;

 struct Input {
        vector<double> numbers;
        size_t bin_count{};
        size_t number_count;

};

Input
input_data(istream& in){  //& тк нельз€ скопировать поток ввода   istream управл€ет извлечением объектов

    setlocale(LC_ALL, "RUSSIAN");

    Input in2;

    cerr << "¬ведите количество чисел: ";
    in >> in2.number_count;



    in2.numbers.resize(in2.number_count);

    cerr << "¬ведите через пробел элементы массива: ";

    vector<double> numbers(in2.number_count);
    for (size_t i = 0; i < in2.number_count; i++) {
        in >> in2.numbers[i];
    }

    size_t bin_count;
    cerr << "¬ведите количество корзин: ";
    in >> in2.bin_count;

    return in2;
};


int
main(){

    auto in = input_data(cin);
    auto bins = make_histogram(in.numbers, in.bin_count);
    show_histogram_text(bins, in.number_count, in.bin_count);

    return 0;
}


// cin - переменна€ котора€ представл€ет поток
