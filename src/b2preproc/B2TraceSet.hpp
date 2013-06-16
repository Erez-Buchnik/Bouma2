
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

#ifndef B2TraceSet___HPP
#define B2TraceSet___HPP

#include "B2StrSet.hpp"


typedef unsigned int B2Trace; // Actually, this is a 2-byte number

class B2TraceName
{
	static const char _hex_digit[16];
	char _name[5];

public:
	B2TraceName(B2Trace trace);
	const char *name() const { return _name; };
};

class B2TraceStruct
{
	std::string _str;
	unsigned int _offset;

public:
	B2TraceStruct() : _str(""), _offset(0) { };
	B2TraceStruct(const std::string str, unsigned int offset);
	const std::string &str() const { return _str; };
	unsigned int offset() const { return _offset; };
	B2Trace trace_val() const
	{
		const char *bytes = _str.c_str();
		// Explicit cast to avoid confusion:
		return *(unsigned short *)&(bytes[_offset]);
	};
	const std::string chars() const { return _str.substr(_offset, 2); };
	unsigned int parity() const { return (_offset & 0x01); };
	bool operator != (const B2TraceStruct &other) const { return (_str != other._str) || (_offset != other._offset); };
};


class B2TraceSet : public B2HashMap<B2Trace, std::vector<B2TraceStruct> >
{
	unsigned int _str_count;
	void add_trace(const B2TraceStruct &trace_struct);

protected:
	B2HashMap<B2Trace, unsigned int> _trace_vals;
	B2TraceSet() : _str_count(0) { };

public:
	B2TraceSet(const B2StrSet &str_set);
	unsigned int str_count() const { return _str_count; };
	const B2HashMap<B2Trace, unsigned int> &trace_vals() const { return _trace_vals; };
};

class B2TraceCoeffs
{

protected:
	B2HashMap<B2Trace, double> _coeffs;

public:
	double operator [] (B2Trace trace) const { return 1.0; };
};


#endif //B2TraceSet___HPP

