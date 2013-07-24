
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

#ifndef B2PreprocDiagnostics___HPP
#define B2PreprocDiagnostics___HPP


#include "B2PreprocDefs.hpp"

enum B2PreprocErrorCounterId
{
	B2_PREPROC_ERROR_UNSPECIFIED = 1,
	B2_PREPROC_ERROR_BAD_TRACE_SET,
	B2_PREPROC_ERROR_BAD_MOTIF_SET,
	B2_PREPROC_ERROR_PATTERN_STR_NOT_FOUND,
	B2_PREPROC_ERROR_MGT_BAD_OFFSET_MAP,
	B2_PREPROC_ERROR_MGT_INCONSISTENT_SCORE,
	B2_PREPROC_ERROR_MGT_OFFSET_NOT_FOUND,
	B2_PREPROC_ERROR_MGT_BAD_BYTE_CHOICES_MAP,
	B2_PREPROC_ERROR_MGT_STATE_NOT_FOUND,
	B2_PREPROC_ERROR_MGT_BAD_TERMINAL,
	B2_PREPROC_ERROR_PATTERN_STR_TOO_SHORT,
	B2_PREPROC_ERROR_TRACE_OFFSET_OUT_OF_RANGE,
	///////////////
	B2_PREPROC_ERRORS
};

enum B2PreprocDiagCounterId
{
	B2_PREPROC_DIAG_ADDED_PATTERN_STR = B2_PREPROC_ERRORS,
	B2_PREPROC_DIAG_ADDED_PATTERN_BYTES,
	B2_PREPROC_DIAG_ADDED_TRACE_COEFF,
	B2_PREPROC_DIAG_ADDED_TRANSITIONAL,
	B2_PREPROC_DIAG_ADDED_PIVOT,
	B2_PREPROC_DIAG_ADDED_SINGLE_STR_PIVOT,
	B2_PREPROC_DIAG_ADDED_STATE,
	B2_PREPROC_DIAG_ADDED_TERMINAL,
	B2_PREPROC_DIAG_MISSING_COEFF_FOR_MOTIF,
	///////////////
	B2_PREPROC_DIAGNOSTICS
};

class B2PreprocDiagnostics
{
	B2HashMap<unsigned int, unsigned int> _counters;

public:
	const unsigned int increment(B2PreprocErrorCounterId id, unsigned int delta) { return (_counters[id] += delta); };
	const unsigned int increment(B2PreprocDiagCounterId id, unsigned int delta) { return (_counters[id] += delta); };
	const unsigned int counter(B2PreprocErrorCounterId id) const
	{
		B2HashMap<unsigned int, unsigned int>::const_iterator find_it = _counters.find(id);
		if(find_it != _counters.end())
		{
			return find_it->second;
		}
		else
		{
			return 0;
		};
	};
	std::string dump() const;
};

const unsigned int b2_preproc_error_inc(B2PreprocErrorCounterId id, unsigned int delta);
const unsigned int b2_preproc_diagnostic_inc(B2PreprocDiagCounterId id, unsigned int delta);


#endif // B2PreprocDiagnostics___HPP
