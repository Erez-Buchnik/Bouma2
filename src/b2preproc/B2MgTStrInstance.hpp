
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

#ifndef B2MgTStrInstance___HPP
#define B2MgTStrInstance___HPP

#include "B2TraceSet.hpp"


class B2MgTStrInstance : public std::string
{
	unsigned int _str_id;
	std::string _purge_mask;
	int _relative_offset;

public:
	B2MgTStrInstance() : _relative_offset(0) { };
	B2MgTStrInstance(unsigned int str_id, const B2TraceStruct &trace);
	unsigned int str_id() const { return _str_id; };
	unsigned char byte(int offset) const { return (*this)[offset - _relative_offset]; };
	int relative_offset() const { return _relative_offset; };
	int relative_end_offset() const { return _relative_offset + size(); };
	unsigned int purge_at_offset(int offset);
	int next_segment(std::string &segment, int offset = B2_MGT_INVALID_OFFSET) const;
	int leftmost_byte_offset() const { return _relative_offset + _purge_mask.find_first_of('+'); };
	int rightmost_byte_offset() const { return _relative_offset + _purge_mask.find_last_of('+'); };
};


#endif //B2MgTStrInstance___HPP

