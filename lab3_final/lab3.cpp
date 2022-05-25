#include <iostream>
#include <fstream>
#include <regex>
#include <string> 
#include <vector> 

using namespace std;

vector<string> read_file(string filename){
    string line;
    vector<string> v;

    ifstream input_file (filename);
    if (input_file.is_open()){
        while(getline(input_file, line)){
            v.push_back(line);
        }
        input_file.close();
    }
    else{
        cout << "Unable to open input file." << endl;
    }
    return v;
}

void parse(vector<string> v){

    regex comment("^\\s*//.*");
    regex empty("( )*");
    regex begin_class("^\\s*// BEGIN CLASS (\\w+)");
    regex end_class("^\\s*// END CLASS (\\w+)");
    regex begin_func("^\\s*// BEGIN FUNCTION (\\w+)");
    regex end_func("^\\s*// END FUNCTION (\\w+)");
    regex anything(".*");
    smatch m;

    int c = 0;
    int f = 0;
    int func_loc = 0;
    int func_count = 0;

    for (auto& line : v) {
        if (regex_search(line, m, begin_class)){
            c = 1;
            func_count = 0;
            cout << "\nClass name: " << m[1] << endl;
        }  
        else if (regex_match(line, end_class)){
            c = 0;
            cout << " Total function count: " << func_count << endl;
            func_count = 0;
        }
        else if (regex_search(line, m, begin_func) && c==1){
            f = 1;
            cout << "  Function name: " << m[1] << endl;
            func_count += 1;
        }
        else if (regex_search(line, m, begin_func) && c==0){
            f = 1;
            cout << "\nFunction name: " << m[1] << endl;
            func_count += 1;
        }
        else if (regex_search(line, m, end_func) && c==1){
            cout << "  LOC: " << func_loc << endl;
            func_loc = 0;
            f = 0;
        }
        else if (regex_search(line, m, end_func) && c==0){
            cout << "LOC: " << func_loc << endl;
            func_loc = 0;
            f = 0;
        }
        else if (f == 1){
            if (!regex_match(line, comment) && !regex_match(line, empty))
                func_loc++;
        }
    }    
}

int main(){

    vector<string> v = read_file("sample.cpp");
    
    parse(v);
    return 0;
}