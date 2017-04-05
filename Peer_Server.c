#include<sys/types.h>
#include<sys/stat.h>
#include<sys/fcntl.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(){


int sockfd,newsockfd,status,portno=13000,recbytes,file,id,rb,jk;
struct sockaddr_in saddr,caddr;

char filename[1000],buf[1000000];


saddr.sin_family=AF_INET;
saddr.sin_addr.s_addr=INADDR_ANY;
saddr.sin_port=htons(portno);


sockfd=socket(AF_INET,SOCK_STREAM,0);


while(bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr))==-1)printf("socket_bind_unsuccessful__\n");


printf("Socket Binded__\n");



while(listen(sockfd,5)==-1)printf("cannot_listen()__\n");

printf("Listening =========\n");


id=1;

while(1){


status=sizeof(caddr);
newsockfd=accept(sockfd,(struct sockaddr*)&caddr,&status);

while(newsockfd==-1)
{
    newsockfd=accept(sockfd,(struct sockaddr*)&caddr,&status);printf("accept_error\n");}

    id=fork();

    if(id==0)
    {
                 
        recbytes=recv(newsockfd,filename,sizeof(filename),0);
                 
        if(recbytes==0)
        {
	        printf("connection_closed_by_peer_client\n");
        }
        else
        {
     
            filename[recbytes]='\0';
                    //buf now has the filename to send to newsockfd

            file=open(filename,O_RDONLY);

            rb=read(file,buf,1000000);

            send(newsockfd,buf,rb,0);

            while(rb!=0)
            {

                rb=read(file,buf,1000000);
     
                send(newsockfd,buf,rb,0);


            }
                                    
            printf("file_sent_successfully\n");
    

        }

        close(file);
        close(newsockfd);

        exit(0);

    }

    else 
        close(newsockfd);

}
return 0;
}
