
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

#ifndef B2TerminalAssembler___HPP
#define B2TerminalAssembler___HPP


#include "B2MgTTerminal.hpp"
#include "B2SPTerminal.hpp"
#include "B2SPSegmentMatch.hpp"


class B2TerminalAssembler
{
	B2HashMap<unsigned int, B2MgTTerminal> _terminals;

	struct SegmentSpecifier
	{
		unsigned int _terminal_id;
		int _segment_relative_offset;
		unsigned int _segment_length;
	};

	std::vector<SegmentSpecifier> _piling_sequence;

	std::vector<B2SPTerminal> _terminals_vec;
	std::vector<B2SPSegmentMatch> _segments_vec;
	std::string _segment_pile;

	void add_to_pile(const SegmentSpecifier &segment_specifier);

public:
	B2TerminalAssembler(const B2HashMap<unsigned int, B2MgTTerminal> &terminals) : _terminals(terminals) { };
	void assemble();
};


#endif //B2TerminalAssembler___HPP

