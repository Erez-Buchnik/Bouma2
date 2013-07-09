
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

#ifndef B2StateAssembler___HPP
#define B2StateAssembler___HPP


#include "B2MgTStateMachine.hpp"
#include "B2SP2BitState.hpp"
#include "B2SP4BitState.hpp"
#include "B2SP8BitState.hpp"
#include "B2SP16BitState.hpp"


class B2StateAssembler
{
	const B2MgTStateMachine &_mgt_state_machine;

	std::vector<B2SP2BitState> _2bit_states_vec;
	std::vector<B2SP4BitState> _4bit_states_vec;
	std::vector<B2SP8BitState> _8bit_states_vec;
	std::vector<B2SP16BitState> _16bit_states_vec;

	template <class StateType> void fill_state(const B2MgTState &mgt_state, std::vector<StateType> &states_vec)
	{
		StateType state;
		for(unsigned int byte_value = 0; byte_value < 256; ++byte_value)
		{
			B2MgTState::const_iterator find_it = mgt_state.find(byte_value);
			if(find_it == mgt_state.end())
			{
				state.set(byte_value, mgt_state.id(), mgt_state.id());
			}
			else
			{
				state.set(byte_value, mgt_state.id(), find_it->second);
			};
		};
		states_vec.push_back(state);
	};
	void fill();

public:
	B2StateAssembler(const B2MgTStateMachine &mgt_state_machine) : _mgt_state_machine(mgt_state_machine) { };
	void assemble();
};


#endif //B2StateAssembler___HPP

