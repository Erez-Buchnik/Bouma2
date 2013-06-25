
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

#ifndef B2PreprocDefs___HPP
#define B2PreprocDefs___HPP


#include <string>
#include <vector>

#ifdef __GNUC__

#include <backward/hash_map>
#define B2HashMap /**/ __gnu_cxx::hash_map /**/
#define B2_HASH_MAP_ERASE(hash_map_inst, iter) { (hash_map_inst).erase(iter++); };

namespace __gnu_cxx
{
	template<> struct hash<std::string>
	{
		unsigned int fnv_hash(const char *bytes, unsigned int len) const
		{
			unsigned int hashval = 2166136261U;
			for(unsigned int i = 0; i < len; ++i)
			{
				hashval = (16777619U * hashval) ^ (unsigned char)(bytes[i]);
			};
			return hashval;
		};

		size_t operator () (const std::string &str) const
		{
			return fnv_hash(str.c_str(), str.size());
		};
	};
};

#else

#include <hash_map>
#define B2HashMap /**/ std::hash_map /**/
#define B2_HASH_MAP_ERASE(hash_map_inst, iter) { (iter) = (hash_map_inst).erase(iter); };

#endif

#define B2_MGT_STATE_INVALID_ID (0xFFFF)
#define B2_MGT_INVALID_OFFSET (1)

#include "B2PreprocConfig.hpp"
#include "B2PreprocDiagnostics.hpp"

#endif // B2PreprocDefs___HPP
