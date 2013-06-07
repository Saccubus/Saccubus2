/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once
#include <cinamo/Handler.h>
#include <nekomata/system/System.h>
#include <deque>
#include "../draw/CommentFactory.h"
#include "../draw/ShapeFactory.h"
namespace saccubus {
namespace layer {
using cinamo::Handler;

class NekomataSystem: public nekomata::system::System {
	draw::CommentFactory* const commentFactory;
	draw::ShapeFactory* const shapeFactory;
private:
	CommentLayer* forkedCommentLayer;
	CommentLayer* mainCommentLayer;
public:
	NekomataSystem(nekomata::logging::Logger& nlog, draw::CommentFactory* commentFactory, draw::ShapeFactory* shapeFactory);
	virtual ~NekomataSystem();
public:
	void tellCommentLayers(CommentLayer* forkedCommentLayer, CommentLayer* mainCommentLayer);
public: /* スクリプトから参照される */
	virtual Handler<nekomata::system::Shape> drawShape(double x, double y, double z, const std::string& shape, double width, double height, unsigned int color, bool visible, const std::string& pos, bool mask, bool commentmask, double alpha, double rotation, const std::string& mover);
	virtual Handler<nekomata::system::Label> drawText(const std::string& text, double x, double y, double z, double size, const std::string& pos, unsigned int color, bool bold, bool visible, const std::string& filter, double alpha, const std::string& mover);
	virtual void jump(const std::string& id, const std::string& msg, double from, double length, bool _return, const std::string& returnmsg, bool newwindow);
	virtual void jumpCancel();
	virtual void seek(double vpos, const std::string& msg);
	virtual Handler<nekomata::system::Sum> sum(double x, double y, double size, unsigned int color,bool visible, bool enabled, const std::string& pos, bool asc, const std::string& unit, bool buttononly, const std::vector<std::string>& words, bool partial);
	virtual Handler<nekomata::system::SumResult> showResult(double x, double y, unsigned int color,bool visible, const std::string& pos, const std::string& unit, bool asc, const std::vector<Handler<nekomata::system::Sum> >& sum);
	virtual void addButton(const std::string& message, const std::string& mail, double vpos, const std::string& commes, const std::string& commail, bool comvisible, int limit, bool hidden);
	virtual void BGM(const std::string& id, double x, double y, double width, double height, bool visual, double volume);
	virtual void playBGM(int id);
	virtual void stopBGM(int id);
	virtual void addAtPausePoint(double vpos, double wait);
	virtual void addPostRoute(const std::string& match, const std::string& id, const std::string& button);
	virtual void CM(const std::string& id, double time, bool pause, const std::string& link, double volume);
	virtual void playCM(int id);
	double screenWidth();
	double screenHeight();
protected: /* INFO: 各サブシステムで再実装すること。 */
	virtual std::string inspect();
	void onChanged();
private: /* レイヤとの連携 */
	int _scerrnWidth;
	int _scerrnHeight;
public:
	void setScreenSize(int const w, int const h);
};

}}
