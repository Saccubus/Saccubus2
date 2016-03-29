/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
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
			const float& vpos, std::string const& message, std::string const& mail,
			std::string const& commes, std::string const& commail, bool comvisible, int limit, bool hidden
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
