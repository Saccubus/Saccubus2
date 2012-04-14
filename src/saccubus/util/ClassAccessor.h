/*
 * ClassAccessor.h
 *
 *  Created on: 2012/03/24
 *      Author: psi
 */

#ifndef CLASSACCESSOR_H_
#define CLASSACCESSOR_H_

#define DEF_ATTR_ACCESSOR(rscope, wscope, type, name)\
private:\
	type _##name;\
rscope:\
	inline type name() const{return _##name;}\
wscope:\
	inline void name(type const& val){_##name = val;}

#endif /* CLASSACCESSOR_H_ */
