
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


void B2MgTByteChoicesMap::add_str_instance(unsigned int total_str_instance_count, unsigned int preserve_instance_id, unsigned char byte)
{
	if(_total_str_instance_count == 0)
	{
		_total_str_instance_count = total_str_instance_count;
		_cavities_count = total_str_instance_count;
	}
	else if(_total_str_instance_count != total_str_instance_count)
	{
		// THROW
	};

	B2MgTByteChoicesMap::iterator find_it = find(byte);
	if(find_it != end())
	{
		B2MgTStrPurgeMap &str_purge_map = find_it->second;
		str_purge_map.erase(preserve_instance_id);
	}
	else
	{
		B2MgTStrPurgeMap str_purge_map(_total_str_instance_count);
		str_purge_map.erase(preserve_instance_id);
		(*this)[byte] = str_purge_map;
	};
	--_cavities_count;
	_fallback_purge_map[preserve_instance_id];
};


void B2MgTOffsetMap::apply_cavities(unsigned int str_instance_id, const B2MgTMotifStruct &motif_struct)
{
	int leftmost_offset = motif_struct.relative_offset();
	int rightmost_offset = leftmost_offset + motif_struct.str().size();
	for(iterator offset_it = begin(); offset_it != end(); ++offset_it)
	{
		int offset = offset_it->first;
		if((offset < leftmost_offset) || (rightmost_offset <= offset))
		{
			B2MgTByteChoicesMap &choices_map = offset_it->second;
			for(B2MgTByteChoicesMap::iterator choice_it = choices_map.begin(); choice_it != choices_map.end(); ++choice_it)
			{
				std::hash_map<unsigned int, unsigned int> &str_purge_map = choice_it->second;
				str_purge_map.erase(str_instance_id);
			};
		};
	};
};


B2MangledTrie::B2MangledTrie(const std::vector<B2TraceStruct> &traces_vec) : _trie_leftmost_offset(0), _trie_rightmost_offset(1)
{
	unsigned int str_instance_id = 0;
	for(std::vector<B2TraceStruct>::const_iterator trace_it = traces_vec.begin(); trace_it != traces_vec.end(); ++trace_it)
	{
		B2MgTMotifStruct motif_struct(*trace_it);
		const unsigned char *bytes = (unsigned char *)(motif_struct.str().c_str());
		int leftmost_offset = motif_struct.relative_offset();
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
		int rightmost_offset = motif_struct.relative_offset() + motif_struct.str().size();
		if(_trie_rightmost_offset < rightmost_offset)
		{
			_trie_rightmost_offset = rightmost_offset;
		};
		for(int byte_offset = 2; byte_offset < rightmost_offset; ++byte_offset)
		{
			B2MgTByteChoicesMap &choices_map = _offset_map[byte_offset];
			choices_map.add_str_instance(traces_vec.size(), str_instance_id, *(bytes++));
		};
		(*this)[str_instance_id++] = motif_struct;
	};

	for(int left_offset = -1, right_offset = 2; 
		(left_offset >= _trie_leftmost_offset) || (right_offset < _trie_rightmost_offset); 
		--left_offset, ++right_offset)
	{
		if(left_offset >= _trie_leftmost_offset)
		{
			_offsets_purge_vec.push_back(left_offset);
		};
		if(right_offset < _trie_rightmost_offset)
		{
			_offsets_purge_vec.push_back(right_offset);
		};
	};

	for(const_iterator str_instance_it = begin(); str_instance_it != end(); ++str_instance_it)
	{
		_offset_map.apply_cavities(str_instance_it->first, str_instance_it->second);
	};

	B2MgTByteChoicesMap &choices_map = _offset_map[-1];
	choices_map.calc_score(-1);
};
