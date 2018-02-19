#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
struct Bank
{	
	char username[50];
	char password[50];//stored in encrypted format
	float balance;
};
char * decode(char *str)
{

}
void main()
{
	struct Bank b1[3];
	strcpy(b1[0].username,"Samar");
	strcpy(b1[1].username,"Sarthake");
	strcpy(b1[2].username,"Rahul");
	strcpy(b1[0].password,"pwwq");//mttn
	strcpy(b1[1].password,"pdqdv");//manas
	strcpy(b1[2].password,"srvw");//post
	b1[0].balance=1000;
	b1[1].balance=5000;
	b1[2].balance=19000;
	int s,r,recb,sntb,x,ns,a=0,i;
	printf("INPUT port number: ");
	scanf("%d", &x);
	socklen_t len;
	struct sockaddr_in server,client;
	char buff[50],usr[50],pass[50];
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
	ns=accept(s,(struct sockaddr*)&client, &len);//client
	if(ns==-1)
	{
		close(s);
		exit(0);
	}

	printf("\nSocket accepting\nReading username");
	recb=recv(ns,buff,sizeof(buff),0);//receive from client
	strcpy(usr,buff);
	printf("\nReading password");	
	recb=recv(ns,buff,sizeof(buff),0);
	strcpy(pass,buff);
	for(i=0;i<3;i++)
	{
		if((strcmp(b1[i].username,usr)==0)&&(strcmp(b1[i].password,pass)==0))//found
		{
			x=1;
			break;			
		}
	}
	if(x==1)
	{
		printf("Valid\nBalance = %f",b1[i].balance);
		strcpy(buff,"1");
	}
	else
	{
		printf("Invalid\n");
		strcpy(buff,"0");
	}
	sntb=send(ns,buff,sizeof(buff),0);
	close(ns);
	close(s);
}