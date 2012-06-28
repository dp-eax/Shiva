/*
 *   Shiva - The Destroyer, src/dbg.c
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

int fuzz::p_dbg()
{
  char *argument[1024], arg[1024][1024];
  int status, i=0;
  istringstream temp;
  pid_t cpid;
  siginfo_t siginfo;
  char *sig;
  string temp1;
  struct user_regs_struct regs;
  struct stat sb;
  if(!type.compare("cli"))
    temp.str(fuzzcase.c_str());
  else if(!type.compare("sock_srv") || !type.compare("sock_client") || !type.compare("file"))
    temp.str(arguments.c_str());

  strncpy(arg[i], filename.c_str(), 1024);
  argument[i] = arg[i];
  i++;

  while(getline(temp, temp1, ' '))
  {
    strncpy(arg[i], temp1.c_str(), 1024);
    argument[i] = arg[i];
    i++;
  }
  argument[i] = NULL;

  if(stat(filename.c_str(), &sb) != 0)
  {
    cout << "ERROR: " << filename << " does not exist!\n";
    exit(0);
  }

  if((cpid = fork()) == 0)
  {
    ptrace(PTRACE_TRACEME, 0, NULL, NULL);
    if(execv(filename.c_str(), argument) == -1)
    {
      cout << "ERROR: execv\n";
      exit(0);
    }
  }
  else
  {
    for(;;)
    {
      wait(&status);
      if(WIFEXITED(status))
        return 0;
      ptrace(PTRACE_GETSIGINFO, cpid, NULL, &siginfo);
      if(siginfo.si_signo == 11 || siginfo.si_signo == 6)
      {
        sig = strsignal(siginfo.si_signo);
        cout << "Signal: " << sig << endl;
        ptrace(PTRACE_GETREGS, cpid, NULL, &regs);
        cout << "EIP: 0x" << hex << regs.rip << ", EAX: 0x" << hex << regs.rax << ", EBX: 0x" << hex << regs.rbx << endl;
        return 1;
      }
      ptrace(PTRACE_CONT, cpid, NULL, NULL);
    }
    ptrace(PTRACE_DETACH, cpid, NULL, NULL);
  }
  return 0;
}
