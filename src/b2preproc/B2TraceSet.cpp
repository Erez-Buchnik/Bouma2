
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

#include "B2TraceSet.hpp"


const char B2TraceName::_hex_digit[16] = {
	'0', '1', '2', '3', '4', '5', '6', '7', 
	'8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

B2TraceName::B2TraceName(B2Trace trace)
{
	_name[0] = _hex_digit[(trace >> 12) & 0x0F];
	_name[1] = _hex_digit[(trace >> 8) & 0x0F];
	_name[2] = _hex_digit[(trace >> 4) & 0x0F];
	_name[3] = _hex_digit[trace & 0x0F];
	_name[3] = '\0';
};

B2TraceStruct::B2TraceStruct(const std::string str, unsigned int offset) : _str(str), _offset(offset)
{
	if((_offset + 2) > _str.size())
	{
		b2_preproc_error(B2_PREPROC_ERROR_TRACE_OFFSET_OUT_OF_RANGE);
	};
};

void B2TraceSet::add_trace(const B2TraceStruct &trace_struct)
{
	B2Trace trace = trace_struct.trace_val();
	B2TraceSet::iterator find_it = find(trace);
	if(find_it == end())
	{
		(*this)[trace].push_back(trace_struct);
		unsigned int trace_count = (_trace_vals.size() + 1);
		_trace_vals[trace] = trace_count;
	}
	else
	{
		find_it->second.push_back(trace_struct);
	};
};

B2TraceSet::B2TraceSet(const B2StrSet &str_set) : _str_count(str_set.size())
{
	for(B2StrSet::const_iterator str_it = str_set.begin(); str_it != str_set.end(); ++str_it)
	{
		const std::string &str = str_it->first;
		for(unsigned int offset = 0; (offset + 2) <= str.size(); ++offset)
		{
			add_trace(B2TraceStruct(str, offset));
		};
	};
};

