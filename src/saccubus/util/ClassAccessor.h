/*
 * ClassAccessor.h
 *
 *  Created on: 2012/03/24
 *      Author: psi
 */

#ifndef CLASSACCESSOR_H_
#define CLASSACCESSOR_H_

#define DEF_ATTR_READER(scope, type, name)\
private:\
	type _##name;\
scope:\
	type name() const{return _##name;}

#define DEF_ATTR_WRITER(scope, type, name)\
private:\
	type _##name;\
scope:\
	void name(type const& val){_##name = val;}

#define DEF_ATTR_ACCESSOR(rscope, wscope, type, name)\
private:\
	type _##name;\
rscope:\
	type name() const{return _##name;}\
wscope:\
	void name(type const& val){_##name = val;}

#endif /* CLASSACCESSOR_H_ */
