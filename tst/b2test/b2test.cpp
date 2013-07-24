
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
#include "B2AssembleApi.h"
#include <stdio.h>
#include <string.h>

void b2_test(const char *strings_file_path)
{
	B2Preprocessor *b2_preprocessor = b2_preproc_create();
	char str_bytes[128];
	FILE *f_strs = fopen(strings_file_path, "r");
	unsigned int str_count = 0;
	while(fgets(str_bytes, 128, f_strs) != NULL)
	{
		b2_preproc_add_str(b2_preprocessor, str_count, (unsigned char *)str_bytes, (strlen(str_bytes) - 1));
		++str_count;
	};
	fclose(f_strs);
	printf("%s\n", b2_preproc_dump_strs(b2_preprocessor));

	b2_preproc_execute(b2_preprocessor);
	printf("%s\n", b2_preproc_dump_motifs(b2_preprocessor));

	B2Assembler *b2_assembler = b2_assemble_create(b2_preprocessor);
};

#include "B2PreprocConfig.hpp"
#include "B2PreprocDiagnostics.hpp"
B2PreprocConfig *preproc_config = NULL;
B2PreprocDiagnostics *preproc_diagnostics = NULL;

const std::string b2_preproc_config(B2PreprocConfigTxtId id) { return preproc_config->txt(id); };
const double b2_preproc_config(B2PreprocConfigNumId id) { return preproc_config->num(id); };
const std::string b2_preproc_msg(unsigned int id) { return preproc_config->msg(id); };

const unsigned int b2_preproc_error_inc(B2PreprocErrorCounterId id, unsigned int delta) { return preproc_diagnostics->increment(id, delta); };
const unsigned int b2_preproc_diagnostic_inc(B2PreprocDiagCounterId id, unsigned int delta) { return preproc_diagnostics->increment(id, delta); };

int main(int argc, char *argv[])
{
	preproc_config = new B2PreprocConfig(argc, (const char **)argv);
	preproc_diagnostics = new B2PreprocDiagnostics;
	b2_test(preproc_config->txt(B2_CFG_STR_SET_FILE).c_str());
	printf("\n%s\n", preproc_diagnostics->dump().c_str());
	exit(0);
};
