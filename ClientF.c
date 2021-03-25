/*FTP Client*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>


/*for getting file size using stat()*/
#include<sys/stat.h>

/*for sendfile()*/
#include<sys/sendfile.h>

/*for O_RDONLY*/
#include<fcntl.h>
#define MAXLINE 100

int main(int argc,char *argv[])
{
  struct sockaddr_in server;
  struct stat obj;
  char line[MAXLINE],buf[100];
  int sock;
  int choice;
  char command[5], filename[20], *f;
  int k, size, status;
  int filehandle;

  sock = socket(AF_INET, SOCK_STREAM, 0);

  if(sock == -1)
  {
      printf("socket creation failed");
      exit(1);
  }


  server.sin_family = AF_INET;
  server.sin_port = htons(atoi(argv[2]));//PORT NO
  server.sin_addr.s_addr = inet_addr(argv[1]);//ADDRESS
  printf("Client Starting service\n");
  k = connect(sock,(struct sockaddr*)&server, sizeof(server));
  if(k == -1)
  {
      printf("Connect Error\n");
      exit(1);
  }
  int i = 1;
  while(1)
  {
    //printf("Enter filename to put to server: ");
    //scanf("%s", filename);
    if(argc==4)
    {
    strcpy(filename,argv[3]);
	filehandle = open(filename, O_RDONLY);
    if(filehandle == -1)
    {
        printf("No such file on the local directory\n\n");
        break;
    }
    strcpy(buf, "put ");

	strcat(buf, filename);
	//printf("FIle is  %s\n",buf);
	send(sock, buf, 100, 0);
	stat(filename, &obj);
	size = obj.st_size;
	send(sock, &size, sizeof(int), 0);
	sendfile(sock, filehandle, NULL, size);
	recv(sock, &status, sizeof(int), 0);
	if(status)
	{
		printf("File stored successfully\n");
	}

	else
	{
		printf("File failed to be stored to remote machine\n");
	}
   }

   else
   {

	   	printf("\n output at the client\n");
	   	recv(sock, buf, 100, 0);
      	sscanf(buf, "%s", filename);
      	printf("file name is %s ",filename);
		int c = 0, len;
	  	char *f;
	  	recv(sock, &size, sizeof(int), 0);
	  	i = 1;
	  	//while(1)
	    //{
	    	filehandle = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0666);
	    	if(filehandle == -1)
			{
				sprintf(filename + strlen(filename), "%d", i);
			}
	    //	else
			//	break;
	//    }
	  	f = malloc(size);
	  	recv(sock, f, size, 0);
	  	c = write(filehandle, f, size);
	  	close(filehandle);
	  	send(sock, &c, sizeof(int), 0);
   }
}
}
