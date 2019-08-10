#include <stdio.h>  
#include <string.h>   //strlen  
#include <stdlib.h>  
#include <errno.h>  
#include <unistd.h>   //close  
#include <arpa/inet.h>    //close   definitions for internet operations
#include <sys/types.h>   // data types
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros  

#define TRUE   1  
#define FALSE  0  
#define PORT 8888  

int main(int argc , char *argv[])   
{   
    int opt = TRUE;   
    int master_socket , addrlen , new_socket , client_socket[30] ,  
          max_clients = 30 , activity, i , valread , sd,tempsocket;   
    // client_socket is the array of file descriptors      
    int max_sd;   
    struct sockaddr_in address;

    /*
    #include <netinet/in.h>

    struct sockaddr_in {
        short            sin_family;   // e.g. AF_INET
        unsigned short   sin_port;     // e.g. htons(3490)
        struct in_addr   sin_addr;     // see struct in_addr, below
        char             sin_zero[8];  // zero this if you want to
    };

    struct in_addr {
        unsigned long s_addr;  // load with inet_aton()
    };

    */

    char buffer[1025];  //data buffer of 1K  
         
    //set of socket descriptors  
    fd_set readfds;  
    /*
    It contains the list of file descriptors to monitor for some activity.
    // Clear an fd_set
    FD_ZERO(&readfds);  

    // Add a descriptor to an fd_set
    FD_SET(master_sock, &readfds);   

    // Remove a descriptor from an fd_set
    FD_CLR(master_sock, &readfds); 

    //If something happened on the master socket , then its an incoming connection  
    FD_ISSET(master_sock, &readfds); 
    */
        //a message  
    char *message = "Hey client , congrats you are connected\r\n";   

    //initialise all client_socket[] to 0 so not checked  
    for (i = 0; i < max_clients; i++)   
        client_socket[i] = 0;   

    //create a master socket  
    //---------------------------------------------------------------------------------------------------------------------------------------------------------------
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)   
    {   
        perror("socket failed");   
        exit(EXIT_FAILURE);   
    }
    // I think the value on the right of == should be -1 as socket never returns 0 in case of error   
    //--------------------------------------------------------------------------------------------------------------------------------------------
    
    //set master socket to allow multiple connections ,  
    //this is just a good habit, it will work without this  
    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,  
          sizeof(opt)) < 0 )   
    {   
        perror("setsockopt");   
        exit(EXIT_FAILURE);   
    }   
    //setsockopt - This helps in manipulating options for the socket referred by the file descriptor sockfd. 
    
    //type of socket created  
    address.sin_family = AF_INET;   
    address.sin_addr.s_addr = htonl(INADDR_ANY);   
    address.sin_port = htons( PORT );

    //bind the socket to localhost port 8888  
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)   
    {   
        perror("bind failed");   
        exit(EXIT_FAILURE);   
    }   
    printf("Listener on port %d \n", PORT);     

    //try to specify maximum of 3 pending connections for the master socket  
    if (listen(master_socket, 3) < 0)   
    {   
        perror("listen");   
        exit(EXIT_FAILURE);   
    } 
    /*
    The listen function converts an unconnected socket into a passive socket,
     indicating that the kernel should accept incoming connection requests directed to this socket.
    */

    //accept the incoming connection  
    addrlen = sizeof(address);   
    puts("Waiting for connections ...");   
        
    while(TRUE)   
    {   
            //clear the socket set  
            FD_ZERO(&readfds);   
         
            //add master socket to set  
            FD_SET(master_socket, &readfds);   
            max_sd = master_socket; 

            //add child sockets to set  
            for ( i = 0 ; i < max_clients ; i++)   
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
            /*
            int select(int  nfds, fd_set  *readfds, fd_set  *writefds, fd_set *errorfds, struct timeval *timeout);
            This call returns 0 on success, otherwise it returns -1 on error.

            Parameters
            nfds − It specifies the range of file descriptors to be tested. 
            The select() function tests file descriptors in the range of 0 to nfds-1

            readfds − It points to an object of type fd_set that on input, 
            specifies the file descriptors to be checked for being ready to read, and on output, 
            indicates which file descriptors are ready to read. It can be NULL to indicate an empty set.

            writefds − It points to an object of type fd_set that on input, 
            specifies the file descriptors to be checked for being ready to write, and on output,
             indicates which file descriptors are ready to write. It can be NULL to indicate an empty set.

            exceptfds − It points to an object of type fd_set that on input, 
            specifies the file descriptors to be checked for error conditions pending, and on output indicates, 
            which file descriptors have error conditions pending. It can be NULL to indicate an empty set.

            timeout − It points to a timeval struct that specifies how long the select call should poll the descriptors 
            for an available I/O operation. If the timeout value is 0, then select will return immediately. If the timeout 
            argument is NULL, then select will block until at least one file/socket handle is ready for an available 
            I/O operation. Otherwise select will return after the amount of time in the timeout has elapsed OR when at 
            least one file/socket descriptor is ready for an I/O operation.   
                   
           */

            if ((activity < 0) && (errno!=EINTR))   
            {   
                printf("select error");   
            }   

            //If something happened on the master socket ,  
            //then its an incoming connection  
        if (FD_ISSET(master_socket, &readfds))   
        {   
            if ((new_socket = accept(master_socket,  
                    (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)   
            {   
                perror("accept");   
                exit(EXIT_FAILURE);   
            }   

          //inform user of socket number - used in send and receive commands  
            printf("New connection , socket fd is %d , ip is : %s , port : %d \n" 
                , new_socket , inet_ntoa(address.sin_addr) , ntohs 
                  (address.sin_port));   
           

            //send new connection greeting message  
            if( send(new_socket, message, strlen(message), 0) != strlen(message) )   
            {   
                perror("send");   
            }   

            puts("Welcome message sent successfully");   
                 
            //add new socket to array of sockets  
            for (i = 0; i < max_clients; i++)   
            {   
                //if position is empty  
                if( client_socket[i] == 0 )   
                {   
                    client_socket[i] = new_socket;   
                    printf("Adding to list of sockets as %d\n" , i);   
                         
                    break;   
                }   
            }   
        }   

        //else its some IO operation on some other socket 
        for (i = 0; i < max_clients; i++)   
        {   
            // printf("for client %d",i+1);

            sd = client_socket[i];   
            
            if (FD_ISSET( sd , &readfds))   
            {   
                //Check if it was for closing , and also read the  
                //incoming message  
                if ((valread = read( sd , buffer, 1024)) == 0)   
                {   
                    //Somebody disconnected , get his details and print  
                    getpeername(sd , (struct sockaddr*)&address ,
                        (socklen_t*)&addrlen);   
                    printf("Host disconnected , ip %s , port %d \n" ,  
                          inet_ntoa(address.sin_addr) , ntohs(address.sin_port));   
                         
                    //Close the socket and mark as 0 in list for reuse  
                    close( sd );   
                    client_socket[i] = 0;   
                }   
                     
                //Echo back the message that came in  
                else 
                {   
                    char *buff;

                    read(sd, buff, sizeof(buff)); 
                    printf("From client: %s\t", buff); 
                    for(int temp = 0; temp<max_clients; temp++){
                        tempsocket = client_socket[temp];
                        if(tempsocket != 0)
                        write(sd, buff, sizeof(buff)); 
                    }
                    //set the string terminating NULL byte on the end  
                    //of the data read  
                    // buffer[valread] = '\0';
                    // send(sd , buffer , strlen(buffer) , 0 );   

                }   
            }   
        }   
    }   
         
    return 0;   
}