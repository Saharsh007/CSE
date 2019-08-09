#include<netdb.h> //definitions for network database operations
#include<netinet/in.h> // Internet Protocol family
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h> // main sockets header
#include<sys/types.h> //data types

#define MAX 80
#define PORT 8080
#define SA struct sockaddr



// Function designed for chat between client and server. 
void func(int sockfd) 
{
    char *buff;
    bzero(buff, sizeof(buff));
    buff = "hey xoxo";
    printf("%s",buff);
    write(sockfd, buff, sizeof(buff));
} 

int main(){

	int sockfd, connfd, len; 
    struct sockaddr_in servaddr, cli;

    // socket create and verification 
    // socket(int,int,int) - create an endpoint for communication 
    //arguments - domain,type,protocol
    //domain -  integer, communication domain e.g., AF_INET (IPv4 protocol) , AF_INET6 (IPv6 protocol)
    //type = SOCK_STREAM - TCP(reliable, connection oriented) , SOCK_DGRAM - UDP(unreliable, connectionless) , SOCK_SEQPACKET
    //protocol: Protocol value for Internet Protocol(IP), which is 0. 
    //This is the same number which appears on protocol field in the IP header of a packet.(man protocols for more details)
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 

    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 
    //The bzero() function shall place n zero-valued bytes in the area pointed to by s.
    bzero(&servaddr, sizeof(servaddr)); 

    // assign IP, PORT 
    //INADDR_ANY  - Local host address.
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 

    /*
    The htonl() function converts the unsigned integer hostlong from host byte order to network byte order.
    (converts big endian or little 
   	to computer readble langauge for socket connection	
    htons - unsigned short interger
	*/

	
	// Binding newly created socket to given IP and verification 
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully binded..\n"); 

   /*
   #define SA struct sockaddr
	1.sockfd - socket descriptor
	2. servaddr - structure  
	int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

	After creation of the socket, bind function binds the socket to
	 the address and port number specified in addr(custom data structure). 
	*/

	// Now server is ready to listen and verification 
    if ((listen(sockfd, 5)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 
    else
        printf("Server listening..\n"); 
    len = sizeof(cli); 
    
    /*
	int listen(int sockfd, int backlog);
	mark a socket as accepting connections 
	If successful, listen() returns a value of zero. On failure, it returns -1 

	It puts the server socket in a passive mode, where it waits for the client to approach the server to make a connection.
	The backlog =  defines the maximum length to which the queue of pending connections for sockfd may grow.
				   If a connection request arrives when the queue is full, the client may receive an error with an 
				   indication of ECONNREFUSED.
	*/

	// Accept the data packet from client and verification 
    connfd = accept(sockfd, (SA*)&cli, &len); 
    if (connfd < 0) { 
        printf("server acccept failed...\n"); 
        exit(0); 
    } 
    else
        printf("server acccept the client...\n"); 
  
    /*
    int new_socket= accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
	It extracts the first connection request on the queue of pending connections for the listening socket,
	sockfd, creates a new connected socket, and returns a new file descriptor referring to that socket.
	At this point, connection is established between client and server, and they are ready to transfer data.

	returns non-negative file descriptior in case of successful connection and -1 otherwise
	*/

	// Function for chatting between client and server 
    func(connfd); 
  
    // After chatting close the socket 
    close(sockfd); 
    //returns 0 in case of success else -1
  


}