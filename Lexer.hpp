#ifndef LEXER_HPP
#define LEXER_HPP

class Lexer {
	public:
		Lexer();
		Lexer(int argc, char* argv[]);
		Lexer(Lexer const& obj);
		~Lexer();

		Lexer& operator=(Lexer const& obj);
};

#endif
