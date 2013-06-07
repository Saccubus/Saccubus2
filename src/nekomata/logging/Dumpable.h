/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
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
