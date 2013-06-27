
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

#ifndef B2MgTReshuffleMap___HPP
#define B2MgTReshuffleMap___HPP

#include "B2MgTStateMachine.hpp"


class B2MgTReshuffleMap : public B2HashMap<unsigned int, unsigned int>
{
	B2HashMap<unsigned int, unsigned int> _reshuffled_terminals;

public:
	B2MgTReshuffleMap(const B2MgTStateMachine &state_machine);
	void reshuffle(unsigned int &id) const
	{
		const_iterator state_it = find(id);
		if(state_it != end())
		{
			id = state_it->second;
		}
		else
		{
			B2HashMap<unsigned int, unsigned int>::const_iterator terminal_it = _reshuffled_terminals.find(id);
			if(terminal_it != _reshuffled_terminals.end())
			{
				id = terminal_it->second;
			};
		};
	};
	void reshuffle(B2MgTStateMachine &state_machine);
};

#endif //B2MgTReshuffleMap___HPP

