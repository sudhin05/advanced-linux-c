// Setting up a TCP Server

// 1. Socket Creation
// 2. Bind
// 3. Listen
// 4. Accept
// 5. Data passing
// 6. Close

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>


//Mainly going for same fd, s_a structure but in latter instead of an IP we set 0 to check for all ips

#define PORT 8181

int main(){
    int s_fd,c_fd;
    
    s_fd = socket(AF_INET,SOCK_STREAM,0);
    if (s_fd < 0){
        printf("socket() error");
        return -1;
    }
    struct sockaddr_in srv, cli;
    srv.sin_family = AF_INET;
    srv.sin_port = htons(PORT);
    srv.sin_addr.s_addr = 0; //for all ips

    // When  a socket is created with socket(2), it exists in a name space (address family) but has no address assigned to it.  bind() assigns the address specified by addr to the socket referred to by the file
    // descriptor sockfd.  addrlen specifies the size, in  bytes,  of  the address  structure  pointed to by addr.  Traditionally, this operation is called “assigning a name to a socket”.

    int b_s = bind(s_fd,(struct sockaddr *)&srv,sizeof(struct sockaddr_in)); // can replace struct sockaddr_in by srv ig
    if (b_s == -1){
        printf("bind() error");
        close(s_fd);
    }
    // Now listen
    printf("listening on 0.0.0.0:%d\n",PORT);
    int l_s = listen(s_fd,5); //The  backlog argument defines the maximum length to which the queue of pending connections for sockfd may grow.  If  a connection request arrives when the queue is full, the client may receive an error with an indication of ECONNREFUSED
    if (l_s == -1){
        printf("listen() error");
        close(s_fd);
    }
    //Now accept

    // The accept() system call is used with connection-based socket types (SOCK_STREAM,  SOCK_SEQPACKET).   It  extracts the first connection request on the queue  of  pending  connections  for  the  listening socket,  sockfd,  creates a new connected socket, and returns a new
    // file descriptor referring to that socket.  The newly created socket is not in the listening state.  The original socket sockfd is unaffected by this call.
    socklen_t addrlen;//Describes the length of a socket address.  This is an  integer type of at least 32 bits.
    addrlen = 0;

    c_fd = accept(s_fd,(struct sockaddr *)&srv,&addrlen);
    if (c_fd < 0){
        printf("accept() error");
    }
    printf("Client connected\n");

    char b[2048];
    char *d;

    //read request from client
    read(c_fd,b,2047);
    char *data = "HTTTP/1.0 200 OK\n"; //petending webserver message
    write(c_fd,data,strlen(data));
    close(c_fd);
    close(s_fd);
    return 0;

}