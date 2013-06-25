
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

#ifndef B2MangledTrie___HPP
#define B2MangledTrie___HPP

#include "B2MgTOffsetMap.hpp"
#include "B2MgTStrPurgeMap.hpp"
#include "B2MgTStateMachine.hpp"


class B2MangledTrie : public B2HashMap<unsigned int, B2MgTStrInstance>
{
	int _trie_leftmost_offset;
	int _trie_rightmost_offset;

	std::vector<int> _left_offsets_vec;
	std::vector<int> _right_offsets_vec;

	B2MgTOffsetMap _offset_map;
	B2MgTStrPurgeMap _aggregate_purge_map;

	B2MgTStateMachine *_mgt_state_machine;

	double proximity(int offset) const;
	void apply_purge_map(int offset, const B2MgTStrPurgeMap &purge_map, std::vector<B2MgTTransitional> &transitionals);
	void partition_purge_maps(B2MgTStrPurgeMap &left_only, B2MgTStrPurgeMap &right_only) const;

public:
	B2MangledTrie(const B2StrSet &str_set, const B2TraceStruct &trace_struct);
	B2MangledTrie(const B2StrSet &str_set, const std::vector<B2TraceStruct> &traces_vec);
	double full_coverage_score(const std::vector<int> &offsets_vec, int &best_offset);
	double partial_coverage_score(const std::vector<int> &offsets_vec, int &best_offset);
	int select_purge_offset();
	unsigned int purge(int offset);
	const B2MgTStateMachine &state_machine() const { return *_mgt_state_machine; };
	unsigned int build();
};

#endif //B2MangledTrie___HPP

