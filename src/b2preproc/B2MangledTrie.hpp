
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

class B2MgTReshuffleMap;


class B2MangledTrie : public B2HashMap<unsigned int, B2MgTStrInstance>
{
	int _trie_leftmost_offset;
	int _trie_rightmost_offset;

	std::vector<int> _left_offsets_vec;
	std::vector<int> _right_offsets_vec;

	B2MgTOffsetMap _offset_map;
	B2MgTStrPurgeMap _aggregate_purge_map;

	B2MgTStateMachine *_mgt_state_machine;
	B2MgTStateMachine *_delegated_mgt_state_machine;

	double proximity(int offset) const;
	void apply_purge_map(const B2MgTStrPurgeMap &purge_map);
	void apply_purge_map(int offset, const B2MgTStrPurgeMap &purge_map, B2MgTState &mgt_state);
	void partition_purge_maps(B2MgTStrPurgeMap &left_only, B2MgTStrPurgeMap &right_only) const;
	void init_single_str_trie(const B2StrSet &str_set, const B2TraceStruct &trace_struct);

public:
	B2MangledTrie(const B2StrSet &str_set, const std::vector<B2TraceStruct> &traces_vec);
	double full_coverage_score(const std::vector<int> &offsets_vec, int &best_offset);
	double partial_coverage_score(const std::vector<int> &offsets_vec, int &best_offset);
	int select_purge_offset();
	void get_valid_bytes(int offset, B2HashMap<unsigned char, unsigned int> &valid_bytes) const;
	unsigned int purge(int offset);
	const B2MgTStateMachine &state_machine() const { return *_mgt_state_machine; };
	unsigned int build_pivot();
	unsigned int build();
	void reshuffle_state_machine();
	B2MgTStateMachine *delegate_state_machine()
	{
		_delegated_mgt_state_machine = _mgt_state_machine;
		//_mgt_state_machine = NULL;
		return _delegated_mgt_state_machine;
	};
};

#endif //B2MangledTrie___HPP

