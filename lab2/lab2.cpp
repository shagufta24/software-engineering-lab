#include <iostream>
#include <fstream>

using namespace std;

int find_LOC(string filename){

    int line_count = 0;
    string line;

    ifstream input_file (filename);
    if (input_file.is_open()){
        int count=0;
        while(getline(input_file, line)){
            if (line.length()==1){
                if (line[0] == '{' or line[0] == '}' or line[0]==';')
                    line_count++;
            }
            else
                line_count++;
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

    int LOC = find_LOC("lab2.cpp");
    cout << "LOC is: " << LOC << endl;
    return 0;
}