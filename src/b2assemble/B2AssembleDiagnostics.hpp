
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

#ifndef B2AssembleDiagnostics___HPP
#define B2AssembleDiagnostics___HPP


#include "B2PreprocDefs.hpp"

enum B2AssembleErrorCounterId
{
	B2_ASSEMBLE_ERROR_UNSPECIFIED = 1,
	B2_ASSEMBLE_ERROR_OUT_OF_MEMORY,
	///////////////
	B2_ASSEMBLE_ERRORS
};

enum B2AssembleDiagCounterId
{
	B2_ASSEMBLE_DIAG_MOTIF_MAP_MEMORY = B2_ASSEMBLE_ERRORS,
	B2_ASSEMBLE_DIAG_MOTIF_VEC_MEMORY,
	B2_ASSEMBLE_DIAG_MANGLED_TRIES_ALLOCATED,
	B2_ASSEMBLE_DIAG_2BIT_STATES_ALLOCATED,
	B2_ASSEMBLE_DIAG_4BIT_STATES_ALLOCATED,
	B2_ASSEMBLE_DIAG_8BIT_STATES_ALLOCATED,
	B2_ASSEMBLE_DIAG_16BIT_STATES_ALLOCATED,
	B2_ASSEMBLE_DIAG_TERMINALS_ALLOCATED,
	B2_ASSEMBLE_DIAG_SEGMENTS_ALLOCATED,
	B2_ASSEMBLE_DIAG_SEGMENT_PILE_MEMORY,
	B2_ASSEMBLE_DIAG_TOTAL_MEMORY,
	///////////////
	B2_ASSEMBLE_DIAGNOSTICS
};

class B2AssembleDiagnostics
{
	B2HashMap<unsigned int, unsigned int> _counters;

public:
	const unsigned int increment(B2AssembleErrorCounterId id, unsigned int delta) { return (_counters[id] += delta); };
	const unsigned int increment(B2AssembleDiagCounterId id, unsigned int delta) { return (_counters[id] += delta); };
	const unsigned int counter(B2AssembleErrorCounterId id) const
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

const unsigned int b2_assemble_error_inc(B2AssembleErrorCounterId id, unsigned int delta);
const unsigned int b2_assemble_diagnostic_inc(B2AssembleDiagCounterId id, unsigned int delta);


#endif // B2AssembleDiagnostics___HPP
