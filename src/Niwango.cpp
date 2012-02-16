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
#include "logging/Logging.h"
#include "machine/Machine.h"
#include "machine/object/Object.h"
using namespace std;
using namespace std::tr1;

int main(const int argc, const char* args[]) {
	//pANTLR3_INPUT_STREAM stream = antlr3FileStreamNew((ANTLR3_UINT8*)args[1], ANTLR3_ENC_UTF8);
	std::string src = "a=1+1";
	pANTLR3_INPUT_STREAM stream = antlr3StringStreamNew((pANTLR3_UINT8)src.c_str(), ANTLR3_ENC_UTF8, src.size(), (pANTLR3_UINT8)"test_file");
	pniwangoLexer lexer = niwangoLexerNew(stream);
	pANTLR3_COMMON_TOKEN_STREAM tokenStream = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lexer));
	pniwangoParser parser = niwangoParserNew(tokenStream);

//	shared_ptr<timeline::TimeLine> timeLine = parser->time_line(parser);
//	logging::Dumper dumper(cout);
//	for(timeline::TimeLine::Iterator it = timeLine->begin();it!=timeLine->end();it++){
//		(*it).getNode()->dump(dumper);
//	}
	shared_ptr<const Node> node = parser->program(parser);
	machine::Machine machine;
	machine::Object* const obj = machine.eval(node.get());
	cout << "result=" << obj->toStringObject()->toString() << endl;


	stream->free(stream);
	lexer->free(lexer);
	tokenStream->free(tokenStream);
	parser->free(parser);
	return 0;
}
