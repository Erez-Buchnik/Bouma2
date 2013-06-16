
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

#include "B2MotifSet.hpp"

typedef unsigned int B2MgTState;


class B2MgTMotifStruct
{
	std::string _str;
	std::string _purge_mask;
	int _relative_offset;

public:
	B2MgTMotifStruct() : _relative_offset(0) { };
	B2MgTMotifStruct(const B2TraceStruct &trace) : _str(trace.str()), _purge_mask(trace.str().size(), '+'), _relative_offset(-(int)trace.offset())
	{
		_purge_mask[trace.offset()] = '.';
		_purge_mask[trace.offset() + 1] = '.';
	};
	const std::string &str() const { return _str; };
	int relative_offset() const { return _relative_offset; };
};


class B2MgTStrPurgeMap : public std::hash_map<unsigned int, unsigned int>
{

public:
	B2MgTStrPurgeMap() { };
	B2MgTStrPurgeMap(unsigned int total_str_count)
	{
		for(unsigned int str_instance_id = 0; str_instance_id < total_str_count; ++str_instance_id)
		{
			(*this)[str_instance_id];
		};
	};
};


class B2MgTByteChoicesMap : public B2HashMap<unsigned char, B2MgTStrPurgeMap>
{
	unsigned int _total_str_instance_count;
	unsigned int _cavities_count;

	B2MgTStrPurgeMap _fallback_purge_map;

public:
	B2MgTByteChoicesMap() : _total_str_instance_count(0), _cavities_count(0) { };
	void add_str_instance(unsigned int total_str_instance_count, unsigned int preserve_instance_id, unsigned char byte);

	double calc_score(int relative_offset)
	{
		//////////////////////////
		double purge_potential = 0;
		for(const_iterator byte_it = begin(); byte_it != end(); ++byte_it)
		{
			purge_potential += (double)(byte_it->second.size());
		};
		purge_potential += (double)(256 - size()) * (double)(_fallback_purge_map.size());
		purge_potential /= (double)256;
		purge_potential /= (double)_total_str_instance_count;
		//////////////////////////
		double coverage = (double)(_total_str_instance_count - _cavities_count) / (double)_total_str_instance_count;
		//////////////////////////
		double score = (coverage * 0.9) + (purge_potential * 0.1);
		return score;
	};
};


class B2MgTOffsetMap : public B2HashMap<int, B2MgTByteChoicesMap>
{

public:
	void apply_cavities(unsigned int str_instance_id, const B2MgTMotifStruct &motif_struct);
};

class B2MangledTrie : public B2HashMap<unsigned int, B2MgTMotifStruct>
{
	int _trie_leftmost_offset;
	int _trie_rightmost_offset;

	std::vector<int> _offsets_purge_vec;

	B2MgTOffsetMap _offset_map;

public:
	B2MangledTrie(const std::vector<B2TraceStruct> &traces_vec);
};

#endif //B2MangledTrie___HPP

