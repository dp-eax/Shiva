/*
 *   Shiva - The Destroyer, include/structs.h
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

#ifndef STRUCTS_H
#define STRUCTS_H

#include "includes.h"

class fuzz
{
  public:
    string arguments;
    string filename;
    string conf;
    string ip;
    string packet;
    string packet_gen;
    string fuzzcase;
    string raw_fuzzcase;
    string type;
    string file_fuzz;
    string file_to_fuzz;

    int num_args;
    int mode;
    int packetno;
    int port;
    int crash;

    fuzz(); // initialize (I'm sure there's a better way to do this)

    int p_dbg(); // debugger

    void parse_config(); // configuration file parsing functions

    int cmdline(); // fuzz methods
    int file();
    int client_socket();
    int server_socket();

    int construct_fuzz_case(); // fuzz case generation
    void gen_fuzzcase();
};


#endif
