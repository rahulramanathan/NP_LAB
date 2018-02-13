#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
void main()
{
	int s,r,recb,sntb,x,ns,a=0,pid,i;
	printf("INPUT port number: ");
	scanf("%d", &x);
	socklen_t len;
	struct sockaddr_in server,client;
	char buff[50],data[100],cdata[100],pdata[100];
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

	printf("\nSocket accepting\n");
	recb=recv(ns,buff,sizeof(buff),0);
	printf("Received filename%s\n",buff);
	if(recb==-1)
	{
		printf("Error");
		close(ns);
		close(s);
		exit(0);		
	}
	printf("Received filename%s\n",buff);
	FILE *f;
	f=fopen(buff,"rw");
	if(f==NULL)
	{
		printf("File not found\n");
		close(ns);
		close(s);
		exit(0);
	}
	else
	{//file found
		fscanf(f,"%s",&data);//read text from file
		puts(data);
		strcpy(cdata,data);
		strcpy(pdata,data);
		pid=fork();
		if(pid>0)
		{//child
			for(i=0;i<strlen(data);i++)
			{//convert to uppercase
				if(data[i]>='a'&&data[i]<='z')
					data[i]-=32;
			}
			fprintf(f,"%d\n",pid);
			fprintf(f,"%s\n",cdata);
		}
		else if(pid==0)
		{//parent			
			for(i=0;i<strlen(data);i++)
			{//convert to uppercase
				if(data[i]>='a'&&data[i]<='z')
					data[i]-=48;
				else if(data[i]>='A'&&data[i]<='Z')
					data[i]-=16;
			}
			fprintf(f,"%d\n",pid);
			fprintf(f,"%s\n",pdata);	
		}
		// strcpy(buff,"read");
		// sntb=send(ns,buff,sizeof(buff),0);		
	}
}