# TCP SOCKET PROGRAMMING IN LINUX C

### Some Networking Concepts 
Ref:   
https://man7.org/linux/man-pages/
https://nmap.org/ncat/guide/ncat-usage.html
https://www.geeksforgeeks.org/linux-unix/practical-uses-of-ncnetcat-command-in-linux/
https://dev.to/sanjayrv/a-beginners-guide-to-socket-programming-in-c-5an5

###  1. NCAT 

Can be used for operations related to TCP, UDP or UNIX domain sockets, opening remote connections or proxies, port scan, listen and redirections

*Basic syntax : nc [options] [hostname] [port]*

By default, Ncat uses TCP. The option --udp or -u enables UDP instead, and --sctp enables SCTP. Ncat listens on both IPv4 and IPv6, and connects to either address family as well. The -6 option forces IPv6-only, and -4 forces IPv4-only. 

 1. Connect Mode: 

**Params**: host, port

    ncat -C scanme.nmap.org 80    
    GET / HTTP/1.0

    Or 

    HEAD / HTTP/1.0

    For just the header

--. In connect mode, Ncat initiates a connection (or sends UDP data) to a service that is listening somewhere. Connect mode is like using the connect function. 
--In this case we use Ncat to manually retrieve a web page from an HTTP server, just as web browsers do in the background when you visit a web site.   
--Here we have instructed Ncat to connect to the host scanme.nmap.org on port 80, the port for HTTP. The -C option turns on CRLF replacement, which replaces any line endings you type with CRLF.  
--GET / HTTP/1.0 requests the root document of the server; we are retrieving the same document named by the URL http://scanme.nmap.org:80/. The web server responds with a status code (HTTP/1.1 200 OK), followed by the HTTP header and the text of the web page
    

 2. Listen Mode: 

**Params**: host, port

    touch hello.http
    nano hello.http

    HTTP/1.0 200 OK

    <html>
    <body>
        <h1>Hello, world!</h1>
    </body>
    </html>

    ncat -l localhost 8080 <hello.http


--For using the Ncat as a server. After creating a document to serve, now the command instructs Ncat to listen on the local port 8080 and read hello.http on its input. Ncat is now primed to send the contents of the file as soon as it receives a connection. Now upon opening a web browser and type in the address http://localhost:8080/ we get the result.      
--In listen mode, <host> controls the address on which Ncat listens; if you omit it, Ncat will bind to all local interfaces (INADDR_ANY). If the port number is omitted, Ncat uses its default port 31337. Typically only privileged (root) users may bind to a port number lower than 1024.


*Finding IPv4 of a host: host hostname or nslookup hostname or just ping hostname*



        