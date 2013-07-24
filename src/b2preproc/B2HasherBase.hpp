
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

#ifndef B2HasherBase___HPP
#define B2HasherBase___HPP

#include "B2MotifSet.hpp"


template <typename LPType> class B2HasherBase
{

protected:
	const B2TraceSet _trace_set;
	const B2StrSet &_str_set;
	LPType *_lp;

	B2MotifSet _motif_set;

public:
	B2HasherBase(const B2StrSet &str_set) : _trace_set(str_set), _str_set(str_set) { };
	const B2MotifSet &motif_set()
	{
		if(_motif_set.size() > 0)
		{
			return _motif_set;
		}
		else
		{
			b2_preproc_error_inc(B2_PREPROC_ERROR_BAD_MOTIF_SET, 1);
			return _motif_set;
		};
	};
};


#endif //B2HasherBase___HPP

