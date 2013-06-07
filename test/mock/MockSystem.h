/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once
#include <nekomata/system/System.h>

namespace samock {

class MockSystem: public nekomata::system::System {
public:
	MockSystem();
	virtual ~MockSystem();
	virtual std::shared_ptr<const nekomata::system::Comment> nextComment();
};

}
