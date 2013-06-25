
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

#include "B2StrSet.hpp"

B2Str::B2Str(unsigned int id, unsigned char *bytes, unsigned int length) : std::string((char *)bytes, length), _id(id)
{
	if(length < 3)
	{
		b2_preproc_error(B2_PREPROC_ERROR_PATTERN_STR_TOO_SHORT);
	};
};


void B2StrSet::add_str(const B2Str &str)
{
	B2StrSet::iterator find_it = find(str);
	if(find_it == end())
	{
		(*this)[str] = B2StrStruct(str);
		b2_preproc_diagnostic(B2_PREPROC_DIAG_ADDED_PATTERN_STR);
	}
	else
	{
		find_it->second.duplicate_id(str);
	};
};
