
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

void b2_test(char *strings_file_path)
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
	for(B2MotifSet::const_iterator motif_it = motif_set.begin(); motif_it != motif_set.end(); ++motif_it)
	{
		const std::vector<B2TraceStruct> &trace_vec = motif_it->second;
		const B2MangledTrie &mangled_trie(trace_vec);
		const B2TraceStruct &trace_struct = *(trace_vec.begin());
		printf("%s:%02X[%02ld]", trace_struct.chars().c_str(), motif_it->first, trace_vec.size());
		for(std::vector<B2TraceStruct>::const_iterator trace_it = trace_vec.begin(); trace_it != trace_vec.end(); ++trace_it)
		{
			printf("(%d)%s ", trace_it->offset(), trace_it->str().c_str());
		};
		printf("\n");
	};
	/////////////////////////////////////////
};

int main(int argc, char *argv[])
{
	b2_test(argv[1]);
	exit(0);
};
