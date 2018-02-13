#include <string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>
void swap(char *xp, char *yp)
{
    char temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void bubbleSort(char *arr, int n,int flag)
{
   int i, j;
   for (i = 0; i < n-1; i++)
       for (j = 0; j < n-i-1; j++)
           if (arr[j] > arr[j+1])
              swap(&arr[j], &arr[j+1]);
   if(flag==1)
   	   strrev(arr);
}
void main()
{
	int s,r,recb,sntb,x,ns,a=0,pid,i,j,k;
	char chars[20],nums[20];
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

	printf("\nSocket accepting\n");
	//receive alphanumeric string from client
	recb=recv(ns,buff,sizeof(buff),0);
	//print string
	printf("Received String : %s\n",buff);
	j=0;k=0;
	for(i=0;i<strlen(buff);i++)
	{//split into chars and numbers		
		if(isalpha(buff[i]))
			chars[j++]=buff[i];
		else if(isdigit(buff[i]))
			nums[k++]=buff[i];
	}
	//final length of chars=j and nums=k
	pid=fork();
	if(pid>0)//child
	{//sort numbers in ascending		
		bubbleSort(&nums,k,0);
		printf("%s\n",nums);
	}
	else if(pid==0)//parent
	{//sorts alphabets in descending
		bubbleSort(&chars,j,1);
		printf("%s\n",chars);
	}		
}