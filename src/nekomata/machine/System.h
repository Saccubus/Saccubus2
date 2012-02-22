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

class System {
private:
	nekomata::Adapter& adapter;
public:
	explicit System(nekomata::Adapter& adapter);
	virtual ~System();
public:
	unsigned int getCommentColor();
	void setCommentColor(unsigned int color);

	std::string getCommentPlace();
	void setCommentPlace(const std::string& place);

	std::string getCommentSize();
	void setCommentSize(const std::string& size);

	bool getCommentInvisible();
	void setCommentInvisible(bool commentInvisible);

	bool getCommentReverse();
	void setCommentReverse(bool commentReverse);

	bool getDefaultSage();
	void setDefaultSage(bool defaultSage);

	bool getPostDisabled();
	void setPostDisabled(bool postDisabled);

	bool getSeekDisabled();
	void setSeekDisabled(bool seekDisabled);

	bool getIsLoaded();
	void setIsLoaded(bool isLoaded);

	bool getIsWide();
	void setIsWide(bool isWide);

	std::string getLastVideo();
	void setLastVideo(const std::string& lastVideo);

public:
};

}
}
#endif /* SYSTEM_H_ */
