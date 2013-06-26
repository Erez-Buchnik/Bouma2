
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
#include "B2MgTTransitional.hpp"
#include "B2MgTPivot.hpp"


class B2MgTState : public B2HashMap<unsigned char, unsigned int>
{
	int _relative_offset;
	unsigned int _id;
	unsigned int _fallback_transition;
	unsigned int _fallback_pivot_transition;


	std::vector<B2MgTPivot> _pivots;
	std::vector<B2MgTTransitional> _transitionals;

public:
	B2MgTState() : 
		_relative_offset(B2_MGT_INVALID_OFFSET), _id(B2_MGT_STATE_INVALID_ID), _fallback_transition(B2_MGT_STATE_INVALID_ID), _fallback_pivot_transition(B2_MGT_STATE_INVALID_ID) { };
	B2MgTState(int relative_offset, unsigned int id) : 
		_relative_offset(relative_offset), _id(id), _fallback_transition(B2_MGT_STATE_INVALID_ID), _fallback_pivot_transition(B2_MGT_STATE_INVALID_ID) { };
	void add_transition(unsigned char byte, unsigned int next_state_id)
	{
		(*this)[byte] = next_state_id;
	};
	void add_transitional(const B2MgTTransitional &transitional) { _transitionals.push_back(transitional); };
	void add_pivot(const B2MgTPivot &pivot)
	{
		if(pivot.transition() != B2_MGT_STATE_INVALID_ID)
		{
			_pivots.push_back(pivot);
		};
	};
	void add_fallback_pivot(unsigned int fallback_pivot_transition)
	{
		_fallback_pivot_transition = fallback_pivot_transition;
	};
	void add_fallback_transition(unsigned int next_state_id)
	{
		_fallback_transition = next_state_id;
	};
	void set_id(unsigned int id) { _id = id; };
	unsigned int id() const { return _id; };
	std::string dump() const;
};

#endif //B2MgTState___HPP

