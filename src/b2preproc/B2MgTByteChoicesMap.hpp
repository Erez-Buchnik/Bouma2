
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

#ifndef B2MgTByteChoicesMap___HPP
#define B2MgTByteChoicesMap___HPP

#include "B2MgTStrPurgeMap.hpp"


class B2MgTByteChoicesMap : public B2HashMap<unsigned char, B2MgTStrPurgeMap>
{
	unsigned int _total_str_instance_count;
	B2MgTStrPurgeMap _cavities_map;
	B2MgTStrPurgeMap _fallback_purge_map;

public:
	B2MgTByteChoicesMap() : _total_str_instance_count(0) { };
	void add_str_instance(unsigned int total_str_instance_count, unsigned int preserve_instance_id, unsigned char byte);
	const B2MgTStrPurgeMap fallback_purge_map() const { return _fallback_purge_map; };
	void clean_purged(const B2MgTStrPurgeMap &purge_map, const std::hash_map<unsigned char, unsigned int> &valid_bytes);

	double coverage() const;
	double diversity() const;
};


#endif //B2MgTByteChoicesMap___HPP

