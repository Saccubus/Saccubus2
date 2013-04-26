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
#include <map>
#include <vector>
#include <string>
#include <cinamo/Logger.h>
#include <cinamo/ClassUtil.h>

namespace nicomo {
namespace model {

class MetaInfo;
class PlayInfo;
class Thread;

class Video {
private:
	cinamo::Logger& log;
	DEFINE_MEMBER(public, private, std::string, videofile);
	DEFINE_MEMBER(public, private, const MetaInfo*, metaInfo);
	DEFINE_MEMBER(public, private, const PlayInfo*, playInfo);
private:
	std::map<unsigned long long, const Thread*> threadList;
public:
	Video(cinamo::Logger& log);
	virtual ~Video();
public:
	void initVideoFile(const std::string& videofile);
	void initPlayInfo(const std::string& metafile);
	void initMetaInfo(const std::string& metafile);
	void initThread(std::vector<std::string>& threads);
public:
	typedef std::map<unsigned long long, const Thread*>::const_iterator ThreadIterator;
	size_t threadSize() const;
	bool hasThread(unsigned long long thread_id) const;
	ThreadIterator threadBegin() const;
	ThreadIterator threadEnd() const;
	const Thread* thread(unsigned long long thread_id) const;
};

}}
