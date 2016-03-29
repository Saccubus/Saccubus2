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
	virtual Handler<nekomata::system::Shape> drawShape(double x, double y, double z, std::string const& shape, double width, double height, unsigned int color, bool visible, std::string const& pos, bool mask, bool commentmask, double alpha, double rotation, std::string const& mover);
	virtual Handler<nekomata::system::Label> drawText(std::string const& text, double x, double y, double z, double size, std::string const& pos, unsigned int color, bool bold, bool visible, std::string const& filter, double alpha, std::string const& mover);
	virtual void jump(std::string const& id, std::string const& msg, double from, double length, bool _return, std::string const& returnmsg, bool newwindow);
	virtual void jumpCancel();
	virtual void seek(double vpos, std::string const& msg);
	virtual Handler<nekomata::system::Sum> sum(double x, double y, double size, unsigned int color,bool visible, bool enabled, std::string const& pos, bool asc, std::string const& unit, bool buttononly, const std::vector<std::string>& words, bool partial);
	virtual Handler<nekomata::system::SumResult> showResult(double x, double y, unsigned int color,bool visible, std::string const& pos, std::string const& unit, bool asc, const std::vector<Handler<nekomata::system::Sum> >& sum);
	virtual void addButton(std::string const& message, std::string const& mail, double vpos, std::string const& commes, std::string const& commail, bool comvisible, int limit, bool hidden);
	virtual void BGM(std::string const& id, double x, double y, double width, double height, bool visual, double volume);
	virtual void playBGM(int id);
	virtual void stopBGM(int id);
	virtual void addAtPausePoint(double vpos, double wait);
	virtual void addPostRoute(std::string const& match, std::string const& id, std::string const& button);
	virtual void CM(std::string const& id, double time, bool pause, std::string const& link, double volume);
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
