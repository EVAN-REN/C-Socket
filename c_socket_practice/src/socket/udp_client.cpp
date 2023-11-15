#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define SERVER_PORT 50001
#define SERVER_IP "127.0.0.1"

int main(int argc, char *argv[]){

    int sockfd;
    char *message;
    struct sockaddr_in server_addr;

    if(argc != 2){
        fputs("Usage: client message \n", stderr);
        exit(1);
    }

    message = argv[1];

    std::cout << "message:" << message << std::endl;

    //create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if(sockfd == -1){
        std::cout << "Failed to create socket" << std::endl;
        return 1;
    }

    //clear and add the information
    memset(&server_addr, 0, sizeof(sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    if(inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) != 1){
        std::cerr << "Invalid IP address" << strerror(errno) << std::endl;
        close(sockfd);
        return 1;
    }

    //write add
    sendto(sockfd, message, sizeof(message), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));

    //receive
    char buf[1024];
    socklen_t addr_len;
    int n;
    n = recvfrom(sockfd, buf, sizeof(buf) - 1, 0, (struct sockaddr*)&server_addr, &addr_len);
    // n = recv(sockfd, buf, sizeof(buf), 0);

    if(n > 0){
        buf[n] = '\0';
        std::cout << "receive:" << buf << std::endl;
    }else{
        perror("error!!!");
    }

    std::cout << "finished" << std::endl;

    close(sockfd);

    return 0;
}