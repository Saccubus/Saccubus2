/*
 * Nekomata.h
 *
 *  Created on: 2012/02/18
 *      Author: psi
 */

#ifndef NEKOMATA_H_
#define NEKOMATA_H_
#include <iostream>
#include <vector>
namespace nekomata {

class CommentAdapter
{
public:
	CommentAdapter();
	virtual ~CommentAdapter();
};

class Adapter
{
public:
	Adapter();
	virtual ~Adapter();

	virtual void drawShape(double x, double y, double z, const std::string& shape, double width, double height, unsigned int color, bool visible, const std::string& pos, bool mask, bool commentmask, double alpha, double rotation, const std::string& mover);
	virtual void sum(double x, double y, double size, unsigned int color,bool visible, bool enabled, const std::string& pos, bool asc, std::string& unit,bool buttononly, std::vector<std::string>& words, bool partial);
	virtual void seek(double vpos, const std::string& msg);
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
