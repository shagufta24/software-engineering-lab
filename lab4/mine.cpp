#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdio.h>
#include <vector>

using namespace std;
    

class regression {

    vector<float> x;
    vector<float> y;
    float coeff;
    float constTerm;
    float sum_xy;
    float sum_x;
    float sum_y;
    float sum_x_square;
    float sum_y_square;

public:
    regression()
    {
        coeff = 0;
        constTerm = 0;
        sum_x = 0;
        sum_y = 0;
        sum_xy = 0;
        sum_x_square = 0;
        sum_y_square = 0;
    }

    void takeInput(int n)
    {
        for (int i = 0; i < n; i++) {
            // In a csv file all the values of xi and yi are separated by commas
            char comma;
            float xi;
            float yi;
            cin >> xi >> comma >> yi;
            sum_xy += xi * yi;
            sum_x += xi;
            sum_y += yi;
            sum_x_square += xi * xi;
            sum_y_square += yi * yi;
            x.push_back(xi);
            y.push_back(yi);
        }
    }
}

int main(){
    
}