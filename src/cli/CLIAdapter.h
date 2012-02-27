/*
 * CLIAdapter.h
 *
 *  Created on: 2012/02/26
 *      Author: psi
 */

#ifndef CLIADAPTER_H_
#define CLIADAPTER_H_

#include "../nekomata/Nekomata.h"

namespace cli {

class CLIChatAdapter : public ::nekomata::ChatAdapter
{
public:
	CLIChatAdapter();
	virtual ~CLIChatAdapter();
};

class CLIAdapter : public ::nekomata::Adapter
{
public:
	CLIAdapter();
	virtual ~CLIAdapter();
};

}
#endif /* CLIADAPTER_H_ */
