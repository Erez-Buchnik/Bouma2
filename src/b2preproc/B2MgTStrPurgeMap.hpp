
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

#ifndef B2MgTStrPurgeMap___HPP
#define B2MgTStrPurgeMap___HPP

#include "B2PreprocDefs.hpp"


class B2MgTStrPurgeMap : public B2HashMap<unsigned int, unsigned int>
{

public:
	B2MgTStrPurgeMap() { };
	B2MgTStrPurgeMap(unsigned int total_str_count)
	{
		for(unsigned int str_instance_id = 0; str_instance_id < total_str_count; ++str_instance_id)
		{
			(*this)[str_instance_id];
		};
	};
	void merge(const B2MgTStrPurgeMap &other_purge_map);
	void deduct(const B2MgTStrPurgeMap &other_purge_map);
};


#endif //B2MgTStrPurgeMap___HPP

