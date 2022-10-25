# Theta Lexer For Cpp
 A lexer called 'Theta' as a small c++ header you can include and use to lex some code in a compiler, transpiler, assembler, etc. Support right now has been updated so that python lexing works with indentation detection, and also most languages that use standard text can be lexed.

This master comes with examples, in 'main.cpp'.

To use it in your compiler, just call from the Theta namespace 'Tokenize' with inputs: code to lex, comment string, weather comment is 2 wide or 1 wide (true = 2 wide) then if newlines should be included in the output tokens, and then if indentation tokens are detected. then get the vector<Token> as an output.

Like: 'vector<Token> tokens = Tokenize(incode, "#", false, true, true);'

If there are any bugs, please let me know.
