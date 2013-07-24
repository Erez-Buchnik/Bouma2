
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


#include "B2AssembleApi.h"


typedef struct B2Assembler
{
	const B2Preprocessor *_preprocessor;
	B2Assembler(const B2Preprocessor *preprocessor) : _preprocessor(preprocessor) { };
} B2Assembler;


B2Assembler *b2_assemble_create(const B2Preprocessor *preprocessor)
{
	B2Assembler *assembler = new B2Assembler(preprocessor);
	return assembler;
};


void b2_assemble_destroy(B2Assembler *assembler)
{
	if(assembler)
	{
		delete assembler;
	};
};


void b2_assemble_execute(B2Assembler *assembler)
{
};

