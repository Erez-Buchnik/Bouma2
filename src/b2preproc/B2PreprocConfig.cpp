
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
#include "B2PreprocDiagnostics.hpp"

#define B2_CONFIG_DEFAULT "b2default"

B2PreprocConfig::B2PreprocConfig(const int argc, const char **argv)
{
	// Text default config:
	_argv[B2_CFG_STR_SET_FILE] = "str_set.txt";
	_argv[B2_CFG_GLPK_DEBUG_FILE] = "B2-ILP.txt";
	// Number default config:
	_argv[B2_CFG_COVERAGE_PURGE_FACTOR] = "0.1";
	_argv[B2_CFG_DIVERSITY_PURGE_FACTOR] = "0.9";
	// Message default config:
	_argv[B2_MSG_CONFIG + B2_PREPROC_ERROR_UNSPECIFIED] = "Preproc ERROR: Unspecified Error";
	_argv[B2_MSG_CONFIG + B2_PREPROC_ERROR_BAD_TRACE_SET] = "Preproc ERROR: Bad Trace-Set";
	_argv[B2_MSG_CONFIG + B2_PREPROC_ERROR_BAD_MOTIF_SET] = "Preproc ERROR: Bad Motif-Set";
	_argv[B2_MSG_CONFIG + B2_PREPROC_ERROR_PATTERN_STR_NOT_FOUND] = "Preproc ERROR: Pattern-String Not Found";
	_argv[B2_MSG_CONFIG + B2_PREPROC_ERROR_MGT_BAD_OFFSET_MAP] = "Preproc ERROR: Bad Mangled-Trie Offset-Map";
	_argv[B2_MSG_CONFIG + B2_PREPROC_ERROR_MGT_INCONSISTENT_SCORE] = "Preproc ERROR: Inconsistent Mangled-Trie Offset Score";
	_argv[B2_MSG_CONFIG + B2_PREPROC_ERROR_MGT_OFFSET_NOT_FOUND] = "Preproc ERROR: Mangled-Trie Offset Not Found";
	_argv[B2_MSG_CONFIG + B2_PREPROC_ERROR_MGT_BAD_BYTE_CHOICES_MAP] = "Preproc ERROR: Bad Mangled-Trie Byte-Choices Map";
	_argv[B2_MSG_CONFIG + B2_PREPROC_ERROR_MGT_STATE_NOT_FOUND] = "Preproc ERROR: Mangled-Trie State Not Found";
	_argv[B2_MSG_CONFIG + B2_PREPROC_ERROR_MGT_BAD_TERMINAL] = "Preproc ERROR: Bad Mangled-Trie Terminal";
	_argv[B2_MSG_CONFIG + B2_PREPROC_ERROR_PATTERN_STR_TOO_SHORT] = "Preproc ERROR: Pattern-String Too Short";
	_argv[B2_MSG_CONFIG + B2_PREPROC_ERROR_TRACE_OFFSET_OUT_OF_RANGE] = "Preproc ERROR: Trace-Offset is Out of Range";
	//////////////////////
	_argv[B2_MSG_CONFIG + B2_PREPROC_DIAG_ADDED_PATTERN_STR] = "Preprocessing: Added Pattern-String";
	_argv[B2_MSG_CONFIG + B2_PREPROC_DIAG_ADDED_TRACE_COEFF] = "Preprocessing: Added Trace Coefficient";
	_argv[B2_MSG_CONFIG + B2_PREPROC_DIAG_ADDED_TRANSITIONAL] = "Preprocessing: Mangled-Trie Transitional";
	_argv[B2_MSG_CONFIG + B2_PREPROC_DIAG_ADDED_PIVOT] = "Preprocessing: Mangled-Trie Pivot";
	_argv[B2_MSG_CONFIG + B2_PREPROC_DIAG_ADDED_SINGLE_STR_PIVOT] = "Preprocessing: Mangled-Trie Single-String Pivot";
	_argv[B2_MSG_CONFIG + B2_PREPROC_DIAG_ADDED_STATE] = "Preprocessing: Mangled-Trie State";
	_argv[B2_MSG_CONFIG + B2_PREPROC_DIAG_ADDED_TERMINAL] = "Preprocessing: Mangled-Trie Terminal";
	_argv[B2_MSG_CONFIG + B2_PREPROC_DIAG_MISSING_COEFF_FOR_MOTIF] = "Preprocessing: Missing Coefficient for Motif";
	for(int i = 0; i < argc; ++i)
	{
		std::string argv_txt(argv[i]);
		if(argv_txt != B2_CONFIG_DEFAULT)
		{
			_argv[i] = argv_txt;
		};
	};
};
