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

#ifndef B2SP4BitState___HPP
#define B2SP4BitState___HPP


#include "B2SPStateBase.hpp"


class B2SP4BitState : public B2SPStateBase
{
	struct Transition2Pack
	{
		char _transition_0 : 4;
		char _transition_1 : 4;
	};
	Transition2Pack _transition_vec[128];

public:
	const unsigned int transition(const unsigned char *motif_position, unsigned int state_id) const
	{
		unsigned char byte = byte_value(motif_position);
		unsigned int div = byte / 2;
		unsigned int mod = byte % 2;
		Transition2Pack transition_2pack = _transition_vec[div];
		if(mod == 0)
		{
			return state_id + transition_2pack._transition_0;
		}
		else
		{
			return state_id + transition_2pack._transition_1;
		};
	};
};


#endif //B2SP4BitState___HPP

