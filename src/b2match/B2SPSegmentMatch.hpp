
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

#ifndef B2SPSegmentMatch___HPP
#define B2SPSegmentMatch___HPP


class B2SPSegmentMatch
{
  char _relative_offset;
	unsigned char _segment_offset;
	unsigned char _segment_length;

public:
	unsigned int match(const char *motif_position, const B2SPSegmentPile &segment_pile) const
	{
    return segment_pile.match((motif_position + _relative_offset), _segment_offset, _segment_length);
	};
};

#endif //B2SPSegmentMatch___HPP

