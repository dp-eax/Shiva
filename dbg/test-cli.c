#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  char buf[10];
  strcpy(buf, argv[1]);
  printf("%s\n",buf);
  return 0;
}
