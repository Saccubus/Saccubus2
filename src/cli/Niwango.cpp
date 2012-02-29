/*
 * Niwango.cpp
 *
 *  Created on: 2012/02/26
 *      Author: psi
 */

#include <iostream>
#include <getopt.h>
#include <libgen.h>
#include <iomanip>
#include <cstdlib>
#include "CLISystem.h"
#include "../nekomata/Nekomata.h"
using namespace std;
using namespace std::tr1;

namespace cli{

void usage(int argc, char* argv[]){
	cout << "Usage: " << basename(argv[0]) << " [switches] [--] [programfile]" << endl;
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

void version(int argc, char* argv[]){
	cout << nekomata::PROGRAM_NAME << ": "<< nekomata::PROGRAM_VERSION <<" (build at " << __DATE__ << " " << __TIME__ << " )" << endl;
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

int main(int argc, char* argv[]){

	int indexptr=0;
	nekomata::logging::Logger::Level level = nekomata::logging::Logger::WARNING;
	bool dump = false;
	while(1){
		int opt = getopt_long(argc, argv, "h", ARG_OPTIONS, &indexptr);
		if(opt < 0){
			break;
		}
		switch(opt)
		{
		case 1:
			level = nekomata::logging::Logger::TRACE;
			break;
		case 2:
			level = nekomata::logging::Logger::VERBOSE;
			break;
		case 3:
			level = nekomata::logging::Logger::DEBUG;
			break;
		case 4:
			level = nekomata::logging::Logger::WARNING;
			break;
		case 5:
			level = nekomata::logging::Logger::ERROR;
			break;
		case 6:
			dump = true;
			break;
		case 7:
		case 'h':
			usage(argc, argv);
			break;
		case 8:
			version(argc, argv);
			break;
		case '?':
			exit(0);
			break;
		}
	}

	nekomata::logging::Logger log(std::cout, level);
	CLISystem _system(log);
	nekomata::Nekomata nekomata(_system, log);

	if(optind == argc){
		nekomata.parseTimelineStream(std::cin, "<cin>");
	}else{
		nekomata.parseTimelineFile(argv[optind]);
	}

	if(dump){
		nekomata.dump(std::cout);
		return 0;
	}
	nekomata.seek(nekomata.getLastTime());

	return 0;
}

}

int main(int argc, char* argv[]){
	return cli::main(argc, argv);
}
