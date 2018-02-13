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
void  main()
{
	int s,r,recb,sntb,x;

	printf("INPUT port number: ");
	scanf("%d", &x);

	struct sockaddr_in server;
	char buff[50];

	s=socket(AF_INET,SOCK_STREAM,0);
	if(s==-1)
	{
		printf("\nSocket creation error");
		exit(0);
	}
	printf("\nSocket created.");
	server.sin_family=AF_INET;
	server.sin_port=htons(x);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	r=connect(s,(struct sockaddr*)&server,sizeof(server));
	if(r==-1)
	{
		printf("\nConnection error");
		exit(0);
	}
	printf("\nSocket connected");	
	int n;
	printf("\nEnter list length");
	scanf("%d",&n);
	sprintf(buff, "%d", n);
	sntb=send(s,buff,sizeof(buff),0);
	int i;
	int *arr=(int *)malloc(sizeof(int)*n);
	printf("\nEnter numbers");
	for(i=0;i<n;i++)
	{
		scanf("%d",arr+i);
	}
	sntb=send(s,arr,sizeof(int)*n,0);
	while(1)
	{
		printf("1.Sorting\n2.Searching\n3.Splitting\n4.Exit\n");
		int opt;	
		scanf("%d",&opt);
		sprintf(buff, "%d", opt);
		sntb=send(s,buff,sizeof(buff),0);
		if(opt==2)
		{
			printf("Enter Search element");
			int ele;
			scanf("%d",&ele);
			sprintf(buff, "%d", ele);
			sntb=send(s,buff,sizeof(buff),0);
		}	
		if(opt==4)
		{
			printf("Terminating");
			break;
		}
	}
}