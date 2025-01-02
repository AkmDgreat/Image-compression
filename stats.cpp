
#include "stats.h"
// #include <cmath>
using namespace std;

// stats::stats(PNG& im) {
//     long topRectSum_r = 0;
//     long topRectSum_b = 0;
//     long topRectSum_g = 0;

//     long leftRectSum_r = 0;
//     long leftRectSum_b = 0;
//     long leftRectSum_g = 0;

//     long topLeftRectSum_r = 0;
//     long topLeftRectSum_b = 0;
//     long topLeftRectSum_g = 0;

//     long topRectSum_r_sq = 0;
//     long topRectSum_b_sq = 0;
//     long topRectSum_g_sq = 0;

//     long leftRectSum_r_sq = 0;
//     long leftRectSum_b_sq = 0;
//     long leftRectSum_g_sq = 0;

//     long topLeftRectSum_r_sq = 0;
//     long topLeftRectSum_b_sq = 0;
//     long topLeftRectSum_g_sq = 0;

//     int imageH = (int) im.height();
//     int imageW = (int) im.width();

//     sumRed.resize(imageH, vector<long>(imageW, 0));
//     sumGreen.resize(imageH, vector<long>(imageW, 0));
//     sumBlue.resize(imageH, vector<long>(imageW, 0));
//     sumsqRed.resize(imageH, vector<long>(imageW, 0));
//     sumsqGreen.resize(imageH, vector<long>(imageW, 0));
//     sumsqBlue.resize(imageH, vector<long>(imageW, 0));

//     for (int i = 0; i < imageH; i++) {
//         for (int j = 0; j < imageW; j++) {
//             RGBAPixel* currPix = im.getPixel(j, i);

//             // find the value stored in the top rectange across the channels
//             if (0 <= j - 1) {
//                 topRectSum_r = sumRed[i][j-1];
//                 topRectSum_g = sumGreen[i][j-1];
//                 topRectSum_b = sumBlue[i][j-1];
//                 topRectSum_r_sq = topRectSum_r * topRectSum_r;
//                 topRectSum_g_sq = topRectSum_g * topRectSum_g;
//                 topRectSum_b_sq = topRectSum_b * topRectSum_b;
//             } else {
//                 topRectSum_r = 0;
//                 topRectSum_g = 0;
//                 topRectSum_b = 0;
//                 topRectSum_r_sq = 0;
//                 topRectSum_g_sq = 0;
//                 topRectSum_b_sq = 0;
//             }

//             // find the value stored in the left rectangle across the channels
//             if (0 <= i - 1) {
//                 leftRectSum_r = sumRed[i-1][j];
//                 leftRectSum_g = sumGreen[i-1][j];
//                 leftRectSum_b = sumBlue[i-1][j];
//                 leftRectSum_r_sq = leftRectSum_r * leftRectSum_r;
//                 leftRectSum_g_sq = leftRectSum_g * leftRectSum_g;
//                 leftRectSum_b_sq = leftRectSum_b * leftRectSum_b;
//             } else {
//                 leftRectSum_r = 0;
//                 leftRectSum_g = 0;
//                 leftRectSum_b = 0;
//                 leftRectSum_r_sq = 0;
//                 leftRectSum_g_sq = 0;
//                 leftRectSum_b_sq = 0;
//             }

//             // find the value stored in the top-left rectangle across the channels
//             if (0 <= i - 1 && 0 <= j - 1) {
//                 topLeftRectSum_r = sumRed[i-1][j-1];
//                 topLeftRectSum_g = sumGreen[i-1][j-1];
//                 topLeftRectSum_b = sumBlue[i-1][j-1];
//                 topLeftRectSum_r_sq = topLeftRectSum_r * topLeftRectSum_r;
//                 topLeftRectSum_b_sq = topLeftRectSum_b * topLeftRectSum_b;
//                 topLeftRectSum_g_sq = topLeftRectSum_g * topLeftRectSum_g;
//             } else {
//                 topLeftRectSum_r = 0;
//                 topLeftRectSum_g = 0;
//                 topLeftRectSum_b = 0;
//                 topLeftRectSum_r_sq = 0;
//                 topLeftRectSum_b_sq = 0;
//                 topLeftRectSum_g_sq = 0;
//             }
            
//             sumRed[i][j] = topRectSum_r + leftRectSum_r - topLeftRectSum_r + currPix->r;
//             sumGreen[i][j] = topRectSum_g + leftRectSum_g - topLeftRectSum_g + currPix->g;
//             sumBlue[i][j] = topRectSum_b + leftRectSum_b - topLeftRectSum_b + currPix->b;
            
//             sumsqRed[i][j] = topRectSum_r_sq + leftRectSum_r_sq - topLeftRectSum_r_sq + currPix->r * currPix->r;
//             sumsqGreen[i][j] = topRectSum_g_sq + leftRectSum_g_sq - topLeftRectSum_g_sq + currPix->g * currPix->g;
//             sumsqBlue[i][j] = topRectSum_b_sq + leftRectSum_b_sq - topLeftRectSum_b_sq + currPix->b * currPix->b;
//         }
//     }
// }


// credit: chatGpt
// the following code has the exactly the same logic as the code written above
// however, it is modified to look much cleaner
stats::stats(PNG& im) {
    int imageH = (int)im.height();
    // imageH = log2(imageH);
    // imageH = pow(2, imageH);

    int imageW = (int)im.width();
    // imageW = log2(imageW);
    // imageW = pow(2, imageW);

    sumRed.resize(imageH, vector<long>(imageW, 0));
    sumGreen.resize(imageH, vector<long>(imageW, 0));
    sumBlue.resize(imageH, vector<long>(imageW, 0));
    sumsqRed.resize(imageH, vector<long>(imageW, 0));
    sumsqGreen.resize(imageH, vector<long>(imageW, 0));
    sumsqBlue.resize(imageH, vector<long>(imageW, 0));

    for (int i = 0; i < imageH; i++) {
        for (int j = 0; j < imageW; j++) {
            RGBAPixel* currPix = im.getPixel(j, i);

            // Current pixel values and their squares
            long red = currPix->r;
            long green = currPix->g;
            long blue = currPix->b;

            long redSq = red * red;
            long greenSq = green * green;
            long blueSq = blue * blue;

            // Cumulative sums
            sumRed[i][j] = red +
                           (j > 0 ? sumRed[i][j - 1] : 0) +
                           (i > 0 ? sumRed[i - 1][j] : 0) -
                           (i > 0 && j > 0 ? sumRed[i - 1][j - 1] : 0);

            sumGreen[i][j] = green +
                             (j > 0 ? sumGreen[i][j - 1] : 0) +
                             (i > 0 ? sumGreen[i - 1][j] : 0) -
                             (i > 0 && j > 0 ? sumGreen[i - 1][j - 1] : 0);

            sumBlue[i][j] = blue +
                            (j > 0 ? sumBlue[i][j - 1] : 0) +
                            (i > 0 ? sumBlue[i - 1][j] : 0) -
                            (i > 0 && j > 0 ? sumBlue[i - 1][j - 1] : 0);

            // Cumulative squared sums
            sumsqRed[i][j] = redSq +
                             (j > 0 ? sumsqRed[i][j - 1] : 0) +
                             (i > 0 ? sumsqRed[i - 1][j] : 0) -
                             (i > 0 && j > 0 ? sumsqRed[i - 1][j - 1] : 0);

            sumsqGreen[i][j] = greenSq +
                               (j > 0 ? sumsqGreen[i][j - 1] : 0) +
                               (i > 0 ? sumsqGreen[i - 1][j] : 0) -
                               (i > 0 && j > 0 ? sumsqGreen[i - 1][j - 1] : 0);

            sumsqBlue[i][j] = blueSq +
                              (j > 0 ? sumsqBlue[i][j - 1] : 0) +
                              (i > 0 ? sumsqBlue[i - 1][j] : 0) -
                              (i > 0 && j > 0 ? sumsqBlue[i - 1][j - 1] : 0);
        }
    }
}


long stats::getSum(char channel, pair<int, int> ul, int dim) {
    /* Your code here!! */
    vector<vector<long>>* sumArray = &sumRed; // the reference needs to point to something

    if (channel == 'g') {
        sumArray = &sumGreen;
    }
    else if (channel == 'b') {
        sumArray = &sumBlue;
    }

    long numPixels = std::pow(2, dim);

    // note: this is NOT true
    // as in, x is ul.first, and y is ul.second
    // however, instead of swapping all the arr[x][y] with arr[y][x]
    // (cuz the later one is correct)
    // I just used this hack, haha smart me
    int y = ul.first; 
    int x = ul.second; 
    // int x = ul.first;
    // int y = ul.second;
    
    long right_bottom_sum = (*sumArray)[x + numPixels - 1][y + numPixels - 1];
    long topSum = 0;
    long leftSum = 0;
    long topLeftSum = 0;

    if (0 <= y-1) {
        topSum = (*sumArray)[x + numPixels - 1][y-1];
    }
    if (0 <= x-1) {
        leftSum = (*sumArray)[x-1][y + numPixels - 1];
    }
    if (0 <= x-1 && 0 <= y-1) {
        topLeftSum = (*sumArray)[x-1][y-1];
    }

    return right_bottom_sum - topSum - leftSum + topLeftSum;
}

long stats::getSumSq(char channel, pair<int, int> ul, int dim) {
    vector<vector<long>>* sumSqArray = &sumsqRed; // the reference needs to point to something

    if (channel == 'g') {
        sumSqArray = &sumsqGreen;
    }
    else if (channel == 'b') {
        sumSqArray = &sumsqBlue;
    }

    long numPixels = std::pow(2, dim);
    int y = ul.first; 
    int x = ul.second; 
    // int x = ul.first;
    // int y = ul.second;

    long right_bottom_sum = (*sumSqArray)[x + numPixels - 1][y + numPixels - 1];
    long topSum = 0;
    long leftSum = 0;
    long topLeftSum = 0;

    if (0 <= y-1) {
        topSum = (*sumSqArray)[x + numPixels - 1][y-1];
    }
    if (0 <= x-1) {
        leftSum = (*sumSqArray)[x-1][y + numPixels - 1];
    }
    if (0 <= x-1 && 0 <= y-1) {
        topLeftSum = (*sumSqArray)[x-1][y-1];
    }
    
    return right_bottom_sum - topSum - leftSum + topLeftSum;
}

long stats::rectArea(int dim) {
    long area = pow(2, dim) * pow(2, dim);
    return area;
}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
double stats::getVar(pair<int, int> ul, int dim) {
    long r_var = getSumSq('r', ul, dim) - pow(getSum('r', ul, dim), 2) / rectArea(dim);
    long g_var = getSumSq('g', ul, dim) - pow(getSum('g', ul, dim), 2) / rectArea(dim);
    long b_var = getSumSq('b', ul, dim) - pow(getSum('b', ul, dim), 2) / rectArea(dim);

    return r_var + g_var + b_var;
}

RGBAPixel stats::getAvg(pair<int, int> ul, int dim) {
    /* Your code here!! */
    long redSum = getSum('r', ul, dim);
    long blueSum = getSum('b', ul, dim);
    long greenSum = getSum('g', ul, dim);
    long area = rectArea(dim);

    int redAvg = (int) (redSum / area);
    int greenAvg = (int) (greenSum / area);
    int blueAvg = (int) (blueSum / area);

    return RGBAPixel(redAvg, greenAvg, blueAvg);
}
