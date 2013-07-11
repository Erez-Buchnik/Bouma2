
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

#include "B2AssembleConfig.hpp"
#include "B2AssembleDiagnostics.hpp"


#ifndef B2_OVERRIDE_GLOBALS

B2AssembleConfig *assemble_config = NULL;
B2AssembleDiagnostics *assemble_diagnostics = NULL;


const std::string b2_assemble_config(B2AssembleConfigTxtId id) { return assemble_config->txt(id); };
const double b2_assemble_config(B2AssembleConfigNumId id) { return assemble_config->num(id); };
const std::string b2_assemble_msg(unsigned int id) { return assemble_config->msg(id); };
void *b2_assemble_malloc(size_t size) { b2_assemble_diagnostic_inc(B2_ASSEMBLE_DIAG_TOTAL_MEMORY, size); return malloc(size); };
void b2_assemble_free(void *ptr) { free(ptr); };;


const unsigned int b2_assemble_error_inc(B2AssembleErrorCounterId id, unsigned int delta) { return assemble_diagnostics->increment(id, delta); };
const unsigned int b2_assemble_diagnostic_inc(B2AssembleDiagCounterId id, unsigned int delta) { return assemble_diagnostics->increment(id, delta); };


#endif //B2_OVERRIDE_GLOBALS

