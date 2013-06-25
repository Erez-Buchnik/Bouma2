
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

#include "B2PreprocDiagnostics.hpp"
#include "B2PreprocConfig.hpp"
#include <sstream>


std::string B2PreprocDiagnostics::dump() const
{
	std::stringstream str_strm;
	for(std::hash_map<unsigned int, unsigned int>::const_iterator counter_it = _counters.begin(); counter_it != _counters.end(); ++counter_it)
	{
		str_strm << b2_preproc_msg(counter_it->first) << ": " << counter_it->second << std::endl;
	};
	return str_strm.str();
};
