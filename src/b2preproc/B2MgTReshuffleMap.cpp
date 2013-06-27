
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

#include "B2MgTReshuffleMap.hpp"


B2MgTReshuffleMap::B2MgTReshuffleMap(const B2MgTStateMachine &state_machine)
{
	for(B2MgTStateMachine::const_iterator state_it = state_machine.begin(); state_it != state_machine.end(); ++state_it)
	{
		unsigned int reshuffled_id = size();
		(*this)[state_it->first] = reshuffled_id;
	};
	const B2HashMap<unsigned int, B2MgTTerminal> &terminals = state_machine.terminals();
	for(B2HashMap<unsigned int, B2MgTTerminal>::const_iterator terminal_it = terminals.begin(); terminal_it != terminals.end(); ++terminal_it)
	{
		unsigned int reshuffled_id = size() + _reshuffled_terminals.size();
		_reshuffled_terminals[terminal_it->first] = reshuffled_id;
	};
};


void B2MgTReshuffleMap::reshuffle(B2MgTStateMachine &state_machine)
{
	for(B2MgTStateMachine::iterator state_it = state_machine.begin(); state_it != state_machine.end(); ++state_it)
	{
		state_it->second.reshuffle(*this);
	};
	B2HashMap<unsigned int, B2MgTTerminal> &terminals = state_machine.terminals();
	for(B2HashMap<unsigned int, B2MgTTerminal>::iterator terminal_it = terminals.begin(); terminal_it != terminals.end(); ++terminal_it)
	{
		terminal_it->second.reshuffle(*this);
	};
};
