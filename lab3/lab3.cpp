#include <iostream>
#include <fstream>
#include <regex>
#include<string>  

using namespace std;

int find_LOC(string filename){

    regex comment("^\\s*//.*");
    regex empty("( )*");
    int line_count = 0;
    string line;

    ifstream input_file (filename);
    if (input_file.is_open()){
        int count=0;
        while(getline(input_file, line)){
            istringstream is(line);
            if (regex_match(line, comment))
                cout << "comment found\n";
            else if (regex_match(line, empty)){
                cout << "empty line found\n";
            }
            else{
                line_count++;
                cout << "code line" << endl;
            }
        }
        input_file.close();
    }
    else{
        cout << "Unable to open input file." << endl;
        return -1;
    }
    return line_count;
}

int main(){

    int LOC = find_LOC("test.cpp");
    cout << "LOC is: " << LOC << endl;
    return 0;
}