/*
 * Dumpable.h
 *
 *  Created on: 2012/03/17
 *      Author: psi
 */

#ifndef DUMPABLE_H_
#define DUMPABLE_H_

#include <nekomata/classdefs.h>

namespace nekomata{
namespace logging{

class Dumpable{
protected:
	Dumpable(){};
	virtual ~Dumpable(){};
public:
	virtual void dump(Dumper& dumper) const = 0;
};

}}
#endif /* DUMPABLE_H_ */
