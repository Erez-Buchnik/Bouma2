
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

#include "B2Hasher.hpp"
#include "B2MangledTrie.hpp"
#include <stdio.h>
#include <string.h>

void b2_test(const char *strings_file_path)
{
	B2StrSet str_set;
	FILE *f_strs = fopen(strings_file_path, "r");
	unsigned int str_count = 0;
	char str_bytes[128];
	while(fgets(str_bytes, 128, f_strs) != NULL)
	{
		B2Str str(str_count, (unsigned char *)str_bytes, (strlen(str_bytes) - 1));
		str_set.add_str(str);
		printf("str#%d:%s\n", str_count, str.c_str());
		++str_count;
	};
	fclose(f_strs);
	B2TraceCoeffs trace_coeffs;
	B2Hasher hasher(trace_coeffs, str_set);
	const B2MotifSet &motif_set = hasher.motif_set();
	/////////////////////////////////////////
	printf("motif count:%ld\n", motif_set.size());
	unsigned int mgt_total_state_count = 0;
	unsigned int mgt_total_terminal_count = 0;
	for(B2MotifSet::const_iterator motif_it = motif_set.begin(); motif_it != motif_set.end(); ++motif_it)
	{
		const std::vector<B2TraceStruct> &trace_vec = motif_it->second;
		unsigned int mgt_state_count = 0;
		unsigned int mgt_terminal_count = 0;
		if(trace_vec.size() > 1)
		{
			B2MangledTrie mangled_trie(str_set, trace_vec);
			int purge_offset = mangled_trie.select_purge_offset();
			mangled_trie.purge(purge_offset);
			mgt_state_count = mangled_trie.state_machine().size();
			mgt_terminal_count = mangled_trie.state_machine().terminals().size();
			printf("\n%s\n", mangled_trie.state_machine().dump().c_str());
		}
		else
		{
			B2MangledTrie mangled_trie(str_set, *trace_vec.begin());
			mgt_state_count = 0;
			mgt_terminal_count = 1;
			printf("\n%s\n", mangled_trie.state_machine().dump().c_str());
		};
		const B2TraceStruct &trace_struct = *(trace_vec.begin());
		printf("%s:<%02d,%02d>%02X[%02ld]", trace_struct.chars().c_str(), mgt_state_count, mgt_terminal_count, motif_it->first, trace_vec.size());
		for(std::vector<B2TraceStruct>::const_iterator trace_it = trace_vec.begin(); trace_it != trace_vec.end(); ++trace_it)
		{
			printf("(%d)%s ", trace_it->offset(), trace_it->str().c_str());
		};
		printf("\n");
		mgt_total_state_count += mgt_state_count;
		mgt_total_terminal_count += mgt_terminal_count;
	};
	printf("TOTALS:<%02d,%02d>\n", mgt_total_state_count, mgt_total_terminal_count);
	/////////////////////////////////////////
};

#include "B2PreprocConfig.hpp"
B2PreprocConfig *preproc_config = NULL;

const std::string b2_preproc_config(B2PreprocConfigTxtId id) { return preproc_config->txt(id); };
const double b2_preproc_config(B2PreprocConfigNumId id) { return preproc_config->num(id); };

int main(int argc, char *argv[])
{
	preproc_config = new B2PreprocConfig(argc, (const char **)argv);
	b2_test(preproc_config->txt(B2_STR_SET_FILE).c_str());
	exit(0);
};
