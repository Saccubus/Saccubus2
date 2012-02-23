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

unsigned int System::getCommentColor()
{
	return adapter.getCommentColor();
}
void System::setCommentColor(unsigned int color)
{
	adapter.setCommentColor(color);
}

std::string System::getCommentPlace()
{
	return adapter.getCommentPlace();
}
void System::setCommentPlace(const std::string& place)
{
	adapter.setCommentPlace(place);
}

std::string System::getCommentSize()
{
	return adapter.getCommentSize();
}
void System::setCommentSize(const std::string& size)
{
	adapter.setCommentSize(size);
}

bool System::getCommentInvisible()
{
	return adapter.getCommentInvisile();
}
void System::setCommentInvisible(bool commentInvisible)
{
	adapter.setCommentInvisible(commentInvisible);
}

bool System::getCommentReverse()
{
	return adapter.getCommentReverse();
}
void System::setCommentReverse(bool commentReverse)
{
	adapter.setCommentReverse(commentReverse);
}
bool System::getDefaultSage()
{
	return adapter.getDefaultSage();
}
void System::setDefaultSage(bool defaultSage)
{
	adapter.setDefaultSage(defaultSage);
}

bool System::getPostDisabled()
{
	return adapter.getPostDisabled();
}
void System::setPostDisabled(bool postDisabled)
{
	adapter.setPostDisabled(postDisabled);
}

bool System::getSeekDisabled()
{
	return adapter.getSeekDisabled();
}
void System::setSeekDisabled(bool seekDisabled)
{
	adapter.setSeekDisabled(seekDisabled);
}

bool System::getIsLoaded()
{
	return adapter.getIsLoaded();
}
void System::setIsLoaded(bool isLoaded)
{
	adapter.setIsLoaded(isLoaded);
}

bool System::getIsWide()
{
	return adapter.getIsWide();
}
void System::setIsWide(bool isWide)
{
	adapter.setIsWide(isWide);
}

std::string System::getLastVideo()
{
	return adapter.getLastVideo();
}
void System::setLastVideo(const std::string& lastVideo)
{
	adapter.setLastVideo(lastVideo);
}

}
}
