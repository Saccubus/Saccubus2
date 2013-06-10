/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#pragma once
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
