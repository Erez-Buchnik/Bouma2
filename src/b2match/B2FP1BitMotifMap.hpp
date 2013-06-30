
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

#ifndef B2FP1BitMotifMap___HPP
#define B2FP1BitMotifMap___HPP


class B2FP1BitMotifMap
{
	unsigned int _map[2048];

	unsigned int match(unsigned short motif) const
	{
		unsigned int div = motif / 32;
		unsigned int mod = motif % 32;
		return ((_map[div] >> mod) & 1);
	};
};


#endif //B2FP1BitMotifMap___HPP

