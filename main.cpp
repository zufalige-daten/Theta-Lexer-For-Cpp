#include <iostream>
#include <vector>
#include <fstream>
#include "Theta.hpp"

using namespace std;
using namespace Theta;

int main(int argc, char *argv[])
{
    if (argc < 2){
        cout << "Error, arguments must at least contain input file." << endl;
        exit(0);
    }
    string incode = "";
    string line;
    ifstream infile (argv[1]);
    if (infile.is_open()){
        while (getline(infile, line)){
            incode += line;
            incode += "\n";
        }
        infile.close();
    }
    else{
        cout << "Error, unable to open input file '" << argv[1];
    }
    vector<Token> tokens = Tokenize(incode, "//", true, true);
    for (int i = 0; i < tokens.size(); i++) {
        cout << tokens[i].Type << "\t\t\t\t" << tokens[i].Text << endl;
    }
}