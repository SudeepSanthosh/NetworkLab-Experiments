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
	int cport,s,csd;
	char file[100],contents[100],new_file[100];
	struct sockaddr_in servaddr;
	
	printf("Enter port number:");
	scanf("%d",&cport);
	
	csd=socket(AF_INET,SOCK_STREAM,0);
	if(csd<0)
	{
		printf("Socket creation failed..\n");
		exit(0);
	}
	else
		printf("Socket created successfully!\n");
	
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servaddr.sin_port=htons(cport);
	
	if(connect(csd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
	{
		printf("Connection failed..\n");
		exit(0);
	}
	else
		printf("Connected successfully!\n");
		
	printf("Enter file name to fetch from server:");
	scanf("%s",file);
	printf("Enter file name to write contents into:");
	scanf("%s",new_file);
	
	fp=fopen(new_file,"w");
	
	send(csd,file,sizeof(file),0);
	
	while(1)
	{
		s=recv(csd,contents,100,0);
		contents[s]='\0';
		
		if(strcmp(contents,"Error")==0)
		{
			printf("Error..\n");
			exit(0);
		}
		
		if(strcmp(contents,"Completed")==0)
		{
			printf("File transfer completed!\n");
			fclose(fp);
			close(csd);
			break;
		}
		
		else
			fputs(contents,stdout);
		fprintf(fp,"%s",contents);
	}	
}
