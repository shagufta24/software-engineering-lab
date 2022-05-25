// Online C++ compiler to run C++ program online
#include <iostream>
#include <regex>
using namespace std;

int main() {
    
    string a = "       // comment 0";
    regex b("( )*\/\/[A-Za-z0-9( )]*");
    
    cout << a << endl;
    
    if ( regex_match(a, b) )
        cout << "match\n";
    else
        cout << "no match\n";
    return 0;
}