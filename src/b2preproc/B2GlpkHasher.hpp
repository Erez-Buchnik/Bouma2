
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

#ifndef B2GlpkHasher___HPP
#define B2GlpkHasher___HPP

#include "B2HasherBase.hpp"
#include <glpk.h>


class B2GlpkHasher : public B2HasherBase<glp_prob>
{
	struct ConstraintBounds
	{
		unsigned int _constraint_idx;
		std::string _str;
		unsigned int _upper_bound;
		ConstraintBounds(unsigned int constraint_idx, const std::string &str, unsigned int upper_bound) : _constraint_idx(constraint_idx), _str(str), _upper_bound(upper_bound) { };
	};
	struct ConstraintCoeff
	{
		unsigned int _constraint_idx;
		unsigned int _trace_var_idx;
		unsigned int _coeff;
		ConstraintCoeff(unsigned int constraint_idx, unsigned int trace_var_idx, unsigned int coeff) : _constraint_idx(constraint_idx), _trace_var_idx(trace_var_idx), _coeff(coeff) { };
	};

	void add_trace_vars(const B2TraceCoeffs &trace_coeffs);
	unsigned int add_single_constraint(unsigned int constraint_idx, const char *traces_begin, const char *traces_limit, std::vector<ConstraintCoeff> &constraint_coeffs_vec);
	void add_str_constraints();
	void build_hash();

public:
	B2GlpkHasher(const B2TraceCoeffs &trace_coeffs, const B2StrSet &str_set);
};

typedef B2GlpkHasher B2Hasher;


#endif //B2GlpkHasher___HPP

