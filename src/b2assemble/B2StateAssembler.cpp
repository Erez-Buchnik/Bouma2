
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

#include "B2StateAssembler.hpp"


void B2StateAssembler::fill()
{
	unsigned int longest_transition = _mgt_state_machine.longest_transition();
	if(longest_transition < 4)
	{
		for(B2MgTStateMachine::const_iterator state_it = _mgt_state_machine.begin(); state_it != _mgt_state_machine.end(); ++state_it)
		{
			fill_state<B2SP2BitState>(state_it->second, _2bit_states_vec);
		};
	}
	else if(longest_transition < 16)
	{
		for(B2MgTStateMachine::const_iterator state_it = _mgt_state_machine.begin(); state_it != _mgt_state_machine.end(); ++state_it)
		{
			fill_state<B2SP4BitState>(state_it->second, _4bit_states_vec);
		};
	}
	else if(longest_transition < 256)
	{
		for(B2MgTStateMachine::const_iterator state_it = _mgt_state_machine.begin(); state_it != _mgt_state_machine.end(); ++state_it)
		{
			fill_state<B2SP8BitState>(state_it->second, _8bit_states_vec);
		};
	}
	else
	{
		for(B2MgTStateMachine::const_iterator state_it = _mgt_state_machine.begin(); state_it != _mgt_state_machine.end(); ++state_it)
		{
			fill_state<B2SP16BitState>(state_it->second, _16bit_states_vec);
		};
	}
};


