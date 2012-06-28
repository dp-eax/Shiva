#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int read_vuln(int sock, char *buf)
{
  char buffer[10];
  bzero(buf, 10);
  read(sock, buf, 1024);
  strcpy(buffer, buf);
  printf("%s\n", buffer);
  return 0;
}

int main(int argc, char *argv[])
{
  int sock, bytes_recieved, port;
  char send_data[1024],recv_data[1024], buf[10];
  struct hostent *host;
  struct sockaddr_in server_addr;

  host = gethostbyname("127.0.0.1");

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    printf("ERROR: socket().\n");
    exit(1);
  }

  port = atoi(argv[1]);
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr = *((struct in_addr *)host->h_addr);
  bzero(&(server_addr.sin_zero),8);

  if(connect(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
  {
    printf("ERROR: connect().\n");
    exit(1);
  }

  for(;;)
  {
    read_vuln(sock, buf);
  }

  return 0;
}
