#include <math.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include <string>
#include "svg.h"

using namespace std;

void
svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end() {
    cout << "</svg>\n";
}

void
svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>";

}

void
svg_rect(double x, double y, double width, double height, string stroke, string fill){
    cout << "<rect x='"<<x<<"' y='"<<y<<"' width='"<<width<<"' height='"<<height<<"' stroke='"<<stroke<<"' fill='"<<fill<<"' />";

}



void
show_histogram_svg(const vector<size_t>& bins, size_t number_count, size_t bin_count) {
    const auto IMAGE_WIDTH = 400;
    auto IMAGE_HEIGHT = 700;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    const auto MAX_WIDTH = IMAGE_WIDTH-TEXT_WIDTH;

    cerr << "Input IMAGE_HEIGHT: ";
    cin >> IMAGE_HEIGHT;
    if (IMAGE_HEIGHT > 700){
        IMAGE_HEIGHT=IMAGE_HEIGHT;
    }

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);

    double top = 0;

    double max_count = bins[0];
    for (size_t i = 0; i < bins.size(); i++){
        if (bins[i] > max_count)
            max_count = bins[i];
    }

    for (size_t bin : bins) {
        const double bin_width = (IMAGE_WIDTH - TEXT_WIDTH)*(bin/max_count);
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT,"#FFFFFF","#32CD32");
        top += BIN_HEIGHT;
    }

    svg_end();
}


