
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


#include "B2MgTState.hpp"
#include "B2MgTReshuffleMap.hpp"
#include <sstream>


std::string B2MgTState::dump() const
{
	std::stringstream str_strm;
	str_strm << _id << ' ' << _relative_offset << '|' << _fallback_transition << ':';
	for(const_iterator segment_it = begin(); segment_it != end(); ++segment_it)
	{
		str_strm << segment_it->first << ">" << segment_it->second << ' ';
	};
	if(_transitionals.size() > 0)
	{
		for(std::vector<B2MgTTransitional>::const_iterator transitional_it = _transitionals.begin(); transitional_it != _transitionals.end(); ++transitional_it)
		{
			str_strm << " T" << transitional_it->dump();
		};
	};
	if(_pivots.size() > 0)
	{
		for(std::vector<B2MgTPivot>::const_iterator pivot_it = _pivots.begin(); pivot_it != _pivots.end(); ++pivot_it)
		{
			str_strm << " P" << pivot_it->dump();
		};
	};
	if(_pivot_fallback_transition != B2_MGT_STATE_INVALID_ID)
	{
		str_strm << " Pfb" << _pivot_fallback_transition;
	};
	return str_strm.str();
};


unsigned int B2MgTState::longest_transition() const
{
	int max_distance = 0;
	for(const_iterator transition_it = begin(); transition_it != end(); ++transition_it)
	{
		if(transition_it->second != B2_MGT_STATE_INVALID_ID)
		{
			int transition_distance = (transition_it->second - _id);
			if(transition_distance < 0)
			{
				transition_distance = -transition_distance;
			};
			if(max_distance < transition_distance)
			{
				max_distance = transition_distance;
			};
		};
	};
	if(_fallback_transition != B2_MGT_STATE_INVALID_ID)
	{
		int transition_distance = (_fallback_transition - _id);
		if(transition_distance < 0)
		{
			transition_distance = -transition_distance;
		};
		if(max_distance < transition_distance)
		{
			max_distance = transition_distance;
		};
	};
	if(_pivot_fallback_transition != B2_MGT_STATE_INVALID_ID)
	{
		int transition_distance = (_pivot_fallback_transition - _id);
		if(transition_distance < 0)
		{
			transition_distance = -transition_distance;
		};
		if(max_distance < transition_distance)
		{
			max_distance = transition_distance;
		};
	};
	return max_distance;
};


void B2MgTState::reshuffle(const B2MgTReshuffleMap &reshuffle_map)
{
	reshuffle_map.reshuffle(_id);
	for(iterator transition_it = begin(); transition_it != end(); ++transition_it)
	{
		reshuffle_map.reshuffle(transition_it->second);
	};
	reshuffle_map.reshuffle(_fallback_transition);
	reshuffle_map.reshuffle(_pivot_fallback_transition);
};
