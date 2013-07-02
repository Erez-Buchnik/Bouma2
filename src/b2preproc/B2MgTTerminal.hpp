
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

#ifndef B2MgTTerminal___HPP
#define B2MgTTerminal___HPP

#include "B2PreprocDefs.hpp"

class B2MgTReshuffleMap;


class B2MgTTerminalBase : public B2HashMap<int, std::string>
{

protected:
	unsigned int _str_id;
	int _relative_offset;
	unsigned int _fallback_transition;

	B2MgTTerminalBase(unsigned int str_id = 0, int relative_offset = 0) : 
		_str_id(str_id), _relative_offset(relative_offset), _fallback_transition(B2_MGT_STATE_INVALID_ID) { };
};

class B2MgTTerminal : public B2MgTTerminalBase
{
	unsigned int _id;

public:
	B2MgTTerminal(unsigned int str_id = 0, int relative_offset = 0, unsigned int id = B2_MGT_STATE_INVALID_ID) : 
		B2MgTTerminalBase(str_id, relative_offset), _id(id) { };
	void add_fallback_transition(unsigned int next_state_id)
	{
		_fallback_transition = next_state_id;
	};
	void set_id(unsigned int id) { _id = id; };
	unsigned int id() const { return _id; };
	bool operator == (const B2MgTTerminal &other) const { return ((const B2MgTTerminalBase &)*this == (const B2MgTTerminalBase &)other); };
	void reshuffle(const B2MgTReshuffleMap &reshuffle_map);
	std::string dump() const;
};


#endif //B2MgTTerminal___HPP

