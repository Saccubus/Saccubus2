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

#include "CommentPipeLine.h"
#include "../../meta/Comment.h"
#include "../../meta/ReplaceTable.h"

namespace saccubus {
namespace layer {
namespace item {

static const std::string TAG("CommentProcessingFlow");

CommentPipeLine::CommentPipeLine(logging::Logger& log, meta::ReplaceTable* replaceTable, NekomataLayer* nekomataLayer)
:log(log)
,replaceTable(replaceTable)
,nekomataLayer(nekomataLayer)
{
}

CommentPipeLine::~CommentPipeLine()
{
}

Comment* CommentPipeLine::process(const meta::Comment* comment)
{
	Comment* const product = new Comment(comment);
	for(meta::Comment::MailIterator it= comment->mailBegin(); it != comment->mailEnd(); ++it){
		if(!MailOperation::apply(*it, product))
		{
			log.v(TAG, "Unknwon command: %s", it->c_str());
		}
	}

	if(replaceTable){
		product->message(replaceTable->replace(product->message()));
	}
	if(nekomataLayer){
		nekomataLayer->replace(product);
	}

	return product;
}

}}}
