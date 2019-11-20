#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include<string.h>
#include <unistd.h>

int main(){

    int sockfd,newsock,port_no,client_socket[30],sd,n;
    int max_sd;
    char buffer[256];
    socklen_t clilen ;  //its a dattype which stores length
    struct sockaddr_in serv_addr,cli_addr;

    // testing argument
    // if(argc < 2){
    //     printf("invalid argument\n");
    //     exit(0);
    // }
    port_no = atoi("51717");

    int master_socket = socket(AF_INET,SOCK_STREAM,0); //creating socket

    if(sockfd<0){
        printf("SOCKET COULD NOT BE CREATED");
        exit(0);
    }

    //initializing buffer to zero
    bzero( (char*) &serv_addr,sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_no);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if( bind(master_socket,(struct sockaddr*) &serv_addr, sizeof(serv_addr) ) < 0 ){
        printf("BIND FAILED");
        exit(0);
    } 

    int clen = sizeof(cli_addr);


    listen(sockfd,5); //now we are ready to recieve message
    int MAX_CLIENT  = 30;
    for(int i=0;i<MAX_CLIENT;i++){
        client_socket[i]=0;
    }

    fd_set readfds;
    char *message = "WELCOME TO THE CHATROOM\n";
    int activity;
    while(1){
        FD_ZERO(&readfds);
        FD_SET(master_socket,&readfds);
        max_sd = master_socket;
        for (int i = 0 ; i < MAX_CLIENT ; i++)   
        {   
            //socket descriptor  
            sd = client_socket[i]; 
            //if valid socket descriptor then add to read list  
            if(sd > 0)   
                FD_SET( sd , &readfds);
            //highest file descriptor number, need it for the select function  
            if(sd > max_sd)   
                max_sd = sd;   
        }
        
        //wait for an activity on one of the sockets , timeout is NULL ,  
        //so wait indefinitely  
         activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);
        if ((activity < 0) )   
        {   
            printf("select error");   
        } 

        //If something happened on the master socket ,  
        //then its an incoming connection  
        if (FD_ISSET(master_socket, &readfds)){
            int new_socket = accept(master_socket,(struct sockaddr *)&cli_addr,&clilen);
            printf("%d,%d,%d",master_socket,activity,new_socket);
            if(new_socket<0) 
            {   
                printf("accept failed");   
                exit(0);   
            }         
            write(new_socket,message,sizeof(message));
            for (int i = 0; i < MAX_CLIENT; i++)   
            {   
                if(client_socket[i] ==0){
                    client_socket[i] = new_socket;
                    printf("new client added\n");
                    break;
                }  
            }
        }

        for(int i=0;i<MAX_CLIENT;i++){
            sd = client_socket[i];
            if(FD_ISSET(sd,&readfds)){
                n = read(sd,buffer,sizeof(buffer));
                if(n==0) printf("connecttion terminated for some client");
                else{
                    printf("message from client : %s\n",buffer);
                    write(sd,buffer,sizeof(buffer));
                }
            }
        }
    }

    // int newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clen);

    // if(newsockfd<0){
    //     printf("ACCEPT FAILED!");
    //     exit(0);
    // }

    // while(1){

    //     bzero(buffer,sizeof(buffer));
    //     int n = read(newsockfd,&buffer,sizeof(buffer));
    //     if(n<=0){
    //         printf("CANNOT READ");
    //     }

    //     else{
    //         printf("MESSAGE IS : %s\n",buffer);
    //         printf("\nENTER A MESSAGE : ");
    //         char message[256];
    //         fgets(message,sizeof(message),stdin);
    //         int n = write(newsockfd,message,sizeof(message));
    //         if(n<0){
    //             printf("write unsuccessful");
    //         }
    //     }
    // }

    return 0;
}