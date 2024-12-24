#pragma once

#include <cctype>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>

namespace theta{
	std::vector<std::string> string_delimiter_split(std::string s, char delimiter);

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
		std::string cb_string;
		std::string ce_string;
		bool use_newline;
		bool use_indent;
		bool use_single_line_comments;
		bool use_many_lines_comments;

	public:
		void configure_newlines(bool enabled);

		void configure_indentations(bool enabled);

		void configure_comments_singular_line(bool enabled, std::string comment_start_string);

		void configure_comments_many_lines(bool enabled, std::string comment_begin_string, std::string comment_end_string);

		tokenizer();

		std::vector<token> tokenize(std::string incode);
	};
}

