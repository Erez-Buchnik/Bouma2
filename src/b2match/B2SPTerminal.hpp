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

#ifndef B2SPTerminal___HPP
#define B2SPTerminal___HPP


#include "B2SPSegmentMatch.hpp"


class B2SPTerminal
{
	unsigned short _str_instance_id;
	unsigned char _first_segment_idx;
	unsigned char _segment_count;

public:
	B2SPTerminal(unsigned short str_instance_id, unsigned char first_segment_idx, unsigned char segment_count) :
		_str_instance_id(str_instance_id), _first_segment_idx(first_segment_idx), _segment_count(segment_count) { };
	void match(unsigned int *&match_list, const unsigned char *motif_position, const B2SPSegmentMatch *segments_vec, const B2SPSegmentPile &segment_pile) const
	{
		unsigned int segments_end = _first_segment_idx + _segment_count;
		for(unsigned int segment_idx = _first_segment_idx; segment_idx < segments_end; ++segment_idx)
		{
			const B2SPSegmentMatch &segment = segments_vec[segment_idx];
			if(segment.match(motif_position, segment_pile) != 0)
			{
				return;
			};
		};
		*match_list = _str_instance_id;
		++match_list;
	};
};

#endif //B2SPTerminal___HPP

