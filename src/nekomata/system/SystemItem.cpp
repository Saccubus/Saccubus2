/*
 * SystemItem.cpp
 *
 *  Created on: 2012/03/08
 *      Author: psi
 */
#include <nekomata/logging/Logging.h>
#include <nekomata/system/System.h>
#include "../util/StringUtil.h"

namespace nekomata{
namespace system {

const std::string TAG("SystemItem");

void SystemItem::incNativeRef(){
	++nativeRef;
};
void SystemItem::decNativeRef(){
	--nativeRef;
	if(nativeRef < 0){
		system.log.e("SystemItem", 0, "[BUG] Native ref = %d < 0 on %s", nativeRef, inspect().c_str());
	}
};

void SystemItem::onChanged()
{
	system.log.v(TAG, 0, "prop changed: %s", inspect().c_str());
}

std::string Shape::inspect()
{
	return nekomata::util::format(
			"Shape(x: %f, y: %f, z: %f, shape: %s, width: %f, height: %f, color:%x, visible: %d, pos: %s, mask: %d, commentmask: %d, alpha: %f, rotation:%f, mover: %s",
			x(), y(), z(), shape().c_str(), width(), height(), color(), visible(), pos().c_str(), mask(), commentmask(), alpha(), rotation(), mover().c_str()
			);
}


std::string Label::inspect()
{
	return nekomata::util::format(
		"Label(text:%s , x: %f, y: %f, z: %f, size: %f, pos: %s, color: %d, bold: %d, visible: %d, filter: %s, alpha: %f, mover: %s)",
		text().c_str(), x(), y(), z(), size(), pos().c_str(), color(), bold(), visible(), filter().c_str(), alpha(), mover().c_str()
		);

}
std::string Sum::inspect()
{
	return nekomata::util::format(
		"Sum(x: %f, y: %f, size: %f, color: %x, visible: %d, enabled: %d, pos: %s, asc: %d, unit: %s, buttononly: %d, words: %d word(s), partial: %d)",
		x(), y(), size(), color(), visible(), enabled(), pos().c_str(), asc(), unit().c_str(), buttononly(), words().size(), partial()
		);
}
std::string SumResult::inspect()
{
	return nekomata::util::format(
		"SumResult(x: %f, y: %f, color: %x, visible: %d, pos: %s, asc: %d, unit: %s, sum: %ditem(s))",
		x(), y(), color(), visible(), pos().c_str(), asc(), unit().c_str(), sum().size()
	);
}
std::string Replace::inspect()
{
	return nekomata::util::format(
		"Replace(src: %s, dst: %s, enabled: %d, target: %s, fill: %d, partial: %d, color: %x, size: %s, pos: %s)",
		src().c_str(), dst().c_str(), enabled(), target().c_str(), fill(), partial(), color(), size().c_str(), pos().c_str()
	);
}
std::string Button::inspect()
{
	return nekomata::util::format(
		"Button(message: %s, mail: %s, vpos: %f, commes: %s, commail: %s, comvisible: %d, limit: %d, hidden:%d)",
		message().c_str(), mail().c_str(), vpos(), commes().c_str(), commail().c_str(), comvisible(), limit(), hidden()
	);
}

#define REF_TEMPLATE(clazz, valid_expr)\
void clazz::decNativeRef()\
{\
	SystemItem::decNativeRef();\
	if(getNativeRef() == 0 && !(valid_expr)){\
		system.log.v(TAG, 0, "%s was not referenced any more, so deleted.", inspect().c_str());\
		system.unregist(this);\
	}\
}\
void clazz::incNativeRef()\
{\
	if(getNativeRef() <= 0){\
		system.log.v(TAG, 0, "%s created and registed.", #clazz);\
		system.regist(this);\
	}\
	SystemItem::incNativeRef();\
}

REF_TEMPLATE(Shape, visible())
REF_TEMPLATE(Label, visible())
REF_TEMPLATE(Sum, visible())
REF_TEMPLATE(SumResult, visible())
REF_TEMPLATE(Replace, enabled())

void Button::decNativeRef()
{
	SystemItem::decNativeRef();
	if(getNativeRef() == 0){
		system.log.v(TAG, 0, "%s was not referenced any more, but cannot delete?", inspect().c_str());
		//system.unregist(this);
	}
}
void Button::incNativeRef()
{
	if(getNativeRef() <= 0){
		system.regist(this);
	}
	SystemItem::incNativeRef();
}

#undef REF_TEMPLATE

}}
