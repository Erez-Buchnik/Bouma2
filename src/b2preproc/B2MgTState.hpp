
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

#ifndef B2MgTState___HPP
#define B2MgTState___HPP

#include "B2PreprocDefs.hpp"


class B2MgTState : public B2HashMap<unsigned char, unsigned int>
{
	unsigned int _id;
	unsigned int _fallback_transition;

public:
	B2MgTState(unsigned int id = B2_MGT_STATE_INVALID_ID) : _id(id), _fallback_transition(B2_MGT_STATE_INVALID_ID) { };
	void add_transition(unsigned char byte, unsigned int next_state_id)
	{
		(*this)[byte] = next_state_id;
	};
	void add_fallback_transition(unsigned int next_state_id)
	{
		_fallback_transition = next_state_id;
	};
	void set_id(unsigned int id) { _id = id; };
	unsigned int id() const { return _id; };
};

#endif //B2MgTState___HPP

