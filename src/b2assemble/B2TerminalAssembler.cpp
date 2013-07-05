
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

#include "B2TerminalAssembler.hpp"


struct B2AsmSegmentSpecifier
{
	unsigned int _terminal_id;
	int _segment_relative_offset;
	std::string _segment;

	B2AsmSegmentSpecifier(unsigned int terminal_id, int segment_relative_offset, const std::string &segment) :
		_terminal_id(terminal_id), _segment_relative_offset(segment_relative_offset), _segment(segment) { };

	struct GlobalSortPredicate
	{
		unsigned int operator() (B2AsmSegmentSpecifier const &a, B2AsmSegmentSpecifier const &b) const
		{
			return (a._segment.size() > b._segment.size());
		};
	};

	static void global_sort(std::vector<B2AsmSegmentSpecifier> &segment_specifier_vec)
	{
		std::sort(segment_specifier_vec.begin(), segment_specifier_vec.end(), GlobalSortPredicate());
	};
};


void B2TerminalAssembler::create_pile()
{
	std::vector<B2AsmSegmentSpecifier> piling_sequence;
	for(B2HashMap<unsigned int, B2MgTTerminal>::const_iterator terminal_it = _mgt_terminals.begin(); terminal_it != _mgt_terminals.end(); ++terminal_it)
	{
		for(B2MgTTerminal::const_iterator segment_it = terminal_it->second.begin(); segment_it != terminal_it->second.end(); ++segment_it)
		{
			piling_sequence.push_back(B2AsmSegmentSpecifier(terminal_it->first, segment_it->first, segment_it->second));
		};
	};

	B2AsmSegmentSpecifier::global_sort(piling_sequence);

	for(std::vector<B2AsmSegmentSpecifier>::const_iterator specifier_it = piling_sequence.begin(); specifier_it != piling_sequence.end(); ++specifier_it)
	{
		const B2AsmSegmentSpecifier &segment_specifier = *specifier_it;
		unsigned int offset_in_pile = _segment_pile.find(segment_specifier._segment);
		if(offset_in_pile == std::string::npos)
		{
			offset_in_pile = _segment_pile.size();
			_segment_pile += segment_specifier._segment;
		};
		_segment_vecs[segment_specifier._terminal_id].push_back(B2SPSegmentMatch(segment_specifier._segment_relative_offset, offset_in_pile, segment_specifier._segment.size()));
	};
};


void B2TerminalAssembler::create_terminals_vec()
{
	unsigned int segment_count = 0;
	for(B2HashMap<unsigned int, std::vector<B2SPSegmentMatch> >::const_iterator seg_vec_it = _segment_vecs.begin(); seg_vec_it != _segment_vecs.end(); ++seg_vec_it)
	{
		B2HashMap<unsigned int, B2MgTTerminal>::const_iterator find_it = _mgt_terminals.find(seg_vec_it->first);
		if(find_it != _mgt_terminals.end())
		{
			const B2MgTTerminal &mgt_terminal = find_it->second;
			_terminals_vec.push_back(B2SPTerminal(mgt_terminal.str_instance_id(), segment_count, seg_vec_it->second.size()));
			segment_count += seg_vec_it->second.size();
		}
		else
		{
			//THROW
		};
	};
};


