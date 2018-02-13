#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
main()
{
	int s,r,recb,sntb,x,ns,a=0;
	printf("INPUT port number: ");
	scanf("%d", &x);
	socklen_t len;
	struct sockaddr_in server,client;
	char buff[500];
	char content[500];
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
	printf("\nSocket accepting.\n\n");
	while(1)
	{
		recb=recv(ns,buff,sizeof(buff),0);
		printf("%s\n\n",buff);
		if(strcmp(buff,"exit")==0)
			break;
		FILE *f;
		f=fopen(buff, "r");
		strcpy(buff,"");
		if(f==NULL)
		{
			strcpy(buff,"errorNOfile\n\n");
			printf("\n\n\n");
			sntb=send(ns,buff,sizeof(buff),0);
			printf("\n\n\n");
		}
		else
		{
			fgets( content,1000,f);
			printf("\n\n\n");
			sntb=send(ns,content,sizeof(content),0);
			printf("\n\n\n");
			recb=recv(ns,buff,sizeof(buff),0);
			printf("the option selected is %s",buff);
			printf("\n\n");
			int opt=atoi(buff);
			if(opt==3)
			{
				break;
			}
			else if(opt==1)
			{
				recb=recv(ns,buff,sizeof(buff),0);
				printf("%s",buff);
				printf("\n\n");
				printf("search begins....\n");
				char temp[50];
				int le=strlen(content);
				int k;
				int l=0;
				int count=0;
				for(k=0;k<le;k++)
				{
					if(buff[k]==' '||buff[k]=='\0')
					{
						temp[l]='\0';
						l=0;
						if(strcmp(temp,buff)==0)
						{
						
							count++;
							printf("%s\n\n",temp);
						}
						strcpy(temp,"");
					}
					else
					{
						temp[l++]=content[k];

					}
				}
				sprintf(buff,"%d",count);
				printf("the count is %d\nAlso its being forwarded to client\n", count);
				sntb=send(ns,buff,sizeof(buff),0);
				printf("\n\n");
			}
			else if(opt==2)
			{
			
				int j,k;
				for(k=0;k<strlen(content)-1;k++)
				{
					for(j=0;j<strlen(content)-k-1;j++)
					{
						if(content[j]>content[j+1])
						{
							char temp=content[j];
							content[j]=content[j+1];
							content[j+1]=temp;
						}
					}
				}
				printf("%s",content);
				printf("\n");
				fclose(f);
				f=fopen("a.txt","w+");
				fputs(content,f);
				printf("\n");

			}
			else if(opt==4)
			{
				char buff1[50];
				recb=recv(ns,buff1,sizeof(buff1),0);
				printf("%s",buff1);
				printf("\n\n");
				char buff2[50];
				recb=recv(ns,buff2,sizeof(buff2),0);
				printf("%s",buff2);
				printf("\n\n");
				int le=strlen(content);
				int k;
				int l=0;
				char result[50];
				strcpy(result,"");
				char temp[50];
				int flag=0;
				for(k=0;k<le;k++)
				{

					if(content[k]==' '||content[k]=='\0')
					{
						temp[l]='\0';
						l=0;
						if(strcmp(temp,buff1)==0)
						{
							strcat(result," ");
							flag=1;
							strcat(result,buff2);
						}
						else
						{
							strcat(result," ");
							strcat(result,temp);	
						}
					}
					else
					{
						temp[l++]=content[k];
					}
				}
			
				printf("sending the message to client \n");
				if(flag==0)
				{
					strcpy(buff,"string not found");
				}
				else
				{
					strcpy(buff,"replacement done");
					printf("\nthe new string is %s\n", result);
				}
				sntb=send(ns,buff,sizeof(buff),0);
				printf("\n\n");

			}
		}
	

	}
}
