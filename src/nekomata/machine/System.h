/*
 * System.h
 *
 *  Created on: 2012/02/22
 *      Author: psi
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

namespace nekomata{
namespace machine {

#include "../classdefs.h"

class System {
private:
	nekomata::Adapter& adapter;
public:
	explicit System(nekomata::Adapter& adapter);
	virtual ~System();
public:
	unsigned int commentColor();
	void commentColor(unsigned int color);

	std::string commentPlace();
	void commentPlace(const std::string& place);

	std::string commentSize();
	void commentSize(const std::string& size);

	bool commentInvisible();
	void commentInvisible(bool commentInvisible);

	bool commentReverse();
	void commentReverse(bool commentReverse);

	bool defaultSage();
	void defaultSage(bool defaultSage);

	bool postDisabled();
	void postDisabled(bool postDisabled);

	bool seekDisabled();
	void seekDisabled(bool seekDisabled);

	bool isLoaded();
	void isLoaded(bool isLoaded);

	bool isWide();
	void isWide(bool isWide);

	std::string lastVideo();
	void lastVideo(const std::string& lastVideo);

public:
};

}
}
#endif /* SYSTEM_H_ */
