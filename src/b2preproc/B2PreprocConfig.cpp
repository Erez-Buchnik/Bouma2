
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

#include "B2PreprocConfig.hpp"

B2PreprocConfig::B2PreprocConfig(const int argc, const char **argv)
{
	_argv[B2_STR_SET_FILE] = "str_set.txt";
	_argv[B2_GLPK_DEBUG_FILE] = "B2-ILP.txt";
	_argv[B2_COVERAGE_PURGE_FACTOR] = "0.1";
	_argv[B2_DIVERSITY_PURGE_FACTOR] = "0.9";
	for(int i = 0; i < argc; ++i)
	{
		_argv[i] = argv[i];
	};
};
