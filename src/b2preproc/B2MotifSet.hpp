
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

#ifndef B2MotifSet___HPP
#define B2MotifSet___HPP

#include "B2TraceSet.hpp"


class B2MotifSet : public B2TraceSet
{

public:
	B2MotifSet() { };
	B2MotifSet(const B2TraceSet &trace_set) : B2TraceSet(trace_set) { };
	B2HashMap<B2Trace, unsigned int> &trace_vals() { return _trace_vals; };
	void remove_duplicates(const B2TraceCoeffs &trace_coeffs);
	void remove_mapping(const B2TraceStruct &trace_struct)
	{
		B2Trace motif = trace_struct.trace_val();
		iterator motif_it = find(motif);
		if(motif_it != end())
		{
			std::vector<B2TraceStruct> &traces_vec = motif_it->second;
			for(std::vector<B2TraceStruct>::iterator struct_it = traces_vec.begin(); struct_it != traces_vec.end(); ++struct_it)
			{
				if(*struct_it != trace_struct)
				{
					continue;
				}
				else
				{
					traces_vec.erase(struct_it);
					return;
				};
			};
		};
	};
};


class B2MotifCoeffs : public B2TraceCoeffs
{
	const B2MotifSet &_motif_set;

public:
	B2MotifCoeffs(const B2MotifSet &motif_set, const B2TraceCoeffs &trace_coeffs);
	double operator [] (B2Trace trace) const;
};


#endif //B2MotifSet___HPP

