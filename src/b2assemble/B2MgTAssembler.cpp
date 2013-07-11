
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

#include "B2MgTAssembler.hpp"


B2SPMatchBase *B2MgTAssembler::assemble()
{
	B2SPMatchBase *sp_match = NULL;
	unsigned int mgt_size = _state_assembler.size() + _terminal_assembler.size();
	if(_state_assembler.state_count() > 0)
	{
		switch(_state_assembler.transition_width())
		{
		case B2SP_2BIT_TRANSITION:
			sp_match = assemble<B2SP2BitState>(mgt_size);
			break;
		case B2SP_4BIT_TRANSITION:
			sp_match = assemble<B2SP4BitState>(mgt_size);
			break;
		case B2SP_8BIT_TRANSITION:
			sp_match = assemble<B2SP8BitState>(mgt_size);
			break;
		case B2SP_16BIT_TRANSITION:
		default:
			sp_match = assemble<B2SP16BitState>(mgt_size);
			break;
		};
	}
	else
	{
	};
	return sp_match;
};

