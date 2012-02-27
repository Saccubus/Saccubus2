/*
 * System.cpp
 *
 *  Created on: 2012/02/22
 *      Author: psi
 */

#include "../Nekomata.h"
#include "System.h"
#include "../object/Object.h"
#include "../object/Heap.h"

namespace nekomata{
namespace machine {

System::System(nekomata::Adapter& adapter):
	adapter(adapter){
	// TODO Auto-generated constructor stub

}

System::~System() {
	// TODO Auto-generated destructor stub
}

unsigned int System::commentColor()
{
	return adapter.commentColor();
}
void System::commentColor(unsigned int color)
{
	adapter.commentColor(color);
}

std::string System::commentPlace()
{
	return adapter.commentPlace();
}
void System::commentPlace(const std::string& place)
{
	adapter.commentPlace(place);
}

std::string System::commentSize()
{
	return adapter.commentSize();
}
void System::commentSize(const std::string& size)
{
	adapter.commentSize(size);
}

bool System::commentInvisible()
{
	return adapter.commentInvisible();
}
void System::commentInvisible(bool commentInvisible)
{
	adapter.commentInvisible(commentInvisible);
}

bool System::commentReverse()
{
	return adapter.commentReverse();
}
void System::commentReverse(bool commentReverse)
{
	adapter.commentReverse(commentReverse);
}
bool System::defaultSage()
{
	return adapter.defaultSage();
}
void System::defaultSage(bool defaultSage)
{
	adapter.defaultSage(defaultSage);
}

bool System::postDisabled()
{
	return adapter.postDisabled();
}
void System::postDisabled(bool postDisabled)
{
	adapter.postDisabled(postDisabled);
}

bool System::seekDisabled()
{
	return adapter.seekDisabled();
}
void System::seekDisabled(bool seekDisabled)
{
	adapter.seekDisabled(seekDisabled);
}

bool System::isLoaded()
{
	return adapter.isLoaded();
}
void System::isLoaded(bool isLoaded)
{
	adapter.isLoaded(isLoaded);
}

bool System::isWide()
{
	return adapter.isWide();
}
void System::isWide(bool isWide)
{
	adapter.isWide(isWide);
}

std::string System::lastVideo()
{
	return adapter.lastVideo();
}
void System::lastVideo(const std::string& lastVideo)
{
	adapter.lastVideo(lastVideo);
}

}
}
