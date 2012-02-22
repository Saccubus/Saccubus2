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

class ChatAdapter
{
public:
	explicit ChatAdapter();
	virtual ~ChatAdapter();
};

class Adapter
{
public:
	explicit Adapter();
	virtual ~Adapter();

	virtual void drawShape(double x, double y, double z, const std::string& shape, double width, double height, unsigned int color, bool visible, const std::string& pos, bool mask, bool commentmask, double alpha, double rotation, const std::string& mover);
	virtual void sum(double x, double y, double size, unsigned int color,bool visible, bool enabled, const std::string& pos, bool asc, std::string& unit,bool buttononly, std::vector<std::string>& words, bool partial);
	virtual void showResult(double x, double y, unsigned int color, bool visible, const std::string& pos, const std::string& unit, bool asc, std::vector<std::string>& sum);
	virtual void replace(const std::string& src, const std::string& dest, bool enabled, const std::string& target, bool fill, bool partial, unsigned int color, double size, const std::string& pos);
	virtual void seek(double vpos, const std::string& msg);
	virtual void jump(const std::string& id, const std::string& msg, double from, double length, bool _return, const std::string& returnmsg, bool newwindow);
	virtual double screenWidth();
	virtual double screenHeight();
	virtual void addButton(const std::string& message, const std::string& mail, double vpos, const std::string& commes, const std::string& commail, bool comvisible, int limit, bool hidden);
	virtual double playStartTime();
	virtual void BGM(const std::string& id, double x, double y, double width, double height, bool visual, double volume);
	virtual void playBGM(int id);
	virtual void stopBGM(int id);
	virtual void addAtPausePoint(double vpos, double wait);
	virtual void addPostRoute(const std::string& match, const std::string& id, const std::string& button);
	virtual void CM(const std::string& id, double time, bool pause, const std::string& link, double volume);
	virtual void playCM(int id);
//
	virtual unsigned int getCommentColor();
	virtual void setCommentColor(unsigned int color);
	virtual std::string getCommentPlace();
	virtual void setCommentPlace(const std::string& place);
	virtual std::string getCommentSize();
	virtual void setCommentSize(const std::string& size);
	virtual bool getCommentInvisile();
	virtual void setCommentInvisible(bool invisible);
	virtual double getCommentReverse();
	virtual void setCommentReverse(double rev);
	virtual bool getDefaultSage();
	virtual void setDefaultSage(bool sage);
	virtual bool getPostDisabled();
	virtual void setPostDisabled(bool disabled);
	virtual bool getSeekDisabled();
	virtual void setSeekDisabled(bool disabled);
	virtual bool getIsLoaded();
	virtual void setIsLoaded(bool loaded);
	virtual bool getIsWide();
	virtual void setIsWide(bool isWide);
	virtual std::string& getLastVideo();
	virtual void setLastVideo(const std::string& last);
};

class Nekomata {
private:
	Adapter* adapter;
public:
	explicit Nekomata();
	virtual ~Nekomata();
public:
	void registAdapter(Adapter* adapter);
	void getAdapter();
	void removeAdapter();
	void parseTimelineStr(std::string& str);
	void parseTimelineFile(std::string& filename);
	void parseProgram(float time, std::string& str);

};

}
#endif /* NEKOMATA_H_ */
