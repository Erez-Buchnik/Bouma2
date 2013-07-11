
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

#ifndef B2MgTAssembler___HPP
#define B2MgTAssembler___HPP


#include "B2StateAssembler.hpp"
#include "B2TerminalAssembler.hpp"
#include "B2AssembleConfig.hpp"


class B2MgTAssembler
{
	B2StateAssembler _state_assembler;
	B2TerminalAssembler _terminal_assembler;

	template <class StateType> B2SPMatch<StateType> *assemble(unsigned int mgt_size)
	{
		B2SPMatch<StateType> *sp_match = new(b2_assemble_malloc(mgt_size)) B2SPMatch<StateType>;
		StateType *states_vec = sp_match->states_vec();
		_state_assembler.assemble(states_vec);
		B2SPTerminal *terminals_vec = sp_match->terminals_vec(states_vec);
		_terminal_assembler.assemble(terminals_vec);
		return sp_match;
	};

public:
	B2MgTAssembler(const B2MgTStateMachine &mgt_state_machine) :
		_state_assembler(mgt_state_machine), _terminal_assembler(mgt_state_machine.terminals()) { };
	B2SPMatchBase *assemble();
};


#endif //B2MgTAssembler___HPP

