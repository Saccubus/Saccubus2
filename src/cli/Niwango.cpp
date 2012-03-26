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
#include <exception>
#include <nekomata/Nekomata.h>

#include "CLISystem.h"

using namespace std;
using namespace std::tr1;

const std::string TAG("CLI");

namespace cli{

void usage(int argc, char* argv[]){
	static const std::string USAGE_TAB="    ";
	cout << "Usage: " << basename(argv[0]) << " [switches] [--] [programfile]" << endl;
	cout << USAGE_TAB << std::left << std::setw(15) << "--trace" << "set log level." << endl;
	cout << USAGE_TAB << std::left << std::setw(15) << "--verbose" << "set log level." << endl;
	cout << USAGE_TAB << std::left << std::setw(15) << "--debug"<<"set log level." << endl;
	cout << USAGE_TAB << std::left << std::setw(15) << "--warning"<<"set log level." << endl;
	cout << USAGE_TAB << std::left << std::setw(15) << "--error"<<"set log level." << endl;
	cout << USAGE_TAB << std::left << std::setw(15) << "--dump"<<"output dump of AST, then exit." << endl;
	cout << USAGE_TAB << std::left << std::setw(15) << "--version"<<"output the version, then exit." << endl;
	cout << USAGE_TAB << std::left << std::setw(15) << "-h, --help"<<"output the help, then exit." << endl;
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
	nekomata::logging::Logger::Level level = nekomata::logging::Logger::WARNING_;
	bool dump = false;
	while(1){
		int opt = getopt_long(argc, argv, "h", ARG_OPTIONS, &indexptr);
		if(opt < 0){
			break;
		}
		switch(opt)
		{
		case 1:
			level = nekomata::logging::Logger::TRACE_;
			break;
		case 2:
			level = nekomata::logging::Logger::VERBOSE_;
			break;
		case 3:
			level = nekomata::logging::Logger::DEBUG_;
			break;
		case 4:
			level = nekomata::logging::Logger::WARNING_;
			break;
		case 5:
			level = nekomata::logging::Logger::ERROR_;
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
	log.t(TAG, 0, "Logger created. Level: %d", level);
	CLISystem _system(log, std::cout);
	nekomata::Nekomata nekomata(_system, log);

	if(optind == argc){
		log.t(TAG, 0, "Parsing timeline from input stream.");
		nekomata.parseTimelineStream(std::cin, "<cin>");
	}else{
		log.t(TAG, 0, "Parsing timeline from file: %s", argv[optind]);
		nekomata.parseTimelineFile(argv[optind]);
	}

	if(dump){
		log.t(TAG, 0, "Dumping timeline.");
		nekomata.dump(std::cout);
		return 0;
	}
	log.t(TAG, 0, "Executing...");
	nekomata.seek(nekomata.getLastTime());

	return 0;
}

}

int main(int argc, char* argv[]){
	try{
		const int resultCode = cli::main(argc, argv);
		return resultCode;
	} catch (nekomata::logging::Exception& e){
		std::cout << "Nekomata Exception catch: " << e.what() << std::endl;
		return -1;
	} catch (std::exception& ex){
		std::cout << "Default Exception catch: " << ex.what() << std::endl;
		return -2;
	} catch(...){
		std::cout << "[FIXME] Unkown exception caught..." << std::endl;
		return -3;
	}
}
