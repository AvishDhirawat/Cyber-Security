
//Tcpclient.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#define MAXBUFFER 1024
void sendstring(int , char *);
int main( int C, char *V[] )
{
int sd,fd;
char c;
struct sockaddr_in serveraddress;
char text[100];
int i=0;
sd = socket( AF_INET, SOCK_STREAM, 0 );
if( sd < 0 ) {
perror( "socket" );
exit( 1 );
}
if (V[1] == NULL ) {
printf ("PL specfiy the server's IP Address \n");
exit(0);
}
if (V[2] == NULL ) {
printf ("PL specify the server's Port No \n");
exit(0);
}
memset( &serveraddress, 0, sizeof(serveraddress) );
serveraddress.sin_family = AF_INET;
serveraddress.sin_port = htons(atoi(V[2]));//PORT NO
serveraddress.sin_addr.s_addr = inet_addr(V[1]);//ADDRESS
if (connect(sd,(struct sockaddr*)&serveraddress,
sizeof(serveraddress))<0)
{
printf("Cannot Connect to server");
exit(1);
}
printf("enter sentence to end enter #");
while(1)
{
c=getchar();
if(c=='#')
break;
text[i++]=c;
}
text[i]='\0';
sendstring(sd,text);
close(sd);
return 0;
}
void sendstring(
int sd, /*Socket Descriptor*/
char *fname) /*Array Containing the string */
{ int n , byteswritten=0 , written ;
char buffer[MAXBUFFER];
strcpy(buffer , fname);
n=strlen(buffer);
while (byteswritten<n)
{
written=write(sd , buffer+byteswritten,(n-byteswritten));
byteswritten+=written;

}
printf("String : %s sent to server \n",buffer);
}
