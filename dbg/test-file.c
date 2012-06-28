#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  FILE *f;
  f = fopen(argv[1], "r");
  char buf[10], buffer[10];

  while(fgets(buf, 255, f) != NULL)
  {
    strcpy(buffer, buf);
    printf("%s\n", buffer);
  }
  return 0;
}
