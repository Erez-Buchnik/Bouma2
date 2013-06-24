
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

#ifndef B2MgTOffsetMap___HPP
#define B2MgTOffsetMap___HPP

#include "B2MgTStrInstance.hpp"
#include "B2MgTByteChoicesMap.hpp"


class B2MgTOffsetMap : public B2HashMap<int, B2MgTByteChoicesMap>
{

public:
	void apply_cavities(unsigned int str_instance_id, const B2MgTStrInstance &str_instance);
};


#endif //B2MgTOffsetMap___HPP

