
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

#include "B2GlpkHasher.hpp"

#define FFFFF B2_GLPK_DEBUG_FILE

B2GlpkHasher::B2GlpkHasher(const B2TraceCoeffs &trace_coeffs, const B2StrSet &str_set) : B2HasherBase(str_set)
{
	_lp = glp_create_prob();
	glp_set_prob_name(_lp, "Bouma2-GLPK");
	glp_set_obj_dir(_lp, GLP_MIN);
	add_trace_vars(trace_coeffs);
	add_str_constraints();
#ifdef B2_GLPK_DEBUG
	glp_write_prob(_lp, 0, b2_preproc_config(B2_GLPK_DEBUG_FILE).c_str());
#endif //B2_GLPK_DEBUG
	build_hash();
	_motif_set.remove_duplicates(trace_coeffs);
};


void B2GlpkHasher::add_trace_vars(const B2TraceCoeffs &trace_coeffs)
{
	const B2HashMap<B2Trace, unsigned int> &trace_vals = _trace_set.trace_vals();
	glp_add_cols(_lp, trace_vals.size());
	for(B2HashMap<B2Trace, unsigned int>::const_iterator trace_it = trace_vals.begin(); trace_it != trace_vals.end(); ++trace_it)
	{
		B2Trace trace = trace_it->first;
		unsigned int trace_var_idx = trace_it->second;
		glp_set_col_kind(_lp, trace_var_idx, GLP_BV);
		glp_set_col_name(_lp, trace_var_idx, B2TraceName(trace).name());
		glp_set_col_bnds(_lp, trace_var_idx, GLP_DB, 0.0, 1.0);
		glp_set_obj_coef(_lp, trace_var_idx, trace_coeffs[trace]);
	};
};


unsigned int B2GlpkHasher::add_single_constraint(unsigned int constraint_idx, const char *traces_begin, const char *traces_limit, std::vector<ConstraintCoeff> &constraint_coeffs_vec)
{
	unsigned int upper_bound = 0;
	B2HashMap<B2Trace, unsigned int> constraint_coeffs;
	for(const unsigned short *trace = (const unsigned short *)traces_begin; trace <= (const unsigned short *)traces_limit; ++trace)
	{
		++constraint_coeffs[*trace];
		++upper_bound;
	};
	const B2HashMap<B2Trace, unsigned int> &trace_vals = _trace_set.trace_vals();
	for(B2HashMap<B2Trace, unsigned int>::const_iterator coeff_it = constraint_coeffs.begin(); coeff_it != constraint_coeffs.end(); ++coeff_it)
	{
		B2Trace trace = coeff_it->first;
		B2HashMap<B2Trace, unsigned int>::const_iterator trace_it = trace_vals.find(trace);
		if(trace_it != trace_vals.end())
		{
			unsigned int trace_var_idx = trace_it->second;
			unsigned int coeff = coeff_it->second;
			constraint_coeffs_vec.push_back(ConstraintCoeff(constraint_idx, trace_var_idx, coeff));
		}
		else
		{
			b2_preproc_error(B2_PREPROC_ERROR_BAD_TRACE_SET);
		};
	};
	return upper_bound;
};


void B2GlpkHasher::add_str_constraints()
{
	std::vector<ConstraintBounds> constraint_bounds_vec;
	std::vector<ConstraintCoeff> constraint_coeffs_vec;
	unsigned int constraint_idx = 0;
	for(B2StrSet::const_iterator str_it = _str_set.begin(); str_it != _str_set.end(); ++str_it)
	{
		const std::string &str = str_it->first;
		const char *first_even_trace = str.c_str();
		const char *first_odd_trace = (str.c_str() + 1);
		const char *trace_limit = (str.c_str() + str.size() - 2);
		unsigned int even_upper_bound = add_single_constraint(++constraint_idx, first_even_trace, trace_limit, constraint_coeffs_vec);
		constraint_bounds_vec.push_back(ConstraintBounds(constraint_idx, std::string("E") + str, even_upper_bound));
		unsigned int odd_upper_bound = add_single_constraint(++constraint_idx, first_odd_trace, trace_limit, constraint_coeffs_vec);
		constraint_bounds_vec.push_back(ConstraintBounds(constraint_idx, std::string("O") + str, odd_upper_bound));
	};

	glp_add_rows(_lp, constraint_bounds_vec.size());
	for(std::vector<ConstraintBounds>::const_iterator bounds_it = constraint_bounds_vec.begin(); bounds_it != constraint_bounds_vec.end(); ++bounds_it)
	{
		const ConstraintBounds &bounds = *bounds_it;
		glp_set_row_name(_lp, bounds._constraint_idx, bounds._str.c_str());
		if(bounds._upper_bound > 1)
		{
			glp_set_row_bnds(_lp, bounds._constraint_idx, GLP_DB, 1, bounds._upper_bound);
		}
		else
		{
			glp_set_row_bnds(_lp, bounds._constraint_idx, GLP_FX, 1, 1);
		};
	};

	int *ia = new int[1 + constraint_coeffs_vec.size()];
	int *ja = new int[1 + constraint_coeffs_vec.size()];
	double *ar = new double[1 + constraint_coeffs_vec.size()];
	unsigned int coeff_count = 0;
	for(std::vector<ConstraintCoeff>::const_iterator coeffs_it = constraint_coeffs_vec.begin(); coeffs_it != constraint_coeffs_vec.end(); ++coeffs_it)
	{
		const ConstraintCoeff &coeff = *coeffs_it;
		++coeff_count;
		ia[coeff_count] = coeff._constraint_idx, ja[coeff_count] = coeff._trace_var_idx, ar[coeff_count] = coeff._coeff; /* a[constraint_idx,trace_var_idx] = coeff */
	};
	glp_load_matrix(_lp, coeff_count, ia, ja, ar);
	delete [] ia;
	delete [] ja;
	delete [] ar;
};


void B2GlpkHasher::build_hash()
{
	glp_simplex(_lp, NULL);
	glp_iocp parm;
	glp_init_iocp(&parm);
	parm.presolve = GLP_ON;
	parm.binarize = GLP_ON;
	glp_intopt(_lp, &parm);
	double motif_count = glp_mip_obj_val(_lp);
	if((motif_count > 0) && (motif_count <= (_str_set.size() * 2)))
	{
		_motif_set = _trace_set;
		B2HashMap<B2Trace, unsigned int> &trace_vals = _motif_set.trace_vals();
		for(B2HashMap<B2Trace, unsigned int>::iterator trace_it = trace_vals.begin(); trace_it != trace_vals.end(); )
		{
			double is_motif = glp_mip_col_val(_lp, trace_it->second);
			if(is_motif == 0)
			{
				_motif_set.erase(trace_it->first);
				B2_HASH_MAP_ERASE(trace_vals, trace_it);
			}
			else
			{
				++trace_it;
			};
		};
	}
	else
	{
		b2_preproc_error(B2_PREPROC_ERROR_BAD_MOTIF_SET);
	};
};

