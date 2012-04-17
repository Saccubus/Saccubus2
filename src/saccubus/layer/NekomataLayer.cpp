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

#include "NekomataLayer.h"
#include "../logging/Logger.h"
#include <nekomata/logging/Logging.h>
#include <iostream>

namespace saccubus {
namespace layer {

NekomataLayer::NekomataLayer(logging::Logger& log, nekomata::logging::Logger& nlog, draw::Renderer* renderer)
:nekomata::system::System(nlog)
,Layer(log, renderer)
{
	// TODO Auto-generated constructor stub

}

NekomataLayer::~NekomataLayer() {
}

nekomata::util::Handler<nekomata::system::Shape> NekomataLayer::drawShape(
		double x, double y, double z, const std::string& shape, double width,
		double height, unsigned int color, bool visible, const std::string& pos,
		bool mask, bool commentmask, double alpha, double rotation,
		const std::string& mover) {
}

nekomata::util::Handler<nekomata::system::Label> NekomataLayer::drawText(
		const std::string& text, double x, double y, double z, double size,
		const std::string& pos, unsigned int color, bool bold, bool visible,
		const std::string& filter, double alpha, const std::string& mover) {
}

void NekomataLayer::jump(const std::string& id, const std::string& msg,
		double from, double length, bool _return, const std::string& returnmsg,
		bool newwindow) {
}

void NekomataLayer::jumpCancel() {
}

void NekomataLayer::seek(double vpos, const std::string& msg) {
}

nekomata::util::Handler<nekomata::system::Sum> NekomataLayer::sum(double x,
		double y, double size, unsigned int color, bool visible, bool enabled,
		const std::string& pos, bool asc, const std::string& unit,
		bool buttononly, const std::vector<std::string>& words, bool partial) {
}

nekomata::util::Handler<nekomata::system::SumResult> NekomataLayer::showResult(
		double x, double y, unsigned int color, bool visible,
		const std::string& pos, const std::string& unit, bool asc,
		std::vector<nekomata::util::Handler<nekomata::system::Sum> > sum) {
}

nekomata::util::Handler<nekomata::system::Replace> NekomataLayer::replace(
		const std::string& src, const std::string& dst, bool enabled,
		const std::string& target, bool fill, bool partial, unsigned int color,
		const std::string& size, const std::string& pos) {
}

nekomata::util::Handler<nekomata::system::Button> NekomataLayer::addButton(
		const std::string& message, const std::string& mail, double vpos,
		const std::string& commes, const std::string& commail, bool comvisible,
		int limit, bool hidden) {
}

void NekomataLayer::BGM(const std::string& id, double x, double y,
		double width, double height, bool visual, double volume) {
}

void NekomataLayer::playBGM(int id) {
}

void NekomataLayer::stopBGM(int id) {
}

void NekomataLayer::addAtPausePoint(double vpos, double wait) {
}

void NekomataLayer::addPostRoute(const std::string& match,
		const std::string& id, const std::string& button) {
}

void NekomataLayer::CM(const std::string& id, double time, bool pause,
		const std::string& link, double volume) {
}

void NekomataLayer::playCM(int id) {
}

std::tr1::shared_ptr<const nekomata::system::Comment> NekomataLayer::nextComment() {
}

std::string NekomataLayer::inspect() {
}

void NekomataLayer::onChanged() {
}

/******************************************************************************************************************
 * レイヤ
 ******************************************************************************************************************/
void NekomataLayer::draw(float vpos)
{
}

}}
