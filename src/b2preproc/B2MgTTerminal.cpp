
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


#include "B2MgTTerminal.hpp"
#include <sstream>


std::string B2MgTTerminal::dump() const
{
	std::stringstream str_strm;
	str_strm << '[' << _relative_offset << '|' << _str_id << ']' << _id << ':';
	int offset = 0;
	std::string str_out = "..";
	for(const_iterator segment_it = begin(); segment_it != end(); ++segment_it)
	{
		int segment_start = segment_it->first;
		int segment_end = (segment_it->first + segment_it->second.size());
		int str_out_end = (offset + str_out.size());
		if(segment_end <= offset)
		{
			str_out = segment_it->second + std::string((offset - segment_end), ' ') + str_out;
			offset = segment_start;
		}
		else if(str_out_end <= segment_start)
		{
			str_out += std::string((segment_start - str_out_end), ' ') + segment_it->second;
		}
		else if((offset <= segment_start) && (segment_end <= str_out_end))
		{
			str_out.replace((segment_start - offset), segment_it->second.size(), segment_it->second);
		}
		else
		{
			b2_preproc_error(B2_PREPROC_ERROR_MGT_BAD_TERMINAL);
		};
	};
	str_strm << str_out;
	return str_strm.str();
};
