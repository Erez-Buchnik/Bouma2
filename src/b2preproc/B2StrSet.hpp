
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

#ifndef B2StrSet___HPP
#define B2StrSet___HPP


#include "B2PreprocDefs.hpp"


class B2Str : public std::string
{
protected:
	unsigned int _id;

public:
	unsigned int id() const { return _id; };

public:
	B2Str() { };
	B2Str(unsigned int id, unsigned char *bytes, unsigned int length);
};


class B2StrStruct : public B2Str
{
	std::vector<unsigned int> _duplicate_ids;

public:
	B2StrStruct(const B2Str &str) : B2Str(str) { };
	B2StrStruct() { };
	void duplicate_id(const B2Str &str) { _duplicate_ids.push_back(str.id()); };
	const std::vector<unsigned int> &duplicate_ids_vec() const { return _duplicate_ids; };
	bool operator < (const B2StrStruct &other) const { return _id < other._id; };
};


class B2StrSet : public B2HashMap<std::string, B2StrStruct>
{

public:
	void add_str(const B2Str &str);
};

#endif //B2StrSet___HPP

