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
	int s,r,recb,sntb,x;

	printf("INPUT port number: ");
	scanf("%d", &x);

	struct sockaddr_in server;
	char buff[500];
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

	while(1)
	{
		printf("Enter the name of the file");
		scanf("%s",buff);
		sntb=send(s,buff,sizeof(buff),0);
		if(strcmp(buff,"exit")==0)
			break;
		printf("\n\n\n");
		recb=recv(s,buff,sizeof(buff),0);
		printf("%s",buff);
		if(strcmp(buff,"errorNOfile\n\n")==0)
		{
			break;
		}
		else
		{
			printf("1.Search2.Sort3.exit4.replace\n");
			int opt;
			scanf("%d",&opt);
		
			sprintf(buff,"%d",opt);
			sntb=send(s,buff,sizeof(buff),0);

			if(opt==0)
				break;
			else if(opt==1)
			{
				printf("Enter search option\n");
				scanf("%s",buff);
				sntb=send(s,buff,sizeof(buff),0);
				recb=recv(s,buff,sizeof(buff),0);
				printf("the count of the word you searched %s\n",buff);
				printf("\n\n");

			}
			else if(opt==3)
			{
				break;
			}
			else if(opt==4)
			{
				printf("enter first word");
				char buff1[50];
				scanf("%s",buff1);
				sntb=send(s,buff1,sizeof(buff1),0);
				printf("\n\n");
				printf("enter second word");
				char buff2[50];
				scanf("%s",buff2);
				sntb=send(s,buff2,sizeof(buff2),0);
				printf("\n\n");
				recb=recv(s,buff,sizeof(buff),0);
				printf("the recieved message is \n%s\n",buff );
				printf("\n\n\n");
			}

		}

	}
}












