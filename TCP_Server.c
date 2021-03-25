//Tcpserver.c

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#define MYPORT 9843 /*The port users will be connecting to*/
void readstring(int,char *);
int main(int C, char *V[] )
{
int listensocket,connectionsocket,retbind;
struct sockaddr_in
serveraddress,cliaddr;
socklen_t len;
char buf[100],databuf[1024];
listensocket = socket(AF_INET, SOCK_STREAM, 0 );
if (listensocket < 0 )
{
perror("socket" );
exit(1);
}
memset(&serveraddress, 0, sizeof(serveraddress) );
serveraddress.sin_family = AF_INET;
serveraddress.sin_port = htons(MYPORT);/*PORT NO*/
serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);/*ADDRESS*/
retbind=bind(listensocket,(struct sockaddr*)&serveraddress,
sizeof(serveraddress));
/*Check the return value of bind for error*/
if(-1==retbind)
{
perror("BIND ERROR\n");
exit(1);
}
listen(listensocket,5);
/*Beginning of the Main Server Processing Loop*/
for (;;)
{
printf("Server:I am waiting-----Start of Main Loop\n");
len=sizeof(cliaddr);
connectionsocket=accept(listensocket,
(struct sockaddr*)&cliaddr,&len);
if (connectionsocket < 0)
{
if (errno == EINTR)
printf("Interrupted system call ??");
continue;
}
printf("Connection from %s\n",
inet_ntop(AF_INET,&cliaddr.sin_addr,buf,sizeof(buf)));
readstring(connectionsocket , databuf);
close(connectionsocket);
printf("Finished Serving One Client\n");
}
}

void readstring(
int connectionsocket, /*Socket Descriptor*/
char *fname) /*Array , to be populated by the string from client*/
{
int pointer=0,n;
int len=0,a,b;
char rev[50],temp[50],temp1[50];
int k,i;
while ((n=read(connectionsocket,(fname + pointer),1024))>0)
{
pointer=pointer+n;
}
fname[pointer]='\0';
printf("enter the string\n");
printf("Server :Received %s\n " ,fname);
k=strlen(fname);
a=0;
for(i=k-1;i>=0;i--)
temp[a++]=fname[i];
temp[a]='\0';
printf("\nrev is %s\n", temp);
}
  
