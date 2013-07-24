
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

#ifndef B2PreprocApi___H
#define B2PreprocApi___H


struct B2Preprocessor;

B2Preprocessor *b2_preproc_create();
void b2_preproc_destroy(B2Preprocessor *preprocessor);

void b2_preproc_add_str(B2Preprocessor *preprocessor, unsigned int str_id, unsigned char *str_bytes, unsigned int str_length);
const char *b2_preproc_dump_strs(B2Preprocessor *preprocessor);
void b2_preproc_execute(B2Preprocessor *preprocessor);
const char *b2_preproc_dump_motifs(B2Preprocessor *preprocessor);

#endif //B2PreprocApi___H

