#include <iostream>
#include <vector>
#include "text.h"

using namespace std;

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
