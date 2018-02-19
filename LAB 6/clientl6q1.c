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
int s,r,recb,sntb,x,amt;
printf("INPUT port number: ");
scanf("%d", &x);
struct sockaddr_in server;
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
server.sin_addr.s_addr=inet_addr("127.0.0.1");
r=connect(s,(struct sockaddr*)&server,sizeof(server));
if(r==-1)
{
printf("\nConnection error.");
exit(0);
}
printf("\nSocket connected.");
//program start
printf("\nEnter username : ");
scanf("%s",buff);
sntb=send(s,buff,sizeof(buff),0);
printf("\nEnter password : ");
scanf("%s",buff);
sntb=send(s,buff,sizeof(buff),0);
recb=recv(s,buff,sizeof(buff),0);
if(strcmp(buff,"0")==0)//user not found
{
	printf("\nUser not found\n");
	close(s);
	exit(0);
}
else
 { //display menu
	while(1)
	{
		printf("\nEnter 1 for debit\n2 for credit\n3 to view balance\n4 to exit\n");
		scanf("%s",buff);
		sntb=send(s,buff,sizeof(buff),0);//send choice to server
		if(strcmp(buff,"4")==0)//exit
		{
			printf("Goodbye");
			close(s);
			exit(0);
		}
		else if(strcmp(buff,"1")==0 || strcmp(buff,"2")==0)//ask for balance
		{
			printf("Enter amount\n");
			scanf("%d",amt);			
		}
		else//view balance
		{

		}
	}	
 }
}