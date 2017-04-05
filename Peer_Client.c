#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>

#define SERVER_IP "10.145.211.194"
#define SERVER_PORT 12000
#define PEER_PORT 13000
int main()
{


int sockfd,newsockfd,status,recbytes,newfd,jk;
struct sockaddr_in serv_addr,peer_addr;

char buf[1000000],file[1000];
//strcpy(file,"vid.mp4");

printf("-----------Enter file you want to download---------(Give Exact names of the files)\n");
scanf("%s",file);

serv_addr.sin_family=AF_INET;
serv_addr.sin_addr.s_addr=inet_addr(SERVER_IP);
serv_addr.sin_port=htons(SERVER_PORT);

peer_addr.sin_family=AF_INET;
peer_addr.sin_port=htons(PEER_PORT);


sockfd=socket(AF_INET,SOCK_DGRAM,0);





while(sendto(sockfd,file,strlen(file),0,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr))==-1)
	printf("send_error\n");


status=sizeof(struct sockaddr);


recbytes=recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr*)&serv_addr,&status);

close(sockfd);

if(recbytes==0)
{

    printf("Connection closed by server\n");
}
else
{

//buf now has destip addr of machine having the requested file

// now connect to peer and download the file
  
buf[recbytes]='\0';

peer_addr.sin_addr.s_addr=inet_addr(buf);


sockfd=socket(AF_INET,SOCK_STREAM,0);

while(connect(sockfd,(struct sockaddr*)&peer_addr,sizeof(peer_addr))==-1)
	printf("Error connecting to peer\n");

while(send(sockfd,file,strlen(file),0)==-1)
	printf("send_error_to_peer\n");



recbytes=recv(sockfd,buf,1000000,0);


if (recbytes==0)
{
		printf("connection_closed_by_peer\n");
}

else
{

//jk=0;

    newfd=open(strcat(file,"(_retrived)"),O_WRONLY|O_TRUNC|O_CREAT,S_IRWXU);

    write(newfd,buf,recbytes);

    while(recbytes!=0)
   {

     recbytes=recv(sockfd,buf,1000000,0);

     write(newfd,buf,recbytes);

   }

   close(newfd);

   printf("*****************Download Successful******************\n");
   close(sockfd);


}



}


return 0;
}
