//============================================================================
// Name        : nicovideo.cpp
// Author      : PSI
// Version     :
// Copyright   : 2007-2011 psi
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "../saccubus/logging/Exception.h"
using namespace std;

namespace cli{
	int main(int argc, char** argv)
	{

		return 0;
	}
}

int main(int argc, char** argv) {
	try {
		return cli::main(argc, argv);
	} catch (saccubus::logging::Exception& e) {
		std::cerr << "Saccubus Exception Catched." << e.what() << std::endl;
		return -1;
	} catch (std::exception& e) {
		std::cerr << "Standard Exception Catched." << e.what() << std::endl;
		return -2;
	} catch(...) {
		std::cerr << "Unknwon Exception Catched" << std::endl;
		return -3;
	}
}
