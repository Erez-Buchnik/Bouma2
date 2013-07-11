
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

#include "B2AssembleConfig.hpp"
#include "B2AssembleDiagnostics.hpp"

#define B2_ASSEMBLE_CFG_DEFAULT "b2default"

B2AssembleConfig::B2AssembleConfig(const int argc, const char **argv)
{
	// Text default config:
	//
	// Number default config:
	//
	// Message default config:
	_argv[B2_MSG_ASSEMBLE_CFG + B2_ASSEMBLE_ERROR_UNSPECIFIED] = "Assemble ERROR: Unspecified Error";
	_argv[B2_MSG_ASSEMBLE_CFG + B2_ASSEMBLE_ERROR_OUT_OF_MEMORY] = "Assemble ERROR: Out of Memory";
	//////////////////////
	_argv[B2_MSG_ASSEMBLE_CFG + B2_ASSEMBLE_DIAG_MOTIF_MAP_MEMORY] = "Assembly: Motif-Map Memory";
	_argv[B2_MSG_ASSEMBLE_CFG + B2_ASSEMBLE_DIAG_MOTIF_VEC_MEMORY] = "Assembly: Motif-Vector Memory";
	_argv[B2_MSG_ASSEMBLE_CFG + B2_ASSEMBLE_DIAG_MANGLED_TRIES_ALLOCATED] = "Assembly: Mangled-Tries Count";
	_argv[B2_MSG_ASSEMBLE_CFG + B2_ASSEMBLE_DIAG_2BIT_STATES_ALLOCATED] = "Assembly: 2-Bit States Count";
	_argv[B2_MSG_ASSEMBLE_CFG + B2_ASSEMBLE_DIAG_4BIT_STATES_ALLOCATED] = "Assembly: 4-Bit States Count";
	_argv[B2_MSG_ASSEMBLE_CFG + B2_ASSEMBLE_DIAG_8BIT_STATES_ALLOCATED] = "Assembly: 8-Bit States Count";
	_argv[B2_MSG_ASSEMBLE_CFG + B2_ASSEMBLE_DIAG_16BIT_STATES_ALLOCATED] = "Assembly: 16-Bit States Count";
	_argv[B2_MSG_ASSEMBLE_CFG + B2_ASSEMBLE_DIAG_TERMINALS_ALLOCATED] = "Assembly: Terminals Count";
	_argv[B2_MSG_ASSEMBLE_CFG + B2_ASSEMBLE_DIAG_SEGMENTS_ALLOCATED] = "Assembly: Terminal Segments Count";
	_argv[B2_MSG_ASSEMBLE_CFG + B2_ASSEMBLE_DIAG_SEGMENT_PILE_MEMORY] = "Assembly: Segment Piles Memory";
	_argv[B2_MSG_ASSEMBLE_CFG + B2_ASSEMBLE_DIAG_TOTAL_MEMORY] = "Assembly: Total Memory";
	for(int i = 0; i < argc; ++i)
	{
		std::string argv_txt(argv[i]);
		if(argv_txt != B2_ASSEMBLE_CFG_DEFAULT)
		{
			_argv[i] = argv_txt;
		};
	};
};
