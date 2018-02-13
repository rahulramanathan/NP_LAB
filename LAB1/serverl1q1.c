#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
void main()
{
	int s,r,recb,sntb,x,ns,a=0;
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

	printf("\nSocket accepting");

	recb=recv(ns,buff,sizeof(buff),0);

	printf("%s\n\n",buff);
	int n=atoi(buff);
	int *arr=(int *)malloc(sizeof(int)*n);

	recb=recv(ns,arr,sizeof(int)*n,0);

	int i=0;
	for(i=0;i<n;i++)
	{
		printf("%d\n",arr[i]);
	}
	while(1)
	{
		// to take opt
		recb=recv(ns,buff,sizeof(buff),0);
		int opt=atoi(buff);
		printf("Option : %d\n",opt);
		if(opt==1)
		{			
			int j,k;
			for(j=0;j<n-1;j++)
				for(k=0;k<n-j-1;k++)
				{
					if(arr[k]>arr[k+1])
					{
						int temp=arr[k];
						arr[k]=arr[k+1];
						arr[k+1]=temp;
					}
				}			
			printf("Sorted List\n");		
			for(i=0;i<n;i++)
			{
				printf("%d\n",arr[i]);
			}
		}	
		if(opt==2)
		{
			recb=recv(ns,buff,sizeof(buff),0);
			int ele=atoi(buff);
			printf("Element to search : %d",ele);
			printf("\n\n\n");
			int flag=0;
			for(i=0;i<n;i++)
			{		
				if(ele==arr[i])
				{
					flag=1;
					printf("Element found");
					break;
				}		
			}
			if(flag==0)
			{
				printf("Element not present");
			}			
		}
		if(opt==3)
		{
			printf("Odd Numbers\n");
			for(i=0;i<n;i++)
			{
				if(arr[i]%2==1)
				{
					printf("%d\n",arr[i]);
				}
			}
			printf("Even numbers\n");
			for(i=0;i<n;i++)
			{
				if(arr[i]%2==0)
				{
					printf("%d\n",arr[i]);
				}
			}			
		}
		if(opt==4)
		{
			printf("Terminating");
			break;
		}
	}
}