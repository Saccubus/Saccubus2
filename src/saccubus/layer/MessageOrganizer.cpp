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

item::Comment* MessageOrganizer::organize(const meta::Comment* comment)
{
	item::Comment* const product = new item::Comment(this->commentFactory(), this->shapeFactory());
	product->import(comment);
	/* コマンド欄の処理 */
	for(meta::Comment::MailIterator it= comment->mailBegin(); it != comment->mailEnd(); ++it){
		if(!MailOperation::apply(*it, product))
		{
			log.v(TAG, "Unknwon command: %s", it->c_str());
		}
	}
	/* 置換リスト */
	if(this->replaceTable()){
		product->message(this->replaceTable()->replace(product->message()));
	}
	/* スクリプトによる置換リスト */
	if(this->nekoSystem()){
		NekomataReplaceOperation::apply(this->nekoSystem(), product);
		this->neko()->queueMessage(product->createNekomataMessage());
	}
	return product;
}

}}
