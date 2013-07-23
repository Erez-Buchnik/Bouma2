
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


#include "B2PreprocApi.h"
#include "B2StrSet.hpp"
#include "B2Hasher.hpp"
#include "B2MangledTrie.hpp"
#include <sstream>


typedef struct B2Preprocessor
{
	B2StrSet _str_set;
} B2Preprocessor;


B2Preprocessor *b2_preproc_create()
{
	return new B2Preprocessor;
};


void b2_preproc_destroy(B2Preprocessor *preprocessor)
{
	delete preprocessor;
};


void b2_preproc_add_str(B2Preprocessor *preprocessor, unsigned int str_id, unsigned char *str_bytes, unsigned int str_length)
{
	B2Str str(str_id, str_bytes, str_length);
	preprocessor->_str_set.add_str(str);
};


const char *b2_preproc_dump_strs(B2Preprocessor *preprocessor)
{
	static std::string dump_buf; // TODO: make thread-safe
	std::stringstream ss;
	B2HashSorter<B2StrSet> strs_sorter(preprocessor->_str_set);
	strs_sorter.sort_by_value();
	for(B2HashSorter<B2StrSet>::const_iterator str_it = strs_sorter.begin(); str_it != strs_sorter.end(); ++str_it)
	{
		const B2StrStruct &str_struct = (*str_it)->second;
		ss << "str#" << str_struct.id() << ":" << str_struct;
		const std::vector<unsigned int> &duplicate_ids = str_struct.duplicate_ids_vec();
		if(duplicate_ids.size() > 0)
		{
			ss << " [dup:";
			for(std::vector<unsigned int>::const_iterator dup_it = duplicate_ids.begin(); dup_it != duplicate_ids.end(); ++dup_it)
			{
				ss << " " << *dup_it;
			};
			ss << "]";
		};
		ss << std::endl;
	};
	ss << "-- " << strs_sorter.size() << " strs" << std::endl;
	dump_buf = ss.str();
	return dump_buf.c_str();
};


void b2_preproc_execute(B2Preprocessor *preprocessor)
{
	B2TraceCoeffs trace_coeffs;
	B2Hasher hasher(trace_coeffs, preprocessor->_str_set);
	const B2MotifSet &motif_set = hasher.motif_set();
	for(B2MotifSet::const_iterator motif_it = motif_set.begin(); motif_it != motif_set.end(); ++motif_it)
	{
		const std::vector<B2TraceStruct> &trace_vec = motif_it->second;
		B2MangledTrie mangled_trie(preprocessor->_str_set, trace_vec);
		mangled_trie.build();
		mangled_trie.reshuffle_state_machine();
	};
};

