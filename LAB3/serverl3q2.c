#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
void main()
{
	int s,r,recb,sntb,x,i,n;
	int ca;

	printf("INPUT port number: ");
	scanf("%d", &x);

	socklen_t len;
	struct sockaddr_in server,client;
	char buff[50];

	s=socket(AF_INET,SOCK_DGRAM,0);
	if(s==-1)
	{
		printf("\nSocket creation error");
		exit(0);
	}

	printf("\nSocket created");

	server.sin_family=AF_INET;
	server.sin_port=htons(x);
	server.sin_addr.s_addr=htonl(INADDR_ANY);

	len=sizeof(client);
	ca=sizeof(client);

	r=bind(s,(struct sockaddr*)&server,sizeof(server));

	if(r==-1)
	{
		printf("\nBinding error");
		exit(0);
	}

	printf("\nSocket binded");
	while(1)
	{
		//receive word from client
		recb=recvfrom(s,buff,sizeof(buff),0,(struct sockaddr*)&client,&ca);
		printf("\nReceived string : %s\n",buff);
		if(strcmp(buff,"halt")==0)
		{//exit condition
			close(s);
			break;
		}
		else
		{
			//print permutations
			n=strlen(buff);
			permute(buff, 0, n-1);
			printf("\n\n");
		}
	}
}
void permute(char *a, int l, int r)
{//generate permutations of a given string
   int i;
   if (l == r)//no need to swap
     printf("%s\n", a);
   else
   {
       for (i = l; i <= r; i++)
       {
          swap((a+l), (a+i));
          permute(a, l+1, r);
          swap((a+l), (a+i)); //backtrack
       }
   }
}
void swap(char *x, char *y)
{//to swap two characters in a string
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}