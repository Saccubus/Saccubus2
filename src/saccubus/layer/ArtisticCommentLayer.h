/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once
#include <memory>
#include <set>
#include <vector>
#include <cinamo/ClassUtil.h>
#include "CommentLayer.h"

namespace saccubus {
namespace layer {

class ArtisticCommentLayer: public saccubus::layer::CommentLayer {
private:
	class Slot{
		DEFINE_MEMBER(public, public, int, y);
		DEFINE_MEMBER(public, public, int, x);
		DEFINE_MEMBER(public, public, float, width);
		DEFINE_MEMBER(public, public, float, height);
		DEFINE_MEMBER(public, private, std::shared_ptr<item::Comment>, comment);
	private:
		Slot& operator=(const Slot& other){return *this;};
		Slot(const Slot& other) = delete;
	public:
		Slot(std::shared_ptr<item::Comment> comment);
		virtual ~Slot();
	public: /* setで比較する時用 */
		bool operator !=(const Slot& other);
		bool operator ==(const Slot& other);
	public:
		struct EndTimeComparator{
			bool operator() (const std::shared_ptr<const Slot>& a, const std::shared_ptr<const Slot>& b);
			bool operator() (const float& a, const std::shared_ptr<const Slot>& b);
			bool operator() (const std::shared_ptr<const Slot>& a, const float& b);
		};
	};
private:
	static const float CommentAheadTime;
private:
	std::vector<std::shared_ptr<item::Comment> > deployQueue;
	typedef std::vector<std::shared_ptr<item::Comment> >::iterator DeployQueueIterator;
	std::vector<std::shared_ptr<Slot> > comments;
	typedef std::vector<std::shared_ptr<Slot> >::iterator CommentIterator;
	typedef std::vector<std::shared_ptr<Slot> >::const_iterator CommentConstIterator;
public:
	ArtisticCommentLayer(cinamo::Logger& log, const std::map<std::string, std::string> & config, layer::ThreadLayer* thread, bool isForked);
	virtual ~ArtisticCommentLayer();
	float last;
public:
	virtual void draw(std::shared_ptr<saccubus::draw::Context> ctx, float vpos);
	virtual bool onClick(int x, int y);
	virtual void queueComment(std::shared_ptr<item::Comment> comment);
private:
	void deploy(std::shared_ptr<saccubus::draw::Context> ctx, const float vpos, std::shared_ptr<Slot> layout);
	float getX(float vpos, float screenWidth, std::shared_ptr<const Slot> layout);
};

}}
