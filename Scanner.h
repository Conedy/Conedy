

#ifndef Scanner_h
#define Scanner_h Scanner_h




#include <FlexLexer.h>



#include <istream>







class Scanner : public yyFlexLexer
{
	public:
		static istream* source;
		Scanner() : yyFlexLexer(source) {};
		int lex()
		{ return yylex(); }

//		yywrap() { return 1; }
};



#endif
