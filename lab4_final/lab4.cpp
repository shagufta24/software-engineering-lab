#include <iostream>
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
 
    void calculateCoefficient()
    {
        float N = x.size();
        float numerator
            = (N * sum_xy - sum_x * sum_y);
        float denominator
            = (N * sum_x_square - sum_x * sum_x);
        coeff = numerator / denominator;
    }
 
    void calculateConstantTerm()
    {
        float N = x.size();
        float numerator
            = (sum_y * sum_x_square - sum_x * sum_xy);
        float denominator
            = (N * sum_x_square - sum_x * sum_x);
        constTerm = numerator / denominator;
    }
 
    int sizeOfData()
    {
        return x.size();
    }
 
    float coefficient()
    {
        if (coeff == 0)
            calculateCoefficient();
        return coeff;
    }
 
    float constant()
    {
        if (constTerm == 0)
            calculateConstantTerm();
        return constTerm;
    }
 
    void BestFitLine()
    {
        if (coeff == 0 && constTerm == 0) {
            calculateCoefficient();
            calculateConstantTerm();
        }
        cout << "The best fitting line is y = "
             << coeff << "x + " << constTerm << endl;
    }
 
    // Function to take input from the input file
    void takeInput(int n)
    {
        for (int i = 0; i < n; i++) {
            // In a txt file, write each pair of xi and yi separated by commas on a separate line
            // The first line must contain the number of pairs
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
        cout << sum_x << endl << sum_y << endl << sum_xy << endl;
    }
 
    // Print the input data set
    void showData()
    {
        printf("\n");
        printf("%15s%5s %15s\n",
               "X", "", "Y");
 
        for (int i = 0; i < x.size(); i++) {
            printf("%20f %20f\n",
                   x[i], y[i]);
        }
        printf("\n");
    }
 
    // Predict the value correspondng to some input
    float predict(float x)
    {
        return coeff * x + constTerm;
    }

};
 
// Driver code
int main()
{
    freopen("input2.txt", "r", stdin);
    regression reg;
 
    // Number of pairs of (xi, yi) in the dataset
    int n;
    cin >> n;
 
    // Calling function takeInput to take input of n pairs
    reg.takeInput(n);
 
    cout << "Input given: " << endl;
    reg.showData();

    // Printing the best fitting line
    reg.BestFitLine();
    // cout << "Predicted value = "
    //      << reg.predict(4) << endl;
}