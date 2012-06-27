/*
 *   Shiva - The Destroyer, src/generator.c
 *   (C) 2012 Justin Barrick
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 1, or (at your option)
 *   any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include "../include/fuzz_class.h"

int fuzz::construct_fuzz_case(int index)
{
  istringstream temp;
  string temp1, temp2;
  int i = 0;

  fuzzcase = "";

  if(type == "cli")                         // need to make this work with execv... string array issues.
    temp.str(arguments.c_str());  // bug, assign
  else if(type == "socket_srv")
    temp.str(packet.c_str());

  while(getline(temp, temp1, '|'))
  {
    if(i == 1)
    {
      gen_fuzzcase();
      temp2 = temp2 + raw_fuzzcase;
      i = 0;
    }
    else
    {
      temp2 = temp2 + temp1;
      i = 1;
    }
  }
  fuzzcase = temp2;
}

void fuzz::gen_fuzzcase()
{
  raw_fuzzcase = raw_fuzzcase + "A";
}

