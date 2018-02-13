#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
void main()
{
	int s,r,recb,sntb,x;
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
		recb=recvfrom(s,buff,sizeof(buff),0,(struct sockaddr*)&client,&ca);
		printf("\nReceived string : %s\n",buff);
		
		if(strcmp(buff,"halt")==0)
			break;

		int i=0;
		int lengthOfArr=strlen(buff);
		int j=lengthOfArr-1;
		int flag=1;
		char result[100];
		char myLength[100];
		strcpy(result,"");

		while(i<j)
		{
			if(buff[i]!=buff[j])
			{
				flag=0;
				break;
			}
			i++;
			j--;
		}
		if(flag==1)
		{	
			strcat(result," Palindrome of length : \n");
			char myLength[10];
			sprintf(myLength,"%d",lengthOfArr);
			strcat(result,myLength);
			printf("\n%s\n",result);
		}
		else
		{
			strcat(result,"Not Palindrome, length : \n");
			sprintf(myLength,"%d",lengthOfArr);
			strcat(result,myLength);
			printf("\n%s\n",result);
		}

		int aCount=0;
		int eCount=0;
		int iCount=0;
		int oCount=0;
		int uCount=0;

		for(i=0;i<lengthOfArr;i++)
		{
	
			if(buff[i]=='a')
				aCount++;
			if(buff[i]=='e')
				eCount++;
			if(buff[i]=='i')
				iCount++;
			if(buff[i]=='o')
				oCount++;
			if(buff[i]=='u')			
				uCount++;			
		}
		strcpy(myLength,"");
		sprintf(myLength,"%d\t",aCount);
		strcat(result,myLength);
		strcat(result,"\t");
		sprintf(myLength,"%d",eCount);
		strcat(result,myLength);
		strcat(result,"\t");
		sprintf(myLength,"%d",iCount);
		strcat(result,myLength);
		strcat(result,"\t");
		sprintf(myLength,"%d",oCount);
		strcat(result,myLength);
		strcat(result,"\t");
		sprintf(myLength,"%d",uCount);
		strcat(result,myLength);
		strcat(result,"\t");
		printf("%s",result);
		sntb=sendto(s,result,sizeof(result),0,(struct sockaddr*)&client,len);
	}
}