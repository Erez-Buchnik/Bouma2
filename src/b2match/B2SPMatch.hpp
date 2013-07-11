
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

#ifndef B2SPMatch___HPP
#define B2SPMatch___HPP


#include "B2SPTerminal.hpp"


enum B2SPTransitionWidth
{
	B2SP_2BIT_TRANSITION = 0,
	B2SP_4BIT_TRANSITION,
	B2SP_8BIT_TRANSITION,
	B2SP_16BIT_TRANSITION
};

class B2SPMatchBase
{

protected:
	unsigned int _transition_width : 2;
	unsigned int _segments_count : 7;
	unsigned int _terminals_count : 7;
	unsigned int _states_count : 16;

	void match(unsigned int *&match_list, const unsigned char *motif_position) const;
	const B2SPTerminal *single_terminal() const { return (B2SPTerminal *)(this + 1); };
	const B2SPSegmentMatch *segments_vec(const B2SPTerminal *terminals_vec) const { return (B2SPSegmentMatch *)(terminals_vec + _terminals_count); };
	const B2SPSegmentPile *segment_pile(const B2SPSegmentMatch *segments_vec) const { return (B2SPSegmentPile *)(segments_vec + _segments_count); };
	void match_single_terminal(unsigned int *&match_list, const unsigned char *motif_position) const
	{
		const B2SPTerminal *terminal = single_terminal();
		const B2SPSegmentMatch *segments = segments_vec(terminal);
		const B2SPSegmentPile *seg_pile = segment_pile(segments);
		terminal->match(match_list, motif_position, segments, *seg_pile);
	};
};

template <class StateType> class B2SPMatch : public B2SPMatchBase
{

public:
	const StateType *states_vec() const { return (StateType *)(this + 1); };
	const B2SPTerminal *terminals_vec(const StateType *states_vec) const { return (B2SPTerminal *)(states_vec + _states_count); };
	StateType *states_vec() { return (StateType *)(this + 1); };
	B2SPTerminal *terminals_vec(const StateType *states_vec) { return (B2SPTerminal *)(states_vec + _states_count); };
	void match(unsigned int *&match_list, const unsigned char *motif_position) const
	{
		const StateType *states = states_vec();
		unsigned int state_id = 0;
		while(state_id < _states_count)
		{
			state_id = states[state_id].transition(motif_position, state_id);
		};
		unsigned int terminal_id = state_id - _states_count;
		if(state_id < _terminals_count)
		{
			const B2SPTerminal *terminals = terminals_vec(states);
			const B2SPSegmentMatch *segments = segments_vec(terminals);
			const B2SPSegmentPile *seg_pile = segment_pile(segments);
			terminals[terminal_id].match(match_list, motif_position, segments, *seg_pile);
		};
	};

	void* operator new(size_t size, void *ptr) { return ptr; };
	void operator delete(void *inst, void *ptr) { };

};

#endif //B2SPMatch___HPP

