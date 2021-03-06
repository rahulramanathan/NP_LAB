#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
struct DNSBase
{
	char name[50];
	char IP[50];
};
void main()
{
	//Decalarnig the database
	struct DNSBase Base1[3];
	strcpy(Base1[0].name,"www.google.co.in");
	strcpy(Base1[0].IP,"10.1.1.0");
	strcpy(Base1[1].name,"www.yahoo.co.in");
	strcpy(Base1[1].IP,"10.2.2.0");
	strcpy(Base1[2].name,"www.bing.co.in");
	strcpy(Base1[2].IP,"10.3.3.0");

	int s,r,recb,sntb,x,ns,a=0,i;
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
	//Connection established
	printf("\nSocket accepting.");
	recb=recv(ns,buff,sizeof(buff),0);
	if(recb==-1)
	{
	printf("\nMessage Receiving Failed");
	close(s);
	close(ns);
	exit(0);
	}
	printf("\nMessage Received: ");
	printf("%s", buff);
	printf("\n");
	//Perform DNS
	int flag=0;
	for(i=0;i<3;i++)
	{
		if(strcmp(Base1[i].name,buff)==0)//found
		{
			flag=1;
			break;
		}
	}
	if(flag==1)//map DNS
	{
		strcpy(buff,Base1[i].IP);
	}
	else//not found
	{
		strcpy(buff,"Not Found");
	}
	sntb=send(ns,buff,sizeof(buff),0);
	if(sntb==-1)
	{
	printf("\nMessage Sending Failed");
	close(s);
	close(ns);
	exit(0);
	}
	close(ns);
	close(s);
}