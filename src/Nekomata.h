/*
 * Nekomata.h
 *
 *  Created on: 2012/02/18
 *      Author: psi
 */

#ifndef NEKOMATA_H_
#define NEKOMATA_H_
#include <iostream>
namespace nekomata {

class Adapter{
public:
	Adapter();
	virtual ~Adapter();
	virtual void drawShape();
};

class Nekomata {
public:
	Nekomata();
	virtual ~Nekomata();
public:
	void registAdapter();
	void getAdapter();
	void removeAdapter();
	void parseTimelineStr(std::string& str);
	void parseTimelineFile(std::string& filename);
	void parseProgram(float time, std::string& str);

};

} /* namespace nekomata */
#endif /* NEKOMATA_H_ */
