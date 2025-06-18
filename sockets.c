// Setting up a TCP Client

// 1. Setting up Socket
// 2. Connecting
// 3. Read some bytes
// 4. Close


#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

//hardcoded now, no dns used
#define IP "142.250.192.100"
#define PORT 80


int main(){
    int s_fd; // Int file descriptor returned by socket()

    // For tcp socket domain = af_inet ipv4 , type = sock_stream and protocolo = 0 or IPPROTO_TCP for stream sockets
    
    s_fd = socket(AF_INET,SOCK_STREAM,0);
    if (s_fd < 0){
        printf("socket() Error \n");
        return -1;
    }

    struct sockaddr_in s_a;//IP Socket Addr combn of IP Interface Addr and 16bit PortNo.
    s_a.sin_family = AF_INET;
    s_a.sin_port = htons(PORT); //htons function takes a 16-bit number in host byte order and returns a 16-bit number in network byte order used in TCP/IP networks (the AF_INET or AF_INET6 address family).
    //sockaddr_in struct has a member sin_addr, which itself is of type struct in_addr, and that has the field s_addr.
    s_a.sin_addr.s_addr = inet_addr(IP); 

    // inet_addr function converts the Internet host address cp from IPv4 numbers-and-dots notation into binary data in network byte order.  If the input is invalid,  INADDR_NONE  (usually  -1)  is  re‐
    // turned. Use of this function is problematic because -1 is a valid address (255.255.255.255).  Avoid its use in favor of  inet_aton(), inet_pton(3), or getaddrinfo(3), which provide a cleaner way to indicate error return

    printf("Connecting to IP %s \n",inet_ntoa(s_a.sin_addr));
    // The inet_ntoa() function converts the  Internet  host  address  in given in network byte order, to a string in IPv4 dotted-decimal notation.

    // The  connect()  system  call connects the socket referred to by the file descriptor sockfd to the address specified by addr. The  addrlen  argument  specifies the size of addr.  The format of the ad‐
    // dress in addr is determined by the  address  space  of  the  socket sockfd; see socket(2) for further details.
    
    int c_s = connect(s_fd,(struct sockaddr *)&s_a,sizeof(struct sockaddr_in));
    //type casting s_a due to const struct arg
    printf("%d \n",c_s);
    if (c_s == -1){
        printf("Connection Error \n");
        close(s_fd);
        return -1;
    }

    // char b[2048]; //buffer
    char *b = malloc(2048);
    
    char *d; 
    d = "GET / HTTP/1.0 \n\n";

    //write to socket file descriptor
    write(s_fd,d,strlen(d));
    read(s_fd,b,2043);
    close(s_fd);

    printf("%s",b);

    
}