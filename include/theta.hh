#pragma once

#include <cctype>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>

namespace theta{
	std::vector<std::string> string_delimiter_split(std::string s, char delimiter);

	enum tokenizer_flags{
		USE_NONE = 0,
		USE_NEWLINE = 1 << 0,
		USE_INDENTATION = 1 << 1,
	};

	enum token_type{
		FILEEND, OP, NEWLINE, IDENT, STRING, CHAR, INT, FLOAT, INDENT, EXDENT,
	};

	class token{
	public:
		token_type type;
		std::string text;

		token(token_type type, std::string text);
	};

	class tokenizer{
	private:
		std::string comment_string;
		bool use_newline;
		bool use_indent;

	public:
		tokenizer(std::string comment_string, tokenizer_flags flags);

		tokenizer();

		std::vector<token> tokenize(std::string incode);
	};
}

