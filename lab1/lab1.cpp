#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;

// To diaply an array of numbers
void show(float* nums, int count){
    for (int i=0; i<count; i++){
        cout << nums[i] << " ";
    }
    cout << endl;
}

// To calculate mean
float mean(float* nums, int count){
    float sum=0;
    for(int i=0; i<count; i++){
        sum += nums[i];
    }
    return sum/count;
}


// To calculate median
float median(float* nums, int count){
    float sorted[count];
    copy(nums, nums+count, sorted);
    sort(sorted, sorted + count);
    if (count%2==0)
        return (sorted[(count/2)-1] + sorted[count/2])/2;
    else
        return sorted[(count/2)];
}

// To calculate standard deviation
float std_dev(float* nums, int count, float mean){
    float sum_of_squares_of_diffs = 0;
    for(int i=0; i<count; i++){
        sum_of_squares_of_diffs += pow(nums[i] - mean, 2);
    }
    return sqrt(sum_of_squares_of_diffs / (count-1));
}


int main(){

    int n; //No. of inputs
    cout << "Enter number of inputs: ";
    cin >> n;

    // Checks
    if (n<1){
        cout << "Input must be a non-zero positive number." << endl;
        return 1;
    }
    if (n>100){
        cout << "Input cannot be greater than 100." << endl;
        return 1;
    }

    // Array to hold input data
    float inputs[n];

    // Opening and reading input file contents to the array
    string line;
    ifstream input_file ("input.txt");

    if (input_file.is_open()){
        int count=0;
        while(getline(input_file, line) && count<n){
            inputs[count] = stof(line);
            count++;
        }
        if (count<n){
            cout << "There are fewer numbers in the input file than the entered number." << endl;
            return 1;
        }
        input_file.close();
    }
    else{
        cout << "Unable to open input file." << endl;
        return 1;
    }

    cout << "Inputs: ";
    show(inputs, n);

    float m = mean(inputs, n);
    cout << "Mean: " << m << endl;
    cout << "Standard Deviation: " << std_dev(inputs, n, m) << endl;
    cout << "Median: " << median(inputs, n) << endl;

    return 0;
}