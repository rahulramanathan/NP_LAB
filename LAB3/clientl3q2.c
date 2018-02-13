#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<sys/stat.h>
void main()
{
	int s,r,recb,sntb,x;
	int sa;
	socklen_t len;

	printf("INPUT port number: ");

	scanf("%d", &x);
	struct sockaddr_in server,client;
	char buff[100];
	s=socket(AF_INET,SOCK_DGRAM,0);
	if(s==-1)
	{
		printf("\nSocket creation error");
		exit(0);
	}

	printf("\nSocket created\n");
	server.sin_family=AF_INET;
	server.sin_port=htons(x);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	sa=sizeof(server);
	len=sizeof(server);

	while(1)
	{	
		//read from terminal
		printf("\nEnter a word\nEnter halt to exit\n");
		scanf("%s",buff);
		//send word to client		
		sntb=sendto(s,buff,sizeof(buff),0,(struct sockaddr *)&server,len);
		if(strcmp(buff,"halt")==0)
		{//exit condition
			close(s);
			break;
		}
	}	
}