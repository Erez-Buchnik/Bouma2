
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

#include "B2MangledTrie.hpp"
#include "B2MgTStateMachine.hpp"


B2MangledTrie::B2MangledTrie(const B2StrSet &str_set, const B2TraceStruct &trace_struct) : _trie_leftmost_offset(0), _trie_rightmost_offset(1), _mgt_state_machine(new B2MgTStateMachine)
{
	B2StrSet::const_iterator find_it = str_set.find(trace_struct.str());
	if(find_it != str_set.end())
	{
		B2MgTStrInstance str_instance(find_it->second.id(), trace_struct);
		(*this)[0] = str_instance;
		_mgt_state_machine->new_terminal(str_instance);
	}
	else
	{
		b2_preproc_error(B2_PREPROC_ERROR_PATTERN_STR_NOT_FOUND);
	};
};

B2MangledTrie::B2MangledTrie(const B2StrSet &str_set, const std::vector<B2TraceStruct> &traces_vec) : _trie_leftmost_offset(0), _trie_rightmost_offset(1), _mgt_state_machine(new B2MgTStateMachine)
{
	unsigned int str_instance_id = 0;
	for(std::vector<B2TraceStruct>::const_iterator trace_it = traces_vec.begin(); trace_it != traces_vec.end(); ++trace_it)
	{
		B2StrSet::const_iterator find_it = str_set.find(trace_it->str());
		if(find_it != str_set.end())
		{
			B2MgTStrInstance str_instance(find_it->second.id(), *trace_it);
			const unsigned char *bytes = (unsigned char *)(str_instance.c_str());
			int leftmost_offset = str_instance.relative_offset();
			if(_trie_leftmost_offset > leftmost_offset)
			{
				_trie_leftmost_offset = leftmost_offset;
			};
			for(int byte_offset = leftmost_offset; byte_offset < 0; ++byte_offset)
			{
				B2MgTByteChoicesMap &choices_map = _offset_map[byte_offset];
				choices_map.add_str_instance(traces_vec.size(), str_instance_id, *(bytes++));
			};
			bytes += 2;
			int rightmost_offset = str_instance.relative_offset() + str_instance.size();
			if(_trie_rightmost_offset < rightmost_offset)
			{
				_trie_rightmost_offset = rightmost_offset;
			};
			for(int byte_offset = 2; byte_offset < rightmost_offset; ++byte_offset)
			{
				B2MgTByteChoicesMap &choices_map = _offset_map[byte_offset];
				choices_map.add_str_instance(traces_vec.size(), str_instance_id, *(bytes++));
			};
			(*this)[str_instance_id++] = str_instance;
		}
		else
		{
			b2_preproc_error(B2_PREPROC_ERROR_BAD_TRACE_SET);
		};
	};

	for(int left_offset = -1; left_offset >= _trie_leftmost_offset; --left_offset)
	{
		_left_offsets_vec.push_back(left_offset);
	};

	for(int right_offset = 2; right_offset < _trie_rightmost_offset; ++right_offset)
	{
		_right_offsets_vec.push_back(right_offset);
	};

	for(const_iterator str_instance_it = begin(); str_instance_it != end(); ++str_instance_it)
	{
		_offset_map.apply_cavities(str_instance_it->first, str_instance_it->second);
	};
};


double B2MangledTrie::full_coverage_score(const std::vector<int> &offsets_vec, int &best_offset)
{
	double score = 0;
	double best_score = 0;
	for(std::vector<int>::const_iterator offset_it = offsets_vec.begin(); offset_it != offsets_vec.end(); ++offset_it)
	{
		B2MgTOffsetMap::iterator find_it = _offset_map.find(*offset_it);
		if(find_it != _offset_map.end())
		{
			B2MgTByteChoicesMap &choices_map = find_it->second;
			if(_aggregate_purge_map.size() > 0)
			{
				choices_map.clean_purged(_aggregate_purge_map);
			};
			if(choices_map.coverage() == 1)
			{
				score = choices_map.diversity();
				if(best_score < score)
				{
					best_score = score;
					best_offset = *offset_it;
					if(best_score == 1)
					{
						break;
					};
				};
			}
			else
			{
				break;
			};
		}
		else
		{
			b2_preproc_error(B2_PREPROC_ERROR_MGT_BAD_OFFSET_MAP);
		};
	};
	return best_score;
};


double B2MangledTrie::partial_coverage_score(const std::vector<int> &offsets_vec, int &best_offset)
{
	double score = 0;
	double best_score = 0;
	double prev_coverage = 0;
	double coverage_purge_factor = b2_preproc_config(B2_COVERAGE_PURGE_FACTOR);
	double diversity_purge_factor = b2_preproc_config(B2_DIVERSITY_PURGE_FACTOR);
	for(std::vector<int>::const_iterator offset_it = offsets_vec.begin(); offset_it != offsets_vec.end(); ++offset_it)
	{
		B2MgTOffsetMap::iterator find_it = _offset_map.find(*offset_it);
		if(find_it != _offset_map.end())
		{
			B2MgTByteChoicesMap &choices_map = find_it->second;
			if(_aggregate_purge_map.size() > 0)
			{
				choices_map.clean_purged(_aggregate_purge_map);
			};
			if((prev_coverage == 0) || (choices_map.coverage() == prev_coverage))
			{
				score = (diversity_purge_factor * choices_map.diversity()) + (coverage_purge_factor * choices_map.coverage());
				if(best_score < score)
				{
					best_score = score;
					best_offset = *offset_it;
				};
			}
			else
			{
				break;
			};
		}
		else
		{
			b2_preproc_error(B2_PREPROC_ERROR_MGT_BAD_OFFSET_MAP);
		};
	};
	return best_score;
};


int B2MangledTrie::select_purge_offset()
{
	int best_left_offset = 0;
	int best_right_offset = 0;
	double best_score = full_coverage_score(_left_offsets_vec, best_left_offset);
	if(best_score < full_coverage_score(_right_offsets_vec, best_right_offset))
	{
		return best_right_offset;
	}
	else if(best_score > 0)
	{
		return best_left_offset;
	}
	else
	{
		best_score = partial_coverage_score(_left_offsets_vec, best_left_offset);
		if(best_score < partial_coverage_score(_right_offsets_vec, best_right_offset))
		{
			return best_right_offset;
		}
		else if(best_score > 0)
		{
			return best_left_offset;
		}
		else
		{
			b2_preproc_error(B2_PREPROC_ERROR_MGT_INCONSISTENT_SCORE);
			return 0;
		};
	};
};


unsigned int B2MangledTrie::build()
{
	B2MgTStrPurgeMap left_only;
	B2MgTStrPurgeMap right_only;
	partition_purge_maps(left_only, right_only);
	if(left_only.size() + right_only.size() == size())
	{
		b2_preproc_diagnostic(B2_PREPROC_DIAG_ADDED_PIVOT);
	};
	int purge_offset = select_purge_offset();
	return purge(purge_offset);
};


unsigned int B2MangledTrie::purge(int offset)
{
	B2MgTOffsetMap::const_iterator find_it = _offset_map.find(offset);
	if(find_it != _offset_map.end())
	{
		B2MgTState &mgt_state = _mgt_state_machine->new_state(offset);
		const B2MgTByteChoicesMap &byte_choices_map = find_it->second;
		for(B2MgTByteChoicesMap::const_iterator byte_it = byte_choices_map.begin(); byte_it != byte_choices_map.end(); ++byte_it)
		{
			const B2MgTStrPurgeMap &byte_purge_map = byte_it->second;
			B2MangledTrie purged_copy = *this;
			purged_copy.apply_purge_map(offset, byte_purge_map, mgt_state.transitionals());
			if(purged_copy.size() > 1)
			{
				unsigned int next_state_id = purged_copy.build();
				mgt_state.add_transition(byte_it->first, next_state_id);
			}
			else if(purged_copy.size() == 1)
			{
				const B2MgTTerminal &new_terminal = _mgt_state_machine->new_terminal(purged_copy.begin()->second);
				mgt_state.add_transition(byte_it->first, new_terminal.id());
			};
		};
		const B2MgTStrPurgeMap &fallback_purge_map = byte_choices_map.fallback_purge_map();
		B2MangledTrie purged_copy = *this;
		purged_copy.apply_purge_map(offset, fallback_purge_map, mgt_state.transitionals());
		if(purged_copy.size() > 1)
		{
			unsigned int next_state_id = purged_copy.build();
			mgt_state.add_fallback_transition(next_state_id);
		};
		return mgt_state.id();
	}
	else
	{
		b2_preproc_error(B2_PREPROC_ERROR_MGT_OFFSET_NOT_FOUND);
	};
	return B2_MGT_STATE_INVALID_ID;
};


void B2MangledTrie::apply_purge_map(int offset, const B2MgTStrPurgeMap &purge_map, std::vector<B2MgTTransitional> &transitionals)
{
	_aggregate_purge_map.merge(purge_map);
	for(iterator str_inst_it = begin(); str_inst_it != end(); )
	{
		B2MgTStrPurgeMap::const_iterator find_it = _aggregate_purge_map.find(str_inst_it->first);
		if(find_it != _aggregate_purge_map.end())
		{
			B2_HASH_MAP_ERASE(*this, str_inst_it);
		}
		else
		{
			unsigned int bytes_left = str_inst_it->second.purge_at_offset(offset);
			if(bytes_left > 0)
			{
				++str_inst_it;
			}
			else
			{
				const B2MgTStrInstance &str_instance = str_inst_it->second;
				transitionals.push_back(B2MgTTransitional(str_instance.byte(offset), str_instance.str_id(), str_instance.relative_offset()));
				b2_preproc_diagnostic(B2_PREPROC_DIAG_ADDED_TRANSITIONAL);
				B2_HASH_MAP_ERASE(*this, str_inst_it);
			};
		};
	};
	if(offset < 0)
	{
		for(std::vector<int>::iterator offset_it = _left_offsets_vec.begin(); offset_it != _left_offsets_vec.end(); ++offset_it)
		{
			if(*offset_it == offset)
			{
				_left_offsets_vec.erase(offset_it);
				break;
			};
		};
	}
	else
	{
		for(std::vector<int>::iterator offset_it = _right_offsets_vec.begin(); offset_it != _right_offsets_vec.end(); ++offset_it)
		{
			if(*offset_it == offset)
			{
				_right_offsets_vec.erase(offset_it);
				break;
			};
		};
	};
	_offset_map.erase(offset);
};


double B2MangledTrie::proximity(int offset) const
{
	int radius = ((-_trie_leftmost_offset > (_trie_rightmost_offset - 2)) ? -_trie_leftmost_offset : (_trie_rightmost_offset - 2));
	if(offset >= 2)
	{
		double proximity = (double)(offset - 2) / (double)radius;
		proximity = 1 - proximity;
		return proximity;
	}
	else
	{
		double proximity = (double)(-offset - 1) / (double)radius;
		proximity = 1 - proximity;
		return proximity;
	};
};


void B2MangledTrie::partition_purge_maps(B2MgTStrPurgeMap &left_only, B2MgTStrPurgeMap &right_only) const
{
	left_only.clear();
	right_only.clear();
	for(const_iterator str_inst_it = begin(); str_inst_it != end(); ++str_inst_it)
	{
		if(str_inst_it->second.rightmost_byte_offset() < 0)
		{
			left_only[str_inst_it->first];
		}
		else if(str_inst_it->second.leftmost_byte_offset() >= 2)
		{
			right_only[str_inst_it->first];
		};
	};
};
