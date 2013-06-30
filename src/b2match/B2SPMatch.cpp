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


#include "B2SPMatch.hpp"
#include "B2SP2BitState.hpp"
#include "B2SP4BitState.hpp"
#include "B2SP8BitState.hpp"
#include "B2SP16BitState.hpp"


void B2SPMatchBase::match(unsigned int *&match_list, const unsigned char *motif_position) const
{
	switch(_transition_width)
	{
	case B2SP_SINGLE_TERMINAL:
		if(_terminals_count == 1)
		{
			match_single_terminal(match_list, motif_position);
			return;
		}
		else
		{
			break;
		};
	case B2SP_2BIT_TRANSITION:
		((B2SPMatch<B2SP2BitState> &)(*this)).match(match_list, motif_position);
		return;
	case B2SP_4BIT_TRANSITION:
		((B2SPMatch<B2SP4BitState> &)(*this)).match(match_list, motif_position);
		return;
	case B2SP_8BIT_TRANSITION:
		((B2SPMatch<B2SP8BitState> &)(*this)).match(match_list, motif_position);
		return;
	case B2SP_16BIT_TRANSITION:
		((B2SPMatch<B2SP16BitState> &)(*this)).match(match_list, motif_position);
		return;
	default:
		break;
	};
	//THROW
};

