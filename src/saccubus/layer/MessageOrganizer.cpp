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

#include <nekomata/Nekomata.h>
#include "MessageOrganizer.h"
#include "MessageOrganizerOperation.h"
#include "../meta/Comment.h"
#include "../meta/ReplaceTable.h"
#include "item/Comment.h"
#include "item/Button.h"

namespace saccubus {
namespace layer {

static const std::string TAG("MsgOrganizer");

MessageOrganizer::MessageOrganizer(logging::Logger& log, draw::CommentFactory* commentFactory, draw::ShapeFactory* shapeFactory, const meta::ReplaceTable* replaceTable, nekomata::Nekomata* neko, layer::NekomataSystem* nekomataSystem)
:log(log)
{
	this->commentFactory(commentFactory);
	this->shapeFactory(shapeFactory);
	this->replaceTable(replaceTable);
	this->neko(neko);
	this->nekoSystem(nekomataSystem);
}


MessageOrganizer::~MessageOrganizer() {
}

std::tr1::shared_ptr<item::Comment> MessageOrganizer::organize(const meta::Comment* comment)
{
	const std::tr1::shared_ptr<item::Comment> product = std::tr1::shared_ptr<item::Comment>(new item::Comment(this->commentFactory(), this->shapeFactory()));
	product->import(comment);
	rewrite(product);
	return product;
}
void MessageOrganizer::rewrite(std::tr1::shared_ptr<item::Comment> comment)
{
	/* コマンド欄の処理 */
	for(item::Comment::MailIterator it= comment->mailBegin(); it != comment->mailEnd(); ++it){
		if(!MailOperation::apply(*it, comment))
		{
			log.v(TAG, "Unknwon command: %s", it->c_str());
		}
	}
	comment->fixTime();
	/* 置換リスト */
	if(this->replaceTable()){
		comment->message(this->replaceTable()->replace(comment->message()));
	}
	/* スクリプトによる置換リスト */
	if(this->nekoSystem()){
		NekomataReplaceOperation::apply(this->nekoSystem(), comment);
		this->neko()->queueMessage(comment->createNekomataMessage());
	}
}

}}
