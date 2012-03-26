/*
 * Saccubus.h
 *
 *  Created on: 2012/03/20
 *      Author: psi
 */

#ifndef SACCUBUS_H_
#define SACCUBUS_H_

#include <string>
#include <map>

namespace saccubus {

class Saccubus {
private:
	const std::string progPath;
	std::map<std::string, std::string> resolveOpts;
public:
	Saccubus(const int argc, const char** argv);
	virtual ~Saccubus();

	void onMeasure(const int w, const int h, int& measuredW, int& measuredH);
};

}
#endif /* SACCUBUS_H_ */
