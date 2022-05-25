#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <string>
#define PI 3.1416

using namespace std;
 
double y(double n)
{
    if(n == 1) 
    {
    	return 1;
    }
    if(n == 0.5) 
    {
		return sqrt(PI);
	}
    else
    {
    	return (n-1)*y(n - 1);
    }
}

double f(double x , double n)
{
    double temp1 = y((n+1)/2)/(y(n/2)*sqrt(n*M_PI));
    double temp2 = (1 + ((x*x)/n));
    return temp1*(1/pow(temp2, (n+1)/2));
}

double integration(double upper,double lower,double subInterval, int deg, int tail)
{
    double stepSize, k, integration = 0.0;
    double error = 100;
    double old = 100000;
    while(error > 0.01)
    {
    stepSize = (upper - lower)/subInterval;
    integration = f(lower, deg) + f(upper, deg);

    for(int i=1; i<= subInterval-1; i++)
    {
        k = lower + i*stepSize;

        if(i%2==0)
        {
            integration = integration + 2 * (f(k, deg));
        }
        else
        {
            integration = integration + 4 * (f(k, deg));
        }
    }
    integration = integration * stepSize/3;
    error = (old - integration)/integration;
    old = integration;
    subInterval *= 2;
    }
    return ((double)1 - integration*(double)tail);
}

int main()
{
    double lower, upper = 350, prob = 0.0, stepsize, k;
    int sno;
    int subInterval= 4, deg, tail;
    double c,old_value;
    string lines;
    fstream input;
    input.open("input.txt", ios::in);
    if(input.is_open()){
        cout << "Test" << "   " << "t" << "      " << "DOF" << "    " << "tails" << "  " << "Probability" << endl;
    	while(getline(input, lines)){
            if(!lines.empty())
            {
                stringstream s(lines);
                string word;
                s >> word;
                sno = std::stoi(word);
                s >> word;
                lower = std::stod(word);
                s >> word;
                deg = std::stoi(word);
                s >> word;
                tail = std::stoi(word);
                prob = 0.0;
                c = 100;
                old_value = 100000;
                subInterval = 4;
                while(c > 0.01)
    			{
    				stepsize = (upper - lower)/subInterval;
    				prob = f(lower, deg) + f(upper, deg);

    				for(int i=1; i<= subInterval-1; i++)
    				{
        				k = lower + i*stepsize;

        			if(i%2==0)
        			{
            			prob = prob + 2 * (f(k, deg));
        			}
        			else
        			{
            			prob = prob + 4 * (f(k, deg));
        			}

    				}
    				prob = prob * stepsize/3;
    				c = (old_value - prob)/prob;
    				old_value = prob;
    				subInterval *= 2;
    			}
    			prob = (double)1 - prob*(double)tail;
                prob = std::ceil(prob * 1000.0) / 1000.0;
                cout << sno << "     " << lower << "     " << deg << "     " << tail << "     " << prob << endl;
            }
        }
        input.close();
    }
}
