/*
 *   Shiva - The Destroyer, src/main.c
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

#include "../include/includes.h"
#include "../include/fuzzer.h"

int main(int argc, char *argv[])
{
  if(argc != 2)
  {
    cout << "Usage: " << argv[1] << " <config file>\n";
    return 1;
  }
  cout << "Beginning fuzz testing using " << argv[1] << ":\n\n";
  fuzzer(argv[1]);
  return 0;
}
