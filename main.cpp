#include <iostream>
#include <vector>

using namespace std;

int main(){

    setlocale(LC_ALL, "RUSSIAN");

    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;


    size_t number_count; //количество чисел в массиве

    cerr << "¬ведите количество чисел: ";
    cin >> number_count;


    vector<double> numbers(number_count); //вектор из этих чисел

    cerr << "¬ведите через пробел элементы массива: ";

    for (double i = 0; i < number_count; i++){
        cin >> numbers[i];
    }

    //////////////////////////////////

    size_t bin_count; // количество корзин

    cerr << " ¬ведите количество корзин:";
    cin >> bin_count;
    cerr << endl;


    vector<size_t> bins(bin_count); // массив из кол-ва элементов в столбцах


    double min = numbers[0];
    double max = numbers[0];

    for (double x : numbers) {
        if (x < min) {
            min = x;
        }
        else if (x > max) {
            max = x;
        }
    }

    double bin_size = (max - min) / bin_count; // размер корзины

    for (size_t i = 0; i < number_count; i++) {
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




    size_t max_count = bins[0]; // количество элементов в большем столбце
    int k = 0;
    for (auto i = 0; i < bin_count; i++){
       if (bins[i] >= max_count){
            max_count = bins[i];
            k=i;
       }
    }

    float procent;

    for (size_t i = 0; i < bin_count; i++){

        int procent =((float)bins[i] / number_count)*100;

        if (bins[i] < 100) cout << " ";
        if (bins[i] < 10) cout << " ";
        cout << procent << "%|";

        size_t height = 0;


        if (bins[i] < max_count){//маштабирование
            size_t height = 76 * (static_cast<double>(bins[i]) / max_count);

            for(size_t j=0; j < height; j++){
                    cout << "*";
            }
        }

        if(i == k)
        {
            for(size_t j=0; j < (76*1.0); j++)
            {

                cout<<"*";
            }
        }
         cout<<endl;
    }


    return 0;
}
