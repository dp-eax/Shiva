/*
 *   Shiva - The Destroyer, src/fuzzer.c
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

#include "../include/fuzzer.h"
#include "../include/fuzz_class.h"

int *crash_ptr;

void signal_handler(int signum)
{
  if(signum == SIGUSR1)
    *crash_ptr = 1;
  else
    *crash_ptr = 0;
}

void fuzzer(char *config_file)
{
  signal(SIGUSR1, signal_handler);  // set signal handler for crash
  signal(SIGUSR2, signal_handler);  // set signal handler for exit
  fuzz info;
  crash_ptr = &info.crash;
  info.conf = config_file;
  info.parse_config();

  cout << "Deployment method: ";
  if(!info.type.compare("cli"))
    info.cmdline();
  else if(!info.type.compare("file"))
    info.file();
  else if(!info.type.compare("sock_client"))
    info.client_socket();
  else if(!info.type.compare("sock_srv"))
    info.server_socket();
  else
    cout << "Unknown!\nAllowed methods:\n * 0: command line\n * 1: file\n * 2: socket client mode\n * 3 socket server mode\n\nQuitting!";
}
