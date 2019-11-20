
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include<string.h>
#include <unistd.h>


int main(int argc,char* argv[]){
    int socketfd,portno,n;
    struct sockaddr_in serv_addr;
    
    char buffer[256];

    if(argc<2){
        printf("invalid arguments");
        exit(0);
    }

    portno = atoi(argv[1]);
    int sockfd = socket(AF_INET,SOCK_STREAM,0);

    if(sockfd < 0){
        printf("socket cannot be made");
    }

    bzero(&serv_addr,sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if( connect(sockfd,(struct sockaddr *)&serv_addr, sizeof(serv_addr) ) < 0){
        printf("connect failed");
        exit(0);
    }

    while(1){
        printf("enter message\n");
        fgets(buffer,sizeof(buffer),stdin);
        int n  = write(sockfd, &buffer, sizeof(buffer));
        if(n<0){
            printf("error in reading");
            exit(0);
        }
        int m =  read(sockfd, &buffer, sizeof(buffer));
        if(m<0){
            printf("cannot read");
            exit(0);
        }
        else{
            printf("MESSAGE FROM CLIENT : %s\n",buffer);
        }
    }


}