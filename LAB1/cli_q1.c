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
main()
{
int s,r,recb,sntb,x,choice,i,n;
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
printf("\n\n");
/*while(true)
{//start of while*/
printf("Enter choice\n1 for search\n2 for sort\n3 for odd-even split\n4 to exit");
scanf("%d",&choice);
if(choice==4)
 ;
else
{//send msg to server
	buff[0]=choice;	
	printf("Enter the no. of elements:\n");
	scanf("%d", &n);
	buff[1]=n;
	printf("Enter the elements:\n");
	for(i=2;i<n+2;i++)
		scanf("%s", &buff[i]);
	sntb=send(s,buff,sizeof(buff),0);
	if(sntb==-1)
	{
	close(s);
	printf("\nMessage Sending Failed");
	exit(0);
	}
}
close(s);
}
