
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

#include "B2MgTStateMachine.hpp"


B2MgTState &B2MgTStateMachine::new_state(int relative_offset)
{
	(*this)[_node_count] = B2MgTState(relative_offset, _node_count);
	b2_preproc_diagnostic(B2_PREPROC_DIAG_ADDED_STATE);
	return (*this)[_node_count++];
};


const B2MgTTerminal &B2MgTStateMachine::new_terminal(const B2MgTStrInstance &str_instance)
{
	B2MgTTerminal terminal(str_instance.str_id(), str_instance.relative_offset(), _node_count);
	std::string segment;
	for(int offset = str_instance.next_segment(segment); 
		offset < str_instance.relative_end_offset(); 
		offset = str_instance.next_segment(segment, offset))
	{
		terminal[offset] = segment;
		offset += segment.size();
	};
	for(B2HashMap<unsigned int, B2MgTTerminal>::const_iterator match_it = _terminals.begin(); match_it != _terminals.end(); ++match_it)
	{
		if(match_it->second == terminal)
		{
			return match_it->second;
		};
	};
	_terminals[_node_count] = terminal;
	b2_preproc_diagnostic(B2_PREPROC_DIAG_ADDED_TERMINAL);
	return _terminals[_node_count++];
};


std::string B2MgTStateMachine::dump() const
{
	std::string str_out = "";
	for(const_iterator state_it = begin(); state_it != end(); ++state_it)
	{
		str_out += state_it->second.dump() + "\n";
	};
	for(B2HashMap<unsigned int, B2MgTTerminal>::const_iterator terminal_it = _terminals.begin(); terminal_it != _terminals.end(); ++terminal_it)
	{
		str_out += terminal_it->second.dump() + "\n";
	};
	return str_out;
};
