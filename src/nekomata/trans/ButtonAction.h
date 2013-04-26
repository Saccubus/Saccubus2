/**
 * Nekomata
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#include "NicosAction.h"

namespace nekomata {
namespace trans {

class ButtonAction: public nekomata::trans::NicosAction {
public:
	ButtonAction(nicomo::model::Comment const& com, const std::vector<std::string>& tokens);
	virtual ~ButtonAction();
protected:
	virtual void read();
	virtual std::string write();
private:
	std::string _message;
	std::string _commsg;
	bool _local;
	std::string _commail;
	int _times;
};

}}
