
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


#include "B2MgTStrInstance.hpp"


B2MgTStrInstance::B2MgTStrInstance(unsigned int str_id, const B2TraceStruct &trace) : _str_id(str_id), _purge_mask(trace.str().size(), '+'), _relative_offset(-(int)trace.offset())
{
	(std::string &)(*this) = trace.str();
	_purge_mask[trace.offset()] = '.';
	_purge_mask[trace.offset() + 1] = '.';
};


unsigned int B2MgTStrInstance::purge_at_offset(int offset)
{
	if((offset >= _relative_offset) && (offset < _relative_offset + (int)(size())))
	{
		_purge_mask[offset - _relative_offset] = '.';
	};
	unsigned int byte_count = 0;
	for(const_iterator byte_it = _purge_mask.begin(); byte_it != _purge_mask.end(); ++byte_it)
	{
		if(*byte_it == '+')
		{
			++byte_count;
		};
	};
	return byte_count;
};


int B2MgTStrInstance::next_segment(std::string &segment, int offset) const
{
	const_iterator byte_it = _purge_mask.begin();
	if(offset != B2_MGT_INVALID_OFFSET)
	{
		byte_it += (offset - _relative_offset);
	};
	const_iterator segment_start;
	unsigned int segment_length;
	for(; byte_it != _purge_mask.end(); ++byte_it)
	{
		if(*byte_it == '+')
		{
			break;
		};
	};
	segment_start = byte_it;
	for(; byte_it != _purge_mask.end(); ++byte_it)
	{
		if(*byte_it == '.')
		{
			break;
		};
	};
	segment_length = (byte_it - segment_start);
	int segment_offset = _relative_offset + (segment_start - _purge_mask.begin());
	segment = this->substr((segment_offset - _relative_offset), segment_length);
	return segment_offset;
};
