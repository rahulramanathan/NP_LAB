#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
void main()
{
	int s,r,recb,sntb,x,ns,a=0,pid;
	printf("INPUT port number: ");
	scanf("%d", &x);
	socklen_t len;
	struct sockaddr_in server,client;
	char buff[50];
	s=socket(AF_INET,SOCK_STREAM,0);
	if(s==-1)
	{

		printf("\nSocket creation error.");
		exit(0);
	}

	printf("\nSocket created.");
	server.sin_family=AF_INET;
	server.sin_port=htons(x);
	server.sin_addr.s_addr=htonl(INADDR_ANY);

	r=bind(s,(struct sockaddr*)&server,sizeof(server));

	if(r==-1)
	{
		printf("\nBinding error.");
		exit(0);
	}

	printf("\nSocket binded.");
	r=listen(s,1);

	if(r==-1)
	{
		close(s);
		exit(0);
	}

	printf("\nSocket listening.");
	len=sizeof(client);
	ns=accept(s,(struct sockaddr*)&client, &len);
	if(ns==-1)
	{
		close(s);
		exit(0);
	}

	printf("\nSocket accepting\nStart Chatting\n");
	pid=fork();
	if(pid>0)//child for receiving
	{
		while(1)
		{
			recb=recv(ns,buff,sizeof(buff),0);
			printf("%s\n",buff);
			if(strcmp(buff,"BYE")==0||strcmp(buff,"bye")==0)
			{//exit condition
				printf("Terminating");
				close(ns);
				close(s);
				break;
			}
		}
	}
	else if(pid==0)//parent for sending
	{
		while(1)
		{
		scanf("%s",&buff);//Read from terminal
		if(strcmp(buff,"BYE")==0||strcmp(buff,"bye")==0)
		{//exit condition
			printf("Terminating");
			close(ns);
			close(s);
			break;
		}
		//send to client
		sntb=send(ns,buff,sizeof(buff),0);
		}
	}
}