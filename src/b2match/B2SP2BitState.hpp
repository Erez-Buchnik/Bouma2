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

#ifndef B2SP2BitState___HPP
#define B2SP2BitState___HPP


#include "B2SPStateBase.hpp"


class B2SP2BitState : public B2SPStateBase
{
	struct Transition4Pack
	{
		char _transition_0 : 2;
		char _transition_1 : 2;
		char _transition_2 : 2;
		char _transition_3 : 2;
	};
	Transition4Pack _transition_vec[64];

public:
	int set(unsigned int byte, unsigned int state_id, unsigned int next_node)
	{
		unsigned int div = byte / 4;
		unsigned int mod = byte % 4;
		Transition4Pack &transition_4pack = _transition_vec[div];
		int transition = (int)next_node - (int)state_id;
		switch(mod)
		{
		case 0:
			transition_4pack._transition_0 = transition;
		case 1:
			transition_4pack._transition_1 = transition;
		case 2:
			transition_4pack._transition_2 = transition;
		default:
			transition_4pack._transition_3 = transition;
		};
		return transition;
	};
	const unsigned int transition(const unsigned char *motif_position, unsigned int state_id) const
	{
		unsigned char byte = byte_value(motif_position);
		unsigned int div = byte / 4;
		unsigned int mod = byte % 4;
		Transition4Pack transition_4pack = _transition_vec[div];
		switch(mod)
		{
		case 0:
			return state_id + transition_4pack._transition_0;
		case 1:
			return state_id + transition_4pack._transition_1;
		case 2:
			return state_id + transition_4pack._transition_2;
		default:
			return state_id + transition_4pack._transition_3;
		};
	};
};


#endif //B2SP2BitState___HPP

