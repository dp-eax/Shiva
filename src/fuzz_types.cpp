/*
 *   Shiva - The Destroyer, src/fuzz_types.c
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
#include "../include/fuzzer.h"

int fuzz::cmdline()
{
  cout << "Command line.\n\n";
  int val;
  for(;;)
  {
    construct_fuzz_case();
    crash = p_dbg();
    if(crash == 1)
    {
      cout << "\nCrash with: " << fuzzcase << endl;
      break;
    }
    else if(val == 2)
    {
      break;
    }
  }
  return crash;
}

int fuzz::file()
{
  cout << "File.\n\n";
  return p_dbg();
}

int fuzz::client_socket()
{
  cout << "Client socket.\n\n";
  return p_dbg();
}

int fuzz::server_socket()
{
  cout << "Server socket.\n\n";
  int sock, bytes_recieved, cpid;
  char send_data[1024],recv_data[1024];
  struct hostent *host;
  struct sockaddr_in server_addr;

  if((cpid = fork()) == 0)
  {
    sleep(1);
    host = gethostbyname(ip.c_str());

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
      cout << "ERROR: socket().\n";
      exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr = *((struct in_addr *)host->h_addr);
    bzero(&(server_addr.sin_zero),8);

    if(connect(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
    {
      cout << "ERROR: connect().\n";
      exit(1);
    }

    do
    {
      construct_fuzz_case();
      istringstream temp;
      string temp1;
      temp.str(packet_gen);
      while(getline(temp, temp1, ';'))
      {
        temp1.append("\n");
        write(sock, temp1.c_str(), temp1.length()); // race condition?
      }
    } while(crash != 1); // signal handler has not triggered
  }
  else
  {
    if(p_dbg() == 1)
      kill(cpid, SIGUSR1);
    else
      kill(cpid, SIGUSR2);
  }
}


