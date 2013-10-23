/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#include <nekomata/logging/Logging.h>
#include "item/Button.h"
#include "item/Label.h"
#include "item/Shape.h"
#include "NekomataSystem.h"
#include "CommentLayer.h"

namespace saccubus {
namespace layer {

static const std::string TAG("SaccubusSystem");

NekomataSystem::NekomataSystem(nekomata::logging::Logger& nlog, draw::CommentFactory* commentFactory, draw::ShapeFactory* shapeFactory)
:nekomata::system::System(nlog)
,commentFactory(commentFactory)
,shapeFactory(shapeFactory)
,forkedCommentLayer(0)
,mainCommentLayer(0)
,_scerrnWidth(512)
,_scerrnHeight(384)
{
}

NekomataSystem::~NekomataSystem() {
}

void NekomataSystem::tellCommentLayers(CommentLayer* forkedCommentLayer, CommentLayer* mainCommentLayer)
{
	this->forkedCommentLayer = forkedCommentLayer;
	this->mainCommentLayer = mainCommentLayer;
}
Handler<nekomata::system::Shape> NekomataSystem::drawShape(
		double x, double y, double z, std::string const& shape, double width,
		double height, unsigned int color, bool visible, std::string const& pos,
		bool mask, bool commentmask, double alpha, double rotation,
		std::string const& mover)
{
	Handler<nekomata::system::Shape> _shape(new item::Shape(*this, this->shapeFactory));
	_shape->load(x, y, z, shape, width, height, color, visible, pos, mask, commentmask, alpha, rotation, mover);
	return _shape;
}

Handler<nekomata::system::Label> NekomataSystem::drawText(
		std::string const& text, double x, double y, double z, double size,
		std::string const& pos, unsigned int color, bool bold, bool visible,
		std::string const& filter, double alpha, std::string const& mover) {
	Handler<nekomata::system::Label> label(new item::Label(*this, this->commentFactory));
	label->load(text, x, y, z, size, pos, color, bold, visible, filter, alpha, mover);
	return label;
}

void NekomataSystem::jump(std::string const& id, std::string const& msg,
		double from, double length, bool _return, std::string const& returnmsg,
		bool newwindow) {
	this->log.e(TAG, 0, "Sorry, 'jump' not supported yet!!");
}

void NekomataSystem::jumpCancel() {
	this->log.e(TAG, 0, "Sorry, 'jumpCancel' not supported yet!!");
}

void NekomataSystem::seek(double vpos, std::string const& msg) {
	this->log.e(TAG, 0, "Sorry, 'seek' not supported yet!!");
}

Handler<nekomata::system::Sum> NekomataSystem::sum(double x,
		double y, double size, unsigned int color, bool visible, bool enabled,
		std::string const& pos, bool asc, std::string const& unit,
		bool buttononly, const std::vector<std::string>& words, bool partial) {
	//FIXME: ちゃんと実装すること。
	return System::sum(x, y, size, color, visible, enabled, pos, asc, unit, buttononly, words, partial);
}

Handler<nekomata::system::SumResult> NekomataSystem::showResult(
		double x, double y, unsigned int color, bool visible,
		std::string const& pos, std::string const& unit, bool asc,
		const std::vector<Handler<nekomata::system::Sum> >& sum) {
	//FIXME: ちゃんと実装すること。
	return System::showResult(x, y, color, visible, pos, unit, asc, sum);
}

void NekomataSystem::addButton(
		std::string const& message, std::string const& mail, double vpos,
		std::string const& commes, std::string const& commail, bool comvisible,
		int limit, bool hidden) {
	vpos = vpos != vpos ? currentTime() : vpos;
	/* FIXME: ユーザとオーナー、どうやって区別する？ */
	std::shared_ptr<item::Button> btn(
		new item::Button(
			this->commentFactory, this->shapeFactory, this, this->forkedCommentLayer,
			true, false, true, item::Comment::Forked,
			currentTime(), message, mail,
			commes, commail, comvisible, limit, hidden
			)
	);
	this->forkedCommentLayer->queueComment(btn);
}

void NekomataSystem::BGM(std::string const& id, double x, double y,
		double width, double height, bool visual, double volume) {
}

void NekomataSystem::playBGM(int id) {
	this->log.e(TAG, 0, "Sorry, 'playBGM' not supported yet!!");
}

void NekomataSystem::stopBGM(int id) {
	this->log.e(TAG, 0, "Sorry, 'stopCancel' not supported yet!!");
}

void NekomataSystem::addAtPausePoint(double vpos, double wait) {
	this->log.e(TAG, 0, "Sorry, 'addAtPausePoint' not supported yet!!");
}

void NekomataSystem::addPostRoute(std::string const& match,
		std::string const& id, std::string const& button) {
	this->log.e(TAG, 0, "Sorry, 'addPostRoute' not supported yet!!");
}

void NekomataSystem::CM(std::string const& id, double time, bool pause,
		std::string const& link, double volume) {
	this->log.e(TAG, 0, "Sorry, 'CM' not supported yet!!");
}

void NekomataSystem::playCM(int id) {
	this->log.e(TAG, 0, "Sorry, 'playCM' not supported yet!!");
}
double NekomataSystem::screenWidth()
{
	return _scerrnWidth;
}
double NekomataSystem::screenHeight()
{
	return _scerrnHeight;
}
std::string NekomataSystem::inspect() {
	return "Saccubus::System";
}

void NekomataSystem::onChanged() {
}

void NekomataSystem::setScreenSize(int const w, int const h)
{
	this->_scerrnWidth = w;
	this->_scerrnHeight = h;
}

}}
