/**
 * Nekomata
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <getopt.h>
#include <libgen.h>
#include <iomanip>
#include <cstdlib>
#include <exception>
#include <nekomata/Nekomata.h>
#include <nekomata/logging/Exception.h>
#include "TimeLineParser.h"
#include "../nekomata/tree/Node.h"

#include "CLISystem.h"

using namespace std;

const std::string TAG("CLI");

namespace cli{

void usage(int argc, char* argv[]){
	static const std::string USAGE_TAB="    ";
	cout << "Usage: " << basename(argv[0]) << " [switches] [--] [programfile]" << endl;
	cout << USAGE_TAB << std::left << std::setw(15) << "--trace" << "set log level." << endl;
	cout << USAGE_TAB << std::left << std::setw(15) << "--verbose" << "set log level." << endl;
	cout << USAGE_TAB << std::left << std::setw(15) << "--debug"<<"set log level." << endl;
	cout << USAGE_TAB << std::left << std::setw(15) << "--warning"<<"set log level." << endl;
	cout << USAGE_TAB << std::left << std::setw(15) << "--info"<<"set log level." << endl;
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
		{"info", no_argument, 0, 5},
		{"error", no_argument, 0, 6},
		{"dump", no_argument, 0, 7},
		{"help", no_argument, 0, 8},
		{"version", no_argument, 0, 9},
		{0,0,0,0}
};

int main(int argc, char* argv[]){

	int indexptr=0;
	cinamo::Logger::Level level = cinamo::Logger::WARN_;
	bool dump = false;
	while(1){
		int opt = getopt_long(argc, argv, "h", ARG_OPTIONS, &indexptr);
		if(opt < 0){
			break;
		}
		switch(opt)
		{
		case 1:
			level = cinamo::Logger::TRACE_;
			break;
		case 2:
			level = cinamo::Logger::VERBOSE_;
			break;
		case 3:
			level = cinamo::Logger::DEBUG_;
			break;
		case 4:
			level = cinamo::Logger::INFO_;
			break;
		case 5:
			level = cinamo::Logger::WARN_;
			break;
		case 6:
			level = cinamo::Logger::ERROR_;
			break;
		case 7:
			dump = true;
			break;
		case 8:
		case 'h':
			usage(argc, argv);
			break;
		case 9:
			version(argc, argv);
			break;
		case '?':
			exit(0);
			break;
		}
	}

	cinamo::Logger plog(std::cout, level);
	nekomata::logging::Logger log(plog);
	log.t(TAG, 0, "Logger created. Level: %d", level);
	std::multimap<float, std::shared_ptr<const nekomata::system::Message> > commentLine;

	if(optind == argc){
		log.t(TAG, 0, "Parsing timeline from input stream.");
		commentLine = TimeLineParser(std::cin, "<CIN>").parse();
	}else{
		log.t(TAG, 0, "Parsing timeline from file: %s", argv[optind]);
		std::ifstream fst(argv[optind]);
		commentLine = TimeLineParser(fst, argv[optind]).parse();
	}

	CLISystem _system(log, std::cout);
	nekomata::Nekomata nekomata(_system, log);

	float last = 0.0f;
	if(dump){
		log.t(TAG, 0, "Dumping timeline.");
		nekomata::logging::Dumper dumper(std::cout);
		for(std::multimap<float, std::shared_ptr<const nekomata::system::Message> >::const_iterator it = commentLine.begin(); it != commentLine.end(); ++it){
			std::cout << "time: " << it->first << std::endl;
			std::cout.flush();
			if(it->second->type == nekomata::system::Message::SCRIPT){
				std::dynamic_pointer_cast<const nekomata::system::Script>(it->second)->node()->dump(dumper);
			}else{
				std::cout << "Comment: " << std::dynamic_pointer_cast<const nekomata::system::Comment>(it->second)->message() << std::endl;
			}
		}
		return 0;
	}else{
		for(std::multimap<float, std::shared_ptr<const nekomata::system::Message> >::const_iterator it = commentLine.begin(); it != commentLine.end(); ++it){
			nekomata.queueMessage(it->second);
			last = it->first;
		}
	}
	log.t(TAG, 0, "Executing...");
	for(float t = 0; t<=last+1; t+=(1/30.0f)){
		nekomata.seek(t);
	}

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
