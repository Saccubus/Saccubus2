/**
 * Saccubus
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <nekomata/logging/Logging.h>
#include "item/Button.h"
#include "item/Label.h"
#include "item/Shape.h"
#include "NekomataSystem.h"

namespace saccubus {
namespace layer {

static const std::string TAG("SaccubusSystem");

NekomataSystem::NekomataSystem(nekomata::logging::Logger& nlog, draw::CommentFactory* commentFactory, draw::ShapeFactory* shapeFactory)
:nekomata::system::System(nlog)
{
	this->commentFactory(commentFactory);
	this->shapeFactory(shapeFactory);
}

NekomataSystem::~NekomataSystem() {
	// TODO Auto-generated destructor stub
}

nekomata::util::Handler<nekomata::system::Shape> NekomataSystem::drawShape(
		double x, double y, double z, const std::string& shape, double width,
		double height, unsigned int color, bool visible, const std::string& pos,
		bool mask, bool commentmask, double alpha, double rotation,
		const std::string& mover)
{
	nekomata::util::Handler<nekomata::system::Shape> _shape(new item::Shape(*this, this->shapeFactory()));
	_shape->load(x, y, z, shape, width, height, color, visible, pos, mask, commentmask, alpha, rotation, mover);
	return _shape;
}

nekomata::util::Handler<nekomata::system::Label> NekomataSystem::drawText(
		const std::string& text, double x, double y, double z, double size,
		const std::string& pos, unsigned int color, bool bold, bool visible,
		const std::string& filter, double alpha, const std::string& mover) {
	nekomata::util::Handler<nekomata::system::Label> label(new item::Label(*this, this->commentFactory()));
	label->load(text, x, y, z, size, pos, color, bold, visible, filter, alpha, mover);
	return label;
}

void NekomataSystem::jump(const std::string& id, const std::string& msg,
		double from, double length, bool _return, const std::string& returnmsg,
		bool newwindow) {
	this->log.e(TAG, 0, "Sorry, 'jump' not supported yet!!");
}

void NekomataSystem::jumpCancel() {
	this->log.e(TAG, 0, "Sorry, 'jumpCancel' not supported yet!!");
}

void NekomataSystem::seek(double vpos, const std::string& msg) {
	this->log.e(TAG, 0, "Sorry, 'seek' not supported yet!!");
}

nekomata::util::Handler<nekomata::system::Sum> NekomataSystem::sum(double x,
		double y, double size, unsigned int color, bool visible, bool enabled,
		const std::string& pos, bool asc, const std::string& unit,
		bool buttononly, const std::vector<std::string>& words, bool partial) {
}

nekomata::util::Handler<nekomata::system::SumResult> NekomataSystem::showResult(
		double x, double y, unsigned int color, bool visible,
		const std::string& pos, const std::string& unit, bool asc,
		std::vector<nekomata::util::Handler<nekomata::system::Sum> > sum) {
}

void NekomataSystem::addButton(
		const std::string& message, const std::string& mail, double vpos,
		const std::string& commes, const std::string& commail, bool comvisible,
		int limit, bool hidden) {
	vpos = vpos != vpos ? currentTime() : vpos;
	log.e(TAG, 0,
			"addButton(message: %s, mail: %s, vpos: %f, commes: %s, commail: %s, comvisible: %d, limit: %d, hidden:%d)",
			message.c_str(), mail.c_str(), vpos, commes.c_str(), commail.c_str(), comvisible, limit, hidden
			);
	/* FIXME: ユーザとオーナー、どうやって区別する？ */
	item::Button* btn = new item::Button(this->commentFactory(), this->shapeFactory());
	btn->vpos(vpos);
	btn->comvisible(comvisible);
	btn->commail(commail);
	btn->commes(commes);
	btn->limit(limit);
	btn->hidden(hidden);
}

void NekomataSystem::BGM(const std::string& id, double x, double y,
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

void NekomataSystem::addPostRoute(const std::string& match,
		const std::string& id, const std::string& button) {
	this->log.e(TAG, 0, "Sorry, 'addPostRoute' not supported yet!!");
}

void NekomataSystem::CM(const std::string& id, double time, bool pause,
		const std::string& link, double volume) {
	this->log.e(TAG, 0, "Sorry, 'CM' not supported yet!!");
}

void NekomataSystem::playCM(int id) {
	this->log.e(TAG, 0, "Sorry, 'playCM' not supported yet!!");
}
double NekomataSystem::screenWidth()
{
	return 640; //KARI
}
double NekomataSystem::screenHeight()
{
	return 360; //KARI
}
std::string NekomataSystem::inspect() {
	return "Saccubus::NekomataSystem";
}

void NekomataSystem::onChanged() {
}


}}
