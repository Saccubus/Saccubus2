/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#include <nekomata/logging/Logging.h>
#include <nekomata/system/System.h>
#include <cinamo/String.h>

namespace nekomata{
namespace system {

const std::string TAG("SystemItem");

bool Drawable::ComparatorByZ::operator () (Drawable* const a, Drawable* const b)
{
	return a->z() < b->z();
}
bool Drawable::ComparatorByZ::operator () (Drawable* const a, const double& b)
{
	return a->z() < b;
}
bool Drawable::ComparatorByZ::operator () (const double& a, Drawable* const b)
{
	return a < b->z();
}

void SystemItem::onChanged()
{
	system.log.v(TAG, 0, "prop changed: %s", inspect().c_str());
}

std::string Shape::inspect()
{
	return cinamo::format(
			"Shape(x: %f, y: %f, z: %f, shape: %s, width: %f, height: %f, color:%x, visible: %d, pos: %s, mask: %d, commentmask: %d, alpha: %f, rotation:%f, mover: %s",
			x(), y(), z(), shape().c_str(), width(), height(), color(), visible(), pos().c_str(), mask(), commentmask(), alpha(), rotation(), mover().c_str()
			);
}


std::string Label::inspect()
{
	return cinamo::format(
		"Label(text:%s , x: %f, y: %f, z: %f, size: %f, pos: %s, color: %d, bold: %d, visible: %d, filter: %s, alpha: %f, mover: %s)",
		text().c_str(), x(), y(), z(), size(), pos().c_str(), color(), bold(), visible(), filter().c_str(), alpha(), mover().c_str()
		);

}
std::string Sum::inspect()
{
	return cinamo::format(
		"Sum(x: %f, y: %f, size: %f, color: %x, visible: %d, enabled: %d, pos: %s, asc: %d, unit: %s, buttononly: %d, words: %d word(s), partial: %d)",
		x(), y(), size(), color(), visible(), enabled(), pos().c_str(), asc(), unit().c_str(), buttononly(), words().size(), partial()
		);
}
std::string SumResult::inspect()
{
	return cinamo::format(
		"SumResult(x: %f, y: %f, color: %x, visible: %d, pos: %s, asc: %d, unit: %s, sum: %ditem(s))",
		x(), y(), color(), visible(), pos().c_str(), asc(), unit().c_str(), sum().size()
	);
}
std::string Replace::inspect()
{
	return cinamo::format(
		"Replace(src: %s, dst: %s, enabled: %d, target: %s, fill: %d, partial: %d, color: %x, size: %s, pos: %s)",
		src().c_str(), dest().c_str(), enabled(), target().c_str(), fill(), partial(), color(), size().c_str(), pos().c_str()
	);
}

#define REF_TEMPLATE(clazz, valid_expr)\
void clazz::decref()\
{\
	SystemItem::decref();\
	if(refcount() == 0 && !(valid_expr)){\
		system.log.v(TAG, 0, "%s was not referenced any more, so deleted.", inspect().c_str());\
		system.unregist(this);\
	}\
}\
void clazz::incref(bool opt)\
{\
	if(refcount() <= 0 && opt){\
		system.log.v(TAG, 0, "%s created and registed.", #clazz);\
		system.regist(this);\
	}\
	SystemItem::incref(opt);\
}

REF_TEMPLATE(Shape, visible())
REF_TEMPLATE(Label, visible())
REF_TEMPLATE(Sum, visible())
REF_TEMPLATE(SumResult, visible())
REF_TEMPLATE(Replace, enabled())

#undef REF_TEMPLATE

}}
