#include <iostream>
#include <vector>

using namespace std;

 struct Input {
        vector<double> numbers;
        size_t bin_count{};
        size_t number_count;

};

Input
input_data(){

    setlocale(LC_ALL, "RUSSIAN");

    size_t number_count;
    cerr << "¬ведите количество чисел: ";
    cin >> number_count;

    Input in;

    in.numbers.resize(number_count);

    cerr << "¬ведите через пробел элементы массива: ";

    vector<double> numbers(number_count);
    for (size_t i = 0; i < number_count; i++) {
        cin >> in.numbers[i];
    }

    size_t bin_count;
    cerr << "¬ведите количество корзин: ";
    cin >> in.bin_count;

    return in;
};

void
find_minmax(const vector<double>& numbers, double& min, double& max) {
    min = numbers[0];
    max = numbers[0];

    for (double x : numbers) {
        if (x < min) {
            min = x;
        }
        else if (x > max) {
            max = x;
        }
    }
}

auto
make_histogram(const vector<double> numbers, size_t bin_count){

    vector <size_t> bins(bin_count);
    double min, max;
    find_minmax(numbers, min, max);

    double bin_size = (max - min) / bin_count;

    for (size_t i = 0; i < numbers.size(); i++) {
        bool found = false;
        for (size_t j = 0; (j < bin_count - 1) && !found; j++) {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;
            if ((lo <= numbers[i]) && (numbers[i] < hi)) {
                bins[j]++;
                found = true;
            }
        }

        if (!found) {
            bins[bin_count - 1]++;
        }
    }

    return bins;
}

void
show_histogram_text(const vector<size_t> bins, size_t number_count, size_t bin_count){

    for (size_t i = 0; i < bin_count; i++){

        if (bins[i] < 100) cout << " ";
        if (bins[i] < 10) cout << " ";
        cout << bins[i] << "|";

        for(size_t j=0; j < bins[i]; j++){
                    cout << "*";
        }
         cout<<endl;
    }
}


int
main(){

    auto in = input_data();
    auto bins = make_histogram(in.numbers, in.bin_count);
    show_histogram_text(bins, in.number_count, in.bin_count);

    return 0;
}
