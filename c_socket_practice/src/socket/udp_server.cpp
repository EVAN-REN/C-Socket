#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#define SERVER_PORT 50001
#define SERVER_IP "127.0.0.1"

int main()
{
    struct sockaddr_in server_addr;

    int server_sock;
    server_sock = socket(AF_INET, SOCK_DGRAM, 0);

    if(server_sock < 0){
        fprintf(stderr, "create socket error, reason: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);
    server_addr.sin_port = htons(SERVER_PORT);

    if(bind(server_sock, (struct  sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        perror("Bind failed!");
        exit(EXIT_FAILURE);
    }else{
        struct sockaddr_in local_addr;
        socklen_t addr_len = sizeof(local_addr);
        if (getsockname(server_sock, (struct sockaddr*)&local_addr, &addr_len) == -1) {
            perror("Getsockname failed");
            close(server_sock);
            return 1;
        }
        printf("Socket bound to port: %d\n", ntohs(local_addr.sin_port));
    }


    int waiting = 1;
    while(waiting){
        struct sockaddr_in client_addr;
        
        // receive the data from client
        char buf[1024];
        socklen_t addr_len;
        int len;
        len = recvfrom(server_sock, buf, sizeof(buf) - 1, 0, (struct sockaddr*)&client_addr, &addr_len);
        buf[len] = '\0';
        std::cout << "receive[" << len << "]: " << buf << std::endl;

        //process the data
        for(int i = 0; i < len; i++){
            buf[i] = toupper(buf[i]);
        }

        //response to the client
        len = sendto(server_sock, buf, strlen(buf), 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
        std::cout << "write finished. len:" << len << std::endl;
         
    }
    close(server_sock);
    return 0;
}