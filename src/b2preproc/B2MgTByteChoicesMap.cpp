
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

#include "B2MgTByteChoicesMap.hpp"


void B2MgTByteChoicesMap::add_str_instance(unsigned int total_str_instance_count, unsigned int preserve_instance_id, unsigned char byte)
{
	if(_total_str_instance_count == 0)
	{
		_total_str_instance_count = total_str_instance_count;
		_cavities_map = B2MgTStrPurgeMap(total_str_instance_count);
	}
	else if(_total_str_instance_count != total_str_instance_count)
	{
		b2_preproc_error_inc(B2_PREPROC_ERROR_MGT_BAD_BYTE_CHOICES_MAP, 1);
	};

	B2MgTByteChoicesMap::iterator find_it = find(byte);
	if(find_it != end())
	{
		B2MgTStrPurgeMap &str_purge_map = find_it->second;
		str_purge_map.erase(preserve_instance_id);
	}
	else
	{
		B2MgTStrPurgeMap str_purge_map(_total_str_instance_count);
		str_purge_map.erase(preserve_instance_id);
		(*this)[byte] = str_purge_map;
	};
	_cavities_map.erase(preserve_instance_id);
	_fallback_purge_map[preserve_instance_id];
};


void B2MgTByteChoicesMap::clean_purged(const B2MgTStrPurgeMap &purge_map, const B2HashMap<unsigned char, unsigned int> &valid_bytes)
{
	for(iterator byte_it = begin(); byte_it != end(); )
	{
		B2HashMap<unsigned char, unsigned int>::const_iterator find_it = valid_bytes.find(byte_it->first);
		if(find_it != valid_bytes.end())
		{
			B2MgTStrPurgeMap &byte_purge_map = byte_it->second;
			byte_purge_map.deduct(purge_map);
			++byte_it;
		}
		else
		{
			B2_HASH_MAP_ERASE(*this, byte_it);
		};
	};
	_fallback_purge_map.deduct(purge_map);
	_cavities_map.deduct(purge_map);
};


double B2MgTByteChoicesMap::coverage() const
{
	return (double)(_total_str_instance_count - _cavities_map.size()) / (double)_total_str_instance_count;
};


double B2MgTByteChoicesMap::diversity() const
{
	return (double)(size()) / (double)_total_str_instance_count;
};
