# Theta Lexer For Cpp
 A lexer called 'Theta' as a small c++ header you can include and use to lex some code in a compiler, transpiler, assembler, etc. Support right now is not full, python lexing won't work due to indentation, but other than that, most languages that don't use indentation as a core part of the language can be lexed.

This master comes with examples, in 'main.cpp'.

To use it in your compiler, just call from the Theta namespace 'Tokenize' with inputs: code to lex, comment string, weather comment is 2 wide or 1 wide (true = 2 wide) then if newlines should be included in the output tokens. then get the vector<tokens> as an output.

Like: 'vector<Token> tokens = Tokenize(incode, "//", true, true);'

If there are any bugs, please let me know.
