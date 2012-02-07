//============================================================================
// Name        : Niwango.cpp
// Author      : PSI
// Version     :
// Copyright   : 2011 PSI
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "parser/niwangoLexer.h"
#include "parser/niwangoParser.h"
using namespace std;

int main(const int argc, const char* args[]) {
	//pANTLR3_INPUT_STREAM stream = antlr3FileStreamNew((ANTLR3_UINT8*)args[1], ANTLR3_ENC_UTF8);
	const std::string src="'testaあaa';0x12";
	pANTLR3_INPUT_STREAM stream = antlr3StringStreamNew((pANTLR3_UINT8)src.c_str(), ANTLR3_ENC_UTF8, src.size(), (pANTLR3_UINT8)"test_file");
	pniwangoLexer lexer = niwangoLexerNew(stream);
	pANTLR3_COMMON_TOKEN_STREAM tokenStream = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lexer));
	pniwangoParser parser = niwangoParserNew(tokenStream);

	parser->program(parser);

	stream->free(stream);
	lexer->free(lexer);
	tokenStream->free(tokenStream);
	parser->free(parser);
	return 0;
}
