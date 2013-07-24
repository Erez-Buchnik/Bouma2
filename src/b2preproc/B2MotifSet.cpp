
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

#include "B2MotifSet.hpp"

void B2MotifSet::remove_duplicates(const B2TraceCoeffs &trace_coeffs)
{
	B2MotifCoeffs motif_coeffs((*this), trace_coeffs);
	B2HashMap<std::string, B2TraceStruct> str_mappings_even;
	B2HashMap<std::string, B2TraceStruct> str_mappings_odd;
	for(iterator motif_it = begin(); motif_it != end(); ++motif_it)
	{
		B2Trace motif = motif_it->first;
		std::vector<B2TraceStruct> &traces_vec = motif_it->second;
		for(std::vector<B2TraceStruct>::iterator struct_it = traces_vec.begin(); struct_it != traces_vec.end(); )
		{
			B2TraceStruct &trace_struct = *struct_it;
			B2HashMap<std::string, B2TraceStruct> *str_mappings = &str_mappings_even;
			if(trace_struct.parity() == 1)
			{
				str_mappings = &str_mappings_odd;
			};
			B2HashMap<std::string, B2TraceStruct>::iterator find_it = str_mappings->find(trace_struct.str());
			if(find_it == str_mappings->end())
			{
				(*str_mappings)[trace_struct.str()] = trace_struct;
				++struct_it;
				continue;
			}
			else
			{
				B2TraceStruct &prev_struct = find_it->second;
				B2Trace prev_motif = prev_struct.trace_val(); 
				double prev_coeff = motif_coeffs[prev_motif];
				double curr_coeff = motif_coeffs[motif];
				if(curr_coeff < prev_coeff)
				{
					remove_mapping(prev_struct);
					find_it->second = trace_struct;
					++struct_it;
					continue;
				}
				else
				{
					struct_it = traces_vec.erase(struct_it);
					continue;
				};
			};
		};
	};
};


B2MotifCoeffs::B2MotifCoeffs(const B2MotifSet &motif_set, const B2TraceCoeffs &trace_coeffs) : 
	B2TraceCoeffs(trace_coeffs), _motif_set(motif_set)
{
	for(B2HashMap<B2Trace, double>::iterator coeff_it = _coeffs.begin(); coeff_it != _coeffs.end(); )
	{
		B2MotifSet::const_iterator find_it = _motif_set.find(coeff_it->first);
		if(find_it == _motif_set.end())
		{
			B2_HASH_MAP_ERASE(_coeffs, coeff_it);
		}
		else
		{
			++coeff_it;
		};
	};
};


double B2MotifCoeffs::operator [] (B2Trace trace) const
{
	B2MotifSet::const_iterator find_it = _motif_set.find(trace);
	if(find_it != _motif_set.end())
	{
		double complexity_factor = (double)(find_it->second.size()) / (double)(_motif_set.str_count());
		double prevalence_factor = ((B2TraceCoeffs &)(*this))[trace];
		return (prevalence_factor * complexity_factor);
	}
	else
	{
		b2_preproc_diagnostic_inc(B2_PREPROC_DIAG_MISSING_COEFF_FOR_MOTIF, 1);
		return 1.0;
	};
};

