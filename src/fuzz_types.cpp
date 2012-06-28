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
      cout << "Length: " << fuzzcase.length() << endl;
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
  int val;
  string command = "cp " + file_fuzz + " " + file_fuzz + ".bak";
  system(command.c_str());

  string line;
  ifstream f(file_fuzz.c_str());
  while(f.good())
  {
    getline(f, line);
    file_to_fuzz.append(line);
  }
  f.close();

  for(;;)
  {
    construct_fuzz_case();
    ofstream f(file_fuzz.c_str(), ios::trunc);
    f << fuzzcase;
    f.close();
    crash = p_dbg();
    if(crash == 1)
    {
      command = "cp " + file_fuzz + " " + file_fuzz + ".CRASH";
      system(command.c_str());
      cout << "\nCrash with: " << file_fuzz << ".CRASH" << endl;
      break;
    }
    else if(val == 2)
    {
      break;
    }
  }
  command = "mv " + file_fuzz + ".bak " + file_fuzz;
  system(command.c_str());
  return crash;
}

int fuzz::client_socket()
{
  cout << "Client socket.\n\n";
  cout << "[*] Starting server...\n";
  int sock, client, cpid;
  socklen_t clilen;
  struct sockaddr_in server_addr, cli_addr;

  if((cpid = fork()) == 0)
  {
    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
      cout << "ERROR: socket().\n";

    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
      cout << "ERROR: bind().\n";

    listen(sock, 5);
    clilen = sizeof(cli_addr);
    client = accept(sock, (struct sockaddr *) &cli_addr, &clilen);

    if (client < 0)
      cout << "ERROR: accept().\n";

    do
    {
      construct_fuzz_case();
      istringstream temp;
      string temp1;
      temp.str(packet_gen);
      while(getline(temp, temp1, ';'))
      {
        temp1.append("\n");
        write(client, temp1.c_str(), temp1.length()); // race condition?
      }
    } while(crash != 1); // signal handler has not triggered
    close(client);
    close(sock);
    cout << "\nCrash with: " << packet_gen << endl;
    cout << "Length: " << packet_gen.length() << endl;
  }
  else
  {
    if(p_dbg() == 1)
      kill(cpid, SIGUSR1);
    else
      kill(cpid, SIGUSR2);
  }
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
    cout << "\nCrash with: " << packet_gen << endl;
    cout << "Length: " << packet_gen.length() << endl;
    close(sock);
  }
  else
  {
    if(p_dbg() == 1)
    {
      kill(cpid, SIGUSR1);
    }
    else
      kill(cpid, SIGUSR2);
  }
}


