#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
struct Student
{
	int regno;
	int sem;
	char sec;
	char name[50];
	char address[50];
	char dept[50];	
};
void main()
{
	//Decalarnig the database
	struct Student student;
	student.regNo=150953242;
	student.sem=6;
	strcpy(student.sec,"B");
	strcpy(aditya.name,"aditya");	
	strcpy(aditya.address,"Thane");
	strcpy(aditya.dept,"ICT");

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
	
}