#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include<string.h>
#include <unistd.h>

x
int main(int argc,char* argv[] ){

    int sockfd,newsock,port_no;
    char buffer[256];
    socklen_t clilen ;  //its a dattype which stores length
    struct sockaddr_in serv_addr,cli_addr;

    // testing argument
    if(argc < 2){
        printf("invalid argument\n");
        exit(0);
    }
    port_no = atoi(argv[1]);

    sockfd = socket(AF_INET,SOCK_STREAM,0); //creating socket

    if(sockfd<0){
        printf("SOCKET COULD NOT BE CREATED");
        exit(0);
    }

    //initializing buffer to zero
    bzero( (char*) &serv_addr,sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_no);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if( bind(sockfd,(struct sockaddr*) &serv_addr, sizeof(serv_addr) ) < 0 ){
        printf("BIND FAILED");
        exit(0);
    } 

    listen(sockfd,1); //now we are ready to recieve message
    int clen = sizeof(cli_addr);
    int newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clen);

    if(newsockfd<0){
        printf("ACCEPT FAILED!");
        exit(0);
    }

    while(1){

        bzero(buffer,sizeof(buffer));
        int n = read(newsockfd,&buffer,sizeof(buffer));
        if(n<=0){
            printf("CANNOT READ");
        }

        else{
            printf("MESSAGE IS : %s\n",buffer);
            printf("\nENTER A MESSAGE : ");
            char message[256];
            fgets(message,sizeof(message),stdin);
            int n = write(newsockfd,message,sizeof(message));
            if(n<0){
                printf("write unsuccessful");
            }
        }
    }

    return 0;
}