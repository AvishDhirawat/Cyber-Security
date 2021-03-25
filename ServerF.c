#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include<sys/sendfile.h>
#include<ctype.h>
#define MAXLINE 100
#define SERV_PORT 9844
#define MAXBUFFER 1000

int main(int argc, char **argv)
{
	int k, i, maxi, maxfd, listenfd, connfd, sockfd;
	int nready, client[FD_SETSIZE];
	struct stat obj;
	ssize_t n;
	fd_set rset, wset, allset;
	char line[MAXLINE],buf[100], buf2[100];
	char command[5], filename[20];
	socklen_t clilen;
	int size, filehandle, status;
	struct sockaddr_in cliaddr, servaddr;
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd < 0 )
	{
		perror("socket" );
		exit(1);
	}
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	listen(listenfd,5);
	maxfd = listenfd; /* initialize */
	maxi = -1; /* index into client[] array */
	for (i = 0; i < FD_SETSIZE; i++)
	{
		client[i] = -1; /* -1 indicates available entry */
	}

	FD_ZERO(&rset);
	FD_ZERO(&wset);
	FD_SET(listenfd, &rset);
    FD_SET(listenfd, &wset);
	FD_SET(listenfd, &allset);

	for ( ; ; )
	{
		printf("Server:I am waiting-----Start of Main Loop\n");
		rset = allset; /* structure assignment */
		wset = allset;
		nready = select(maxfd+1, &rset, &wset, NULL, NULL);
		if (FD_ISSET(listenfd, &rset))
		{ /* new client connection */
			clilen = sizeof(cliaddr);
			connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
			#ifdef NOTDEF
			printf("new client: %s, port %d\n",inet_ntop(AF_INET, &cliaddr.sin_addr, buf, NULL),ntohs(cliaddr.sin_port));
			#endif
			for (i = 0; i < FD_SETSIZE; i++)
			if (client[i] < 0)
			{
				client[i] = connfd; /* save descriptor */
				break;
			}
			if (i == FD_SETSIZE)
			{
				printf("too many clients");
				exit(0);
			}
			FD_SET(connfd, &allset); /* add new descriptor to set */
			if (connfd > maxfd)
				maxfd = connfd; /* for select */

			if (i > maxi)
				maxi = i; /* max index in client[] array */
			if (--nready <= 0)
				continue; /* no more readable descriptors*/
		}
		for (i = 0; i <= maxi; i++)
		{ /* check all clients for data */
			if ( (sockfd = client[i]) < 0)
				continue;
			if (FD_ISSET(sockfd, &rset))
			{
				recv(sockfd, buf2, 100, 0);
      			sscanf(buf2, "%s", command);
      			printf("Hello %s\n",buf2);
				if(!strcmp(command, "put"))
     			{
	  				int c = 0, len;
	  				char *f;
	  				printf("Hello\n");
	  				sscanf(buf2+strlen(command), "%s", filename);
	 	 			recv(sockfd, &size, sizeof(int), 0);
	  				i = 1;
	  				while(1)
	    			{
	      				filehandle = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0666);
	      				if(filehandle == -1)
						{
		  					sprintf(filename + strlen(filename), "%d", i);
						}
	      				else
							break;
	    			}
	  				f = malloc(size);
	  				recv(sockfd, f, size, 0);
	  				c = write(filehandle, f, size);
	  				close(filehandle);
	  				send(sockfd, &c, sizeof(int), 0);
	  				close(sockfd);
					FD_CLR(sockfd, &allset);
					client[i] = -1;
        		}
        			if (--nready <= 0)
						break; /* no more readable descriptors*/
			}
			if (FD_ISSET(sockfd, &wset))
			{
				filehandle = open(filename, O_RDONLY);
    			if(filehandle == -1)
    			{
        			printf("No such file on the local directory\n\n");
        			break;
    			}
    			strcpy(buf2, filename);
				send(sockfd, buf2, 100, 0);
				stat(filename, &obj);
				size = obj.st_size;
				send(sockfd, &size, sizeof(int), 0);
				sendfile(sockfd, filehandle, NULL, size);
				recv(sockfd, &status, sizeof(int), 0);
				close(filehandle);
	  			close(sockfd);
				FD_CLR(sockfd, &allset);
				client[i] = -1;
				if(status)
				{
					printf("File stored successfully\n");
				}
				else
				{
					printf("File failed to be stored to remote machine\n");
				}
	  			if (--nready <= 0)
				break; /* no more readable descriptors*/
			}
        }
	}
}
