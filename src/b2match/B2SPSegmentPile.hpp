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

#ifndef B2SPSegmentPile___HPP
#define B2SPSegmentPile___HPP


class B2SPSegmentPile
{
	unsigned char *_pile;

public:
	unsigned int match(const unsigned char *subject_ptr, const unsigned int offset_in_pile, const unsigned int length_in_pile) const
	{
		unsigned char *segment_ptr = _pile + offset_in_pile;
		unsigned char *segment_end = segment_ptr + length_in_pile;
		while(segment_ptr < segment_end)
		{
			if(*segment_ptr != *subject_ptr)
			{
				return 1;
			};
			++segment_ptr;
			++subject_ptr;
		};
		return 0;
	};
};

#endif //B2SPSegmentPile___HPP

