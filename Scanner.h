

#ifndef Scanner_h
#define Scanner_h Scanner_h




#include "FlexLexer.h"



#include <istream>




//aeaienirnaesr

//! Class for the scanner, which is generated by flex
class Scanner : public yyFlexLexer
{
	public:

		Scanner(ParserBase::STYPE__ &d_val ) : yyFlexLexer(source) 
		{	
			d_val__ = & d_val;
		}	
		static istream* source;
		Scanner() : yyFlexLexer(source) {};
		int lex()
		{ return yylex(); }

//		yywrap() { return 1; }
};



#endif
