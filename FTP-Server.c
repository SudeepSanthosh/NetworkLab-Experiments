#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

void main()
{
	FILE *fp;
	int port,s,n,ssd,clisd;
	char filename[100],contents[100];
	struct sockaddr_in servaddr,cliaddr;
	
	printf("Enter port number:");
	scanf("%d",&port);
	
	ssd=socket(AF_INET,SOCK_STREAM,0);
	if(ssd<0)
		printf("Socket creation failed..\n");
	else
		printf("Socket created successfully!\n");
	
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(port);
	
	if(bind(ssd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
		printf("Binding failed..\n");
	else
		printf("Binded successfully!\n");
	
	listen(ssd,5);
	int clilen=sizeof(cliaddr);
	clisd=accept(ssd,(struct sockaddr*)&cliaddr,&clilen);
	if(clisd<0)
		printf("Accept failed..\n");
	else
		printf("Connection accepted!\n");
	
	
	n=recv(clisd,filename,100,0);
	filename[n]='\0';
	fp=fopen(filename,"r");
	
	if(fp==NULL)
	{
		send(clisd,"Error",5,0);	
	}
	
	while(fgets(contents,sizeof(contents),fp))
	{
		if(send(clisd,contents,sizeof(contents),0)<0)
		{
			printf("Couldn't send..\n");
			exit(0);
		}
		sleep(1);
	}
	
	if(!fgets(contents,sizeof(contents),fp))
	{
		send(clisd,"Completed",sizeof("Completed"),0);
	}
	fclose(fp);
	close(clisd);
}
