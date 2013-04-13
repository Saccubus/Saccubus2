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
#pragma once
#include "Comment.h"

namespace saccubus {
namespace layer {
namespace item {

class Button: public saccubus::layer::item::Comment {
	DEFINE_MEMBER(private, private, unsigned int, buttonColor);
	DEFINE_MEMBER(private, private, std::string, commes);
	DEFINE_MEMBER(private, private, std::string, commail);
	DEFINE_MEMBER(private, private, bool, comvisible);
	DEFINE_MEMBER(private, private, int, limit);
	DEFINE_MEMBER(private, private, bool, hidden);
private:
	int isClicked;
private:
	NekomataSystem* const nekoSystem;
	CommentLayer* const postLayer;
private:
	float btnRelX;
	float btnRelY;
	draw::Sprite::Handler<draw::Sprite> leftSprite;
	draw::Sprite::Handler<draw::Sprite> textSprite;
	draw::Sprite::Handler<draw::Sprite> rightSprite;

	draw::Sprite::Handler<draw::Sprite> buttonSprite;
	void constructComment(std::shared_ptr<saccubus::draw::Context> ctx);
private:
	Button();
	Button(const Button& other);
	Button& operator = (const Button& other);
public:
	Button(
			draw::CommentFactory* commentFactory, draw::ShapeFactory* shapeFactory,
			NekomataSystem* const nekoSystem, CommentLayer* const postLayer,
			bool fromButton, bool isYourPost, const bool isPremium, enum Layer layer,
			const float& vpos, const std::string& message, const std::string& mail,
			const std::string& commes, const std::string& commail, bool comvisible, int limit, bool hidden
			);
	virtual ~Button() noexcept = default;
public:
	virtual bool isButton() const;
public:
	virtual bool onClick(int relX, int relY);
	virtual void draw(std::shared_ptr<saccubus::draw::Context> ctx, int x, int y);
protected:
	virtual draw::Sprite::Handler<draw::Sprite> createSprite(std::shared_ptr<saccubus::draw::Context> ctx);
};

}}}
