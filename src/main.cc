#include <iostream>
#include <vector>
#include <fstream>
#include <theta.hh>

int main(int argc, char *argv[])
{
    if (argc < 2){
		std::cout << "Error: Arguments must at least contain input file.\n";
        exit(0);
    }
	std::string incode = "";
	std::string line;
	std::ifstream infile (argv[1]);
    if (infile.is_open()){
        while (getline(infile, line)){
            incode += line;
            incode += "\n";
        }
        infile.close();
    }
    else{
		std::cout << "Error: Unable to open input file '" << argv[1] << "'.\n";
    }
	theta::tokenizer tokenizer("#", theta::USE_NONE);
	std::vector<theta::token> tokens = tokenizer.tokenize(incode);
    for (int i = 0; i < tokens.size(); i++) {
		std::cout << tokens[i].type << "\t\t\t\t" << tokens[i].text << "\n";
    }
}

