
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

#ifndef B2PreprocConfig___HPP
#define B2PreprocConfig___HPP


#include <string>
#include <hash_map>

enum B2PreprocConfigTxtId
{
	B2_STR_SET_FILE = 1,
	B2_GLPK_DEBUG_FILE,
	///////////////
	B2_CONFIG_TXT_COUNT
};

enum B2PreprocConfigNumId
{
	B2_COVERAGE_PURGE_FACTOR = B2_CONFIG_TXT_COUNT,
	B2_DIVERSITY_PURGE_FACTOR
};

class B2PreprocConfig
{
	std::hash_map<unsigned int, std::string> _argv;

public:
	B2PreprocConfig(const int argc, const char **argv);
	const std::string txt(B2PreprocConfigTxtId id) { return _argv[id]; };
	const double num(B2PreprocConfigNumId id) { return atof(_argv[id].c_str()); };
};

const std::string b2_preproc_config(B2PreprocConfigTxtId id);
const double b2_preproc_config(B2PreprocConfigNumId id);


#endif // B2PreprocConfig___HPP
