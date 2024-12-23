#include <theta.hh>
#include <cctype>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>

namespace theta{
	std::vector<std::string> string_delimiter_split(std::string s, char delimiter){
		std::vector<std::string> result;
		std::stringstream ss (s);
		std::string item;
	
	    while (getline (ss, item, delimiter)) {
	        result.push_back (item);
	    }

	    return result;
	}

	token::token(token_type type, std::string text){
		this->type = type;
		this->text = text;
	}

	tokenizer::tokenizer(std::string comment_string, tokenizer_flags flags){
		this->comment_string = comment_string;
		this->use_newline = flags & USE_NEWLINE;
		this->use_indent = flags & USE_INDENTATION;
	}

	std::vector<token> tokenizer::tokenize(std::string incode){
        int line = 1;
		std::vector<token> tokens;
		int i = 0;
        int oldindent = 0;
        int newindent = 0;
		while (true) {
            if (i > 0 && incode[i-1] == '\n' && this->use_indent){
                // coming from newline
                newindent = 0;
                while(incode[i] == '\t' || incode[i] == ' '){
                    if(incode[i] == '\t'){
                        newindent += 4; // tab = 4 spaces
                    }
                    else{
                        newindent++;
                    }
                    i++;
                }
                newindent /= 4;
                if(newindent > oldindent){
                    for(int i = 0; i < newindent-oldindent; i++){
                        tokens.push_back(token(token_type::INDENT, ""));
                    }
                }
                else if(oldindent > newindent){
                    for(int i = 0; i < oldindent-newindent; i++){
                        tokens.push_back(token(token_type::EXDENT, ""));
                    }
                }
                oldindent = newindent;
            }
            if (i >= incode.size()){
                break;
            }
            if (incode[i] == '\n'){
                if (this->use_newline){
                    tokens.push_back(token(token_type::NEWLINE, "\n"));
                }
			    i++;
                line++;
            }
			else if (strncmp(&incode.data()[i], comment_string.data(), comment_string.size()) == 0){
				while (incode[i] != '\n' && i < incode.size()){
					i++;
				}
			}
            else if (incode[i] == ' ' || incode[i] == '\t'){
			    i++;
            }
            else if (isalpha(incode[i])){
				std::string outstr = "";
                while (isalnum(incode[i]) || incode[i] == '_' || incode[i] == '.'){
                    outstr += incode[i];
                    i++;
                }
                tokens.push_back(token(token_type::IDENT, outstr));
            }
            else if (incode[i] == '0' && toupper(incode[i+1]) == 'X'){
                i += 2;
				std::string outstr = "0x";
                while (isxdigit(incode[i])){
                    outstr += incode[i];
                    i++;
                }
                tokens.push_back(token(token_type::INT, outstr));
            }
            else if (isdigit(incode[i])){
                std::string outstr = "";
                while (isdigit(incode[i])){
                    outstr += incode[i];
                    i++;
                }
                if (incode[i] == '.'){
                    outstr += ".";
                    i++;
                    while (isdigit(incode[i])){
                        outstr += incode[i];
                        i++;
                    }
                    tokens.push_back(token(token_type::FLOAT, outstr));
                }
                else{
                    tokens.push_back(token(token_type::INT, outstr));
                }
            }
            else if (incode[i] == '"'){
                i++;
                std::string outstr = "\"";
                while (incode[i] != '"' && i != incode.size()){
                    if (incode[i] == '\\'){
                        i++;
                        if (incode[i] == 'n'){
                            outstr += "\", 10, \"";
                            i++;
                        }
                        else if (incode[i] == 'r'){
                            outstr += "\", 13, \"";
                            i++;
                        }
                        else if (incode[i] == 't'){
                            outstr += "\", 9, \"";
                            i++;
                        }
                        else if (incode[i] == '"'){
                            outstr += "\\\"";
                            i++;
                        }
                        else{
                            outstr += incode[i];
                            i++;
                        }
                    }
                    else{
                        outstr += incode[i];
                        i++;
                    }
                }
                outstr += "\"";
                i++;
                tokens.push_back(token(token_type::STRING, outstr));
            }
            else if ((incode[i] == '+' && (incode[i+1] == '+' || incode[i+1] == '=')) ||
                (incode[i] == '-' && (incode[i+1] == '-' || incode[i+1] == '=')) ||
                (incode[i] == '*' && incode[i+1] == '=') || (incode[i] == '/' && incode[i+1] == '=') ||
                (incode[i] == '=' && incode[i+1] == '=') ||
                (incode[i] == '|' && incode[i+1] == '|') ||
                (incode[i] == '&' && incode[i+1] == '&') ||
                (incode[i] == '<' && (incode[i+1] == '=' || incode[i+1] == '<')) ||
                (incode[i] == '>' && (incode[i+1] == '=' || incode[i+1] == '>'))){
                std::string outstr = incode[i] + std::string().append(1, incode[i+1]);
                i += 2;
                tokens.push_back(token(token_type::OP, outstr));
            }
            else if (incode[i] == '\''){
                i++;
                std::string outstr = "'";
                while (incode[i] != '\'' && i != incode.size()){
                    if (incode[i] == '\\'){
                        i++;
                        if (incode[i] == 'n'){
                            outstr += "', 10, '";
                            i++;
                        }
                        else if (incode[i] == 'r'){
                            outstr += "', 13, '";
                            i++;
                        }
                        else if (incode[i] == 't'){
                            outstr += "', 9, '";
                            i++;
                        }
                        else if (incode[i] == '\''){
                            outstr += "\\'";
                            i++;
                        }
                        else{
                            outstr += incode[i];
                            i++;
                        }
                    }
                    else{
                        outstr += incode[i];
                        i++;
                    }
                }
                outstr += "'";
                i++;
                tokens.push_back(token(token_type::CHAR, outstr));
            }
            else{
                tokens.push_back(token(token_type::OP, std::string().append(1, incode[i])));
			    i++;
            }
		}
		tokens.push_back(token(token_type::FILEEND, ""));
		return tokens;
	}
}

