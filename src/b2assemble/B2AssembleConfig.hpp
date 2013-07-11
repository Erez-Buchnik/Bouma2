
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

#ifndef B2AssembleConfig___HPP
#define B2AssembleConfig___HPP


#include "B2PreprocDefs.hpp"

enum B2AssembleConfigTxtId
{
	///////////////
	B2_ASSEMBLE_CFG_TXT_COUNT = 1
};

enum B2AssembleConfigNumId
{
	///////////////
	B2_ASSEMBLE_CFG_NUM_COUNT = B2_ASSEMBLE_CFG_TXT_COUNT
};

enum B2AssembleConfigMsgId
{
	B2_MSG_ASSEMBLE_CFG = B2_ASSEMBLE_CFG_NUM_COUNT
};


class B2AssembleConfig
{
	B2HashMap<unsigned int, std::string> _argv;

public:
	B2AssembleConfig(const int argc, const char **argv);
	const std::string txt(B2AssembleConfigTxtId id) { return _argv[id]; };
	const double num(B2AssembleConfigNumId id) { return atof(_argv[id].c_str()); };
	const std::string msg(unsigned int id) { return _argv[B2_MSG_ASSEMBLE_CFG + id]; };
};

const std::string b2_assemble_config(B2AssembleConfigTxtId id);
const double b2_assemble_config(B2AssembleConfigNumId id);
const std::string b2_assemble_msg(unsigned int id);
void *b2_assemble_malloc(size_t size);
void b2_assemble_free(void *ptr);


#endif // B2AssembleConfig___HPP
