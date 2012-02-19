//============================================================================
// Name        : Niwango.cpp
// Author      : PSI
// Version     :
// Copyright   : 2011 PSI
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sstream>
#include <getopt.h>
#include <libgen.h>
#include <iomanip>
#include "const.h"
#include "parser/niwangoLexer.h"
#include "parser/niwangoParser.h"
#include "logging/Logging.h"
#include "machine/Machine.h"
#include "machine/object/Object.h"
using namespace std;
using namespace std::tr1;

void usage(int argc, char* args[]){
	cout << "Usage: " << basename(args[0]) << " [switches] [--] [programfile]" << endl;
	cout << "    " << std::left << std::setw(15) << "--trace" << "set log level." << endl;
	cout << "    " << std::left << std::setw(15) << "--verbose" << "set log level." << endl;
	cout << "    " << std::left << std::setw(15) << "--debug"<<"set log level." << endl;
	cout << "    " << std::left << std::setw(15) << "--warning"<<"set log level." << endl;
	cout << "    " << std::left << std::setw(15) << "--error"<<"set log level." << endl;
	cout << "    " << std::left << std::setw(15) << "--dump"<<"output dump of AST, then exit." << endl;
	cout << "    " << std::left << std::setw(15) << "--version"<<"output the version, then exit." << endl;
	cout << "    " << std::left << std::setw(15) << "-h, --help"<<"output the help, then exit." << endl;
	exit(0);
}

void version(int argc, char* args[]){
	cout << PROGRAM_NAME << ": "<< PROGRAM_VERSION <<" (build at " << __DATE__ << " " << __TIME__ << " )" << endl;
	exit(0);
}

const struct option ARG_OPTIONS[] = {
		{"trace", no_argument, 0, 1},
		{"verbose", no_argument, 0, 2},
		{"debug", no_argument, 0, 3},
		{"warning", no_argument, 0, 4},
		{"error", no_argument, 0, 5},
		{"dump", no_argument, 0, 6},
		{"help", no_argument, 0, 7},
		{"version", no_argument, 0, 8},
		{0,0,0,0}
};

int main(int argc, char* args[]) {
	int indexptr=0;
	logging::Logger::Level level = logging::Logger::WARNING;
	bool dump = false;
	while(1){
		int opt = getopt_long(argc, args, "h", ARG_OPTIONS, &indexptr);
		if(opt < 0){
			break;
		}
		switch(opt)
		{
		case 1:
			level = logging::Logger::TRACE;
			break;
		case 2:
			level = logging::Logger::VERBOSE;
			break;
		case 3:
			level = logging::Logger::DEBUG;
			break;
		case 4:
			level = logging::Logger::WARNING;
			break;
		case 5:
			level = logging::Logger::ERROR;
			break;
		case 6:
			dump = true;
			break;
		case 7:
		case 'h':
			usage(argc, args);
			break;
		case 8:
			version(argc, args);
			break;
		case '?':
			exit(0);
			break;
		}
	}

	pANTLR3_INPUT_STREAM stream = 0;
	std::string out;
	if(optind < argc){
		stream = antlr3FileStreamNew((ANTLR3_UINT8*)args[optind], ANTLR3_ENC_UTF8);
	}else{
		stringstream ss;
		char buff[8192];
		while(1){
			cin >> buff;
			if(cin.eof()){
				break;
			}
			ss << buff;
		}
		out=ss.str();
		stream = antlr3StringStreamNew((pANTLR3_UINT8)out.c_str(), ANTLR3_ENC_UTF8, out.size(), (pANTLR3_UINT8)"cin");
	}

	pniwangoLexer lexer = niwangoLexerNew(stream);
	pANTLR3_COMMON_TOKEN_STREAM tokenStream = antlr3CommonTokenStreamSourceNew(ANTLR3_SIZE_HINT, TOKENSOURCE(lexer));
	pniwangoParser parser = niwangoParserNew(tokenStream);

	shared_ptr<timeline::TimeLine> timeLine = parser->time_line(parser);

	if(dump){
		logging::Dumper dumper(cout);
		timeLine->dump(dumper);
		return 0;
	}

	logging::Logger log(std::cout, level);
	machine::Machine machine(log);
	machine::Object* obj;
	for(timeline::TimeLine::Iterator it = timeLine->begin();it != timeLine->end();++it){
		obj = machine.eval((*it).getNode().get());
	}
	cout << "result=" << obj->toStringObject()->toString() << endl;


	stream->free(stream);
	lexer->free(lexer);
	tokenStream->free(tokenStream);
	parser->free(parser);
	return 0;
}
