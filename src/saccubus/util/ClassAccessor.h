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
	type name##_;\
scope:\
	type name() const{return name##_;}

#define DEF_ATTR_WRITER(scope, type, name)\
private:\
	type name##_;\
scope:\
	void name(const type& val){name##_ = val;}

#define DEF_ATTR_ACCESSOR(rscope, wscope, type, name)\
private:\
	type name##_;\
rscope:\
	type name() const{return name##_;}\
wscope:\
	void name(const type& val){name##_ = val;}

#endif /* CLASSACCESSOR_H_ */
