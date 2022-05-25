#include <iostream>
#include <regex>
#include <fstream>
#include <vector>

using namespace std;

vector<string> get_strings(string filename){
    vector<string> v;
    string line;

    fstream input_file;
    input_file.open(filename,ios::in);
    if (input_file.is_open()){
        while(getline(input_file, line)){
            v.push_back(line);
        }
        input_file.close();
    }
    return v;
}

int main(){
    string filename = "test.cpp";
    vector<string> v;

    v = get_strings(filename);

    regex r(".*");
    for (auto& line : v) {
        if ( regex_match(line, r) )
        cout << line << endl;
    }
}
