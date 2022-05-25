#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

// Data related to historical proxies
// Indexed from proxy 1 to proxy 33
int total_loc[] = {93,112,79,126,68,128,141,142,58,79,95,127,90,122,97,131,118,122,42,107,94,131,89,125,106,92,101,38,104,26,75,114,90};
int methods[] = {5,1,1,6,1,6,3,1,6,3,5,4,6,5,5,5,3,5,4,4,6,6,5,5,7,10,8,5,3,5,2,2,6};
string type[] = {"Calculation", "Calculation", "Calculation", "Calculation", "Calculation", "Calculation", "Calculation", "Calculation", "Calculation", "Calculation", "Data", "Data", "Data", "Data", "Data", "Data", "Data", "Data", "Data", "Data", "Data", "Data", "Data", "I/O", "I/O", "I/O", "I/O", "I/O", "I/O", "I/O", "I/O", "I/O", "I/O"};

// Data related to projects
vector<float> est_loc{124,360,229,321,279,352,297,263,357,311,341,153,390,260,215,468,528,232,304,459};
vector<float> actual_loc{98,284,292,286,350,464,381,369,365,284,277,212,319,218,238,312,676,266,225,395};
vector<float> est_dur{360,900,540,840,720,780,780,660,900,780,840,420,1020,660,540,1200,1260,600,780,1080};
vector<float> actual_dur{300,720,720,780,900,1380,1020,960,900,720,600,480,720,540,600,660,1620,840,600,1080};

int project_count = est_loc.size();
float sum_x, sum_y, sum_xy, sum_x_square, sum_y_square, coeff, constTerm = 0;

// To calculate mean
float mean(vector<float> nums, int count){
    float sum=0;
    for(int i=0; i<count; i++){
        sum += nums[i];
    }
    return sum/count;
}

// To calculate standard deviation
float std_dev(vector<float> nums, int count, float mean){
    float sum_of_squares_of_diffs = 0;
    for(int i=0; i<count; i++){
        sum_of_squares_of_diffs += pow(nums[i] - mean, 2);
    }
    return sqrt(sum_of_squares_of_diffs / (count-1));
}

// Midpoints calculation
// VS, S, M, L, VL
vector<float> midpoints(float mean, float sd){
    vector<float> res;
    res.push_back(mean - 2*sd);
    res.push_back(mean - sd);
    res.push_back(mean);
    res.push_back(mean + sd);
    res.push_back(mean + 2*sd);
    return res;
}


void print_vector(vector<float> v){
    for (int i=0; i<v.size(); i++){
        cout << v[i] << ", ";
    }
    cout << endl;
}

void calc_factors_loc(){
    for (int i=0; i<project_count; i++){
        sum_x += est_loc[i];
        sum_y += actual_loc[i];
        sum_xy += est_loc[i] * actual_loc[i];
        sum_x_square += est_loc[i] * est_loc[i];
        sum_y_square += actual_loc[i] * actual_loc[i];
    }
}

void calc_factors_dur(){
    for (int i=0; i<project_count; i++){
        sum_x += est_dur[i];
        sum_y += actual_dur[i];
        sum_xy += est_dur[i] * actual_dur[i];
        sum_x_square += est_dur[i] * est_dur[i];
        sum_y_square += actual_dur[i] * actual_dur[i];
    }
}

void calculateCoefficient()
{
    float numerator
        = (project_count * sum_xy - sum_x * sum_y);
    float denominator
        = (project_count * sum_x_square - sum_x * sum_x);
    coeff = numerator / denominator;
}
 
void calculateConstantTerm()
{
    float numerator
        = (sum_y * sum_x_square - sum_x * sum_xy);
    float denominator
        = (project_count * sum_x_square - sum_x * sum_x);
    constTerm = numerator / denominator;
}

void BestFitLine()
{
    calculateCoefficient();
    calculateConstantTerm();
    cout << endl << "The best fitting line is y = "
            << coeff << "x + " << constTerm << endl;
}

float t_value =  1.06716;
int n = 20;

float range(){
    float B0 = constTerm;
    float B1 = coeff;

    // Term 1
    float sum = 0;
    for (int i=0; i<project_count; i++){
        float diff = (actual_loc[i] - (B1 * est_loc[i]) - B0);
        sum += diff * diff;
    }
    float term1 = sqrt(sum/(n-2));

    // Term 2
    float avg_x = mean(est_loc, project_count);
    float LOCE = 1059.16;

    sum = 0;
    for (int i=0; i<project_count; i++){
        float diff = est_loc[i] - avg_x;
        sum += diff * diff;
    }

    float a = LOCE - avg_x;
    float term2 = sqrt(1 + (1/n) + (a*a)/sum);

    return t_value * term1 * term2;
}

// Additional proxy data
vector <float> LOC{142,101,118,122,107,122,93,68};
vector <float> meth{1,8,3,5,4,5,5,1};
vector<float> midpnts{39.17701808,16.98243652,37.131893,22.46,29.79799778,22.46,16.94937436,39.17701808};
vector <float> loc_per_method;
void proxy_sizing(){
    cout << "LOC per method (log-normal): " ;
    for(int i=0; i<LOC.size(); i++){
        float val = log10(LOC[i]/meth[i]);
        loc_per_method.push_back(val);
        cout << val << ", ";
    }

    cout << endl << "Predicted LOC for each proxy: " ;
    for(int i=0; i<LOC.size(); i++){
        float val = meth[i] * midpnts[i];
        cout << val << ", ";
    }
    
}

int main(){

    // Array containing log normal LOC per method of each proxy in these types
    vector<float>calc;
    vector<float>data;
    vector<float>io;

    for (int i=0; i<33; i++){
        if (type[i].compare("Calculation") == 0){
            calc.push_back(log10(total_loc[i]/methods[i]));
        }
        else if (type[i].compare("Data") == 0){
            data.push_back(log10(total_loc[i]/methods[i]));
        }
        else{
            io.push_back(log10(total_loc[i]/methods[i]));
        }
    }

    float calc_mean = mean(calc, calc.size());
    float data_mean = mean(data, data.size());
    float io_mean = mean(io, io.size());

    cout << endl << "Means: " << endl << 
    "Calculation: " << calc_mean << endl << 
    "Data: " << data_mean << endl << 
    "IO: " << io_mean << endl;

    float calc_sd = std_dev(calc, calc.size(), calc_mean);
    float data_sd = std_dev(data, data.size(), data_mean);
    float io_sd = std_dev(io, io.size(), io_mean);

    cout << endl << "SD: " << endl << 
    "Calculation: " << calc_sd << endl << 
    "Data: " << data_sd << endl << 
    "IO: " << io_sd << endl;

    
    cout << endl << "Midpoints:" << endl << "(VS, S, M, L, VL)" << endl;
    vector<float> calc_mids = midpoints(calc_mean, calc_sd);
    vector<float> data_mids = midpoints(data_mean, data_sd);
    vector<float> io_mids = midpoints(io_mean, io_sd);

    cout << "Calculation: ";
    print_vector(calc_mids);
    cout << "Data: ";
    print_vector(data_mids);
    cout << "IO: ";
    print_vector(io_mids);

    cout << endl << "Proxy_sizing: " << endl;
    proxy_sizing();
    cout << endl;

    cout << endl << "Project LOC data projections: ";
    calc_factors_loc();
    BestFitLine();
    cout << "B0 = " << constTerm << " and B1 = " << coeff << endl;

    cout << "70% Prediction Range: " << range() << endl;

    int N = 952;
    float u_lim = N + range();
    float l_lim = N - range();
    cout << "UPI: " << u_lim << endl;
    cout << "LPI: " << l_lim << endl;
    
}