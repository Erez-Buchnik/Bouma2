
/***********************************************************

Bouma2 - A Multiple String Match Algorithm
<http://arxiv.org/abs/1209.4554>
Copyright (C) 2013 Erez M. Buchnik. All Rights Reserved.
Email: <erez.buchnik@gmail.com>

***********************************************************

This file is part of Bouma2.

Bouma2 is free software; you can redistribute it and/or 
modify it under the terms of the GNU General Public License 
as published by the Free Software Foundation; either version 2 
of the License, or (at your option) any later version.

Bouma2 is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
GNU General Public License for more details.

You should have received a copy of the GNU General Public License 
along with Bouma2; if not, see <http://www.gnu.org/licenses>.

***********************************************************/

#ifndef B2MgTStateMachine___HPP
#define B2MgTStateMachine___HPP

#include "B2MgTState.hpp"
#include "B2MgTTerminal.hpp"
#include "B2MgTTransitional.hpp"
#include "B2MgTStrInstance.hpp"


class B2MgTStateMachine : public B2HashMap<unsigned int, B2MgTState>
{
	unsigned int _node_count;
	B2HashMap<unsigned int, B2MgTTerminal> _terminals;

public:
	B2MgTStateMachine() : _node_count(0) { };
	B2MgTState &new_state(int relative_offset);
	const B2MgTTerminal &new_terminal(const B2MgTStrInstance &str_instance);
	const B2HashMap<unsigned int, B2MgTTerminal> &terminals() const { return _terminals; };
	std::string dump() const;
};

#endif //B2MgTStateMachine___HPP

