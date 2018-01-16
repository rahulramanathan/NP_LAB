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
int arr[100], i,j, n, search,choice;
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
printf("\nMessage Recieving Failed");
close(s);
close(ns);
exit(0);
}
printf("%s",buff);
choice=(int)buff[0];
n=(int)buff[1];
if(choice==1)
{
	printf("Enter ele to search:\n");
	scanf("%d", &search);
	for(i=2;i<n+2;i++)
	{
	 if ((int)buff[i]==search)
	 {	printf("%d is present at %d\n",search,i+2);
		break;
	 }
	}	
	if(i==n)
	printf("%d is not present in the array\n",search);
}
else if(choice==2)
{ 
// A function to implement bubble sort
   for (i = 2; i < n+1; i++) 
       for (j = 2; j < n-i+1; j++)
           if (buff[j] > buff[j+1])
               {
		 int temp=(int)buff[j];
		 buff[j]=(int)buff[j+1];
		 buff[j+1]=temp;
		}
printf("Sorted Array\n%s",buff);
}
}
