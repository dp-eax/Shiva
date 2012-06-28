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

int fuzz::construct_fuzz_case()
{
  istringstream temp;
  string temp1, temp2;
  int i = 0;

  fuzzcase = "";

  if(type == "cli")                         // need to make this work with execv... string array issues.
    temp.str(arguments.c_str());  // bug, assign
  else if(type == "sock_srv" || type == "sock_client")
    temp.str(packet.c_str());
  else if(type == "file")
    temp.str(file_to_fuzz.c_str());

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
  if(type == "cli" || type == "file")
    fuzzcase = temp2;
  else if(type == "sock_srv" || type == "sock_client")
    packet_gen = temp2;
}

/*
  * Modes for data generation:
    * 0 - long strings
    * 1 - format strings
    * 2 - escape sequences
    * 3 - EOFs
    * 4 - null bytes
    * 5 - random binary data
  * --------------------------
*/

void fuzz::gen_fuzzcase()
{
  if(raw_fuzzcase.length() > 10000 && fuzzcase_mode == 0) // long strings
  {
    raw_fuzzcase = raw_fuzzcase + "A";
  }
  else if(/* && */fuzzcase_mode == 1) // format strings
  {
    fuzzcase_mode++;
  }
  else if(/* && */fuzzcase_mode == 2) // escape sequences
  {
    fuzzcase_mode++;
  }
  else if(/* && */fuzzcase_mode == 3) // EOFs
  {
    fuzzcase_mode++;
  }
  else if(/* && */fuzzcase_mode == 4) // null strings
  {
    fuzzcase_mode++;
  }
  else if(/* && */fuzzcase_mode == 5) // random binary data
  {
    fuzzcase_mode++;
  }

  // change data generation mode (see above for mode numbers)
  if(raw_fuzzcase.length() > 10000 && fuzzcase_mode == 0)
    fuzzcase_mode++;
  else if(/* && */fuzzcase_mode == 1)
    fuzzcase_mode++;
  else if(/* && */fuzzcase_mode == 2)
    fuzzcase_mode++;
  else if(/* && */fuzzcase_mode == 3)
    fuzzcase_mode++;
  else if(/* && */fuzzcase_mode == 4)
    fuzzcase_mode++;
  else if(/* && */fuzzcase_mode == 5)
    fuzzcase_mode++;
}

