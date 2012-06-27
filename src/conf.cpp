/*
 *   Shiva - The Destroyer, src/conf.c
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
#include <libconfig.h++>

using namespace libconfig;

string lookup_str(Config *cfg, char *key, string save)   // looks up key from config file
{
  try
  {
    save = (const char *)cfg->lookup(key);
    return save;
  }
  catch(const SettingNotFoundException &nfex)
  {
    cout << "'" << key << "' not found. Quitting.\n";
    exit(1);
  }
}

int lookup_int(Config *cfg, char *key, int save)   // looks up key from config file
{
  try
  {
    save = cfg->lookup(key);
    return save;
  }
  catch(const SettingNotFoundException &nfex)
  {
    cout << "'" << key << "' not found. Quitting.\n";
    exit(1);
  }
}

void fuzz::parse_config()  // parse config using libconfig
{
  Config cfg;
  try
  {
    cfg.readFile(conf.c_str());
  }
  catch(const FileIOException &fioex)
  {
    cout << "I/O error while reading file." << endl;
    exit(1);
  }
  catch(const ParseException &pex)
  {
    cout << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError() << endl;
    exit(1);
  }

  char key[1024];
  strcpy(key, "type");
  type = lookup_str(&cfg, key, type);
  strcpy(key, "filename");
  filename = lookup_str(&cfg, key, filename);
  strcpy(key, "arguments");
  arguments = lookup_str(&cfg, key, arguments);

  if(type == "sock_srv")
  {
    strcpy(key, "ip");
    ip = lookup_str(&cfg, (char *)"ip", ip);
    strcpy(key, "port");
    port = lookup_int(&cfg, (char *)"port", port);
    strcpy(key, "packet");
    packet = lookup_str(&cfg, (char *)"packet", packet);
  }
}

