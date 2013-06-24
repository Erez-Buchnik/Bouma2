
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

#include "B2MgTOffsetMap.hpp"


void B2MgTOffsetMap::apply_cavities(unsigned int str_instance_id, const B2MgTStrInstance &str_instance)
{
	int leftmost_offset = str_instance.relative_offset();
	int rightmost_offset = leftmost_offset + str_instance.size();
	for(iterator offset_it = begin(); offset_it != end(); ++offset_it)
	{
		int offset = offset_it->first;
		if((offset < leftmost_offset) || (rightmost_offset <= offset))
		{
			B2MgTByteChoicesMap &choices_map = offset_it->second;
			for(B2MgTByteChoicesMap::iterator choice_it = choices_map.begin(); choice_it != choices_map.end(); ++choice_it)
			{
				B2HashMap<unsigned int, unsigned int> &str_purge_map = choice_it->second;
				str_purge_map.erase(str_instance_id);
			};
		};
	};
};
