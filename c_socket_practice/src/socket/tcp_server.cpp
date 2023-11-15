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
    //sockaddr_in是一个存ipv4信息的结构体,sockaddr是一个存ipv4/ipv6的结构体
    struct sockaddr_in server_addr;

    int server_sock;
    //create a socket(domain, type, protocol)
    //domain:AF_INET/AF_INET6/AF_UNIX本地协议，使用在unix和linux系统上，一般客户端和服务器在同一台机器上是用
    //type:SOCK_STREAM(TCP)/SOCK_DGRAM(UDP)/SOCK_SEQPACKET(双线路可靠连接)/SOCK_RAW(单一网络访问，如ICMP/ping)/SOCK_RDM
    //protocol:default is 0，表示跟type一致，也可以显式写出：IPPROTO_TCP/IPPROTO_UDP
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    //if failed
    if(server_sock < 0){
        perror("Socket creation failed");
        //stderr是标准错误流，类似stdout，strerror可以将errno（错误号）转化为错误信息字符串
        fprintf(stderr, "create socket error, reason: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    //clear the address and write down the IP address and port number
    bzero(&server_addr, sizeof(server_addr));
    //choose protocol IPV4
    server_addr.sin_family = AF_INET;
    //choose IP address, inet_addr将点分十进制的ip地址转换为对应32位网络字节序(ipv4)的整数，返回内容可能造成误解（不推荐）
    // server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);
    //choose port number，htonl将主机字节序（整形数）转换为网络字节序,ntohl正好相反,l代表long（处理32位无符号整数，如ip地址）,htons中s代表short（处理16位无符号整数，如port）
    server_addr.sin_port = htons(SERVER_PORT);

    //bind Address message to socket,success return 0,fail return -1
    if(bind(server_sock, (struct  sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        perror("Bind failed!");
        exit(EXIT_FAILURE);
    }else{
        struct sockaddr_in local_addr;
        socklen_t addr_len = sizeof(local_addr);
        if (getsockname(server_sock, (struct sockaddr*)&local_addr, &addr_len) == -1) {
            //perror将自定义错误信息输出stderr
            perror("Getsockname failed");
            close(server_sock);
            return 1;
        }
        printf("Socket bound to port: %d\n", ntohs(local_addr.sin_port));
    }

    //begin listening, backlog allow 64 clients to connect(总的还是会受系统影响)
//查看系统默认backlog, cat /proc/sys/net/ipv4/tcp_max_syn_backlog
//改变系统限制的backlog大小, vim /etc/sysctl.conf
//最后加入: net.core.somaxconn = 1024
//net.ipv4.tcp_max_syn_backlog = 1024
//保存后执行: sysctl -p
    listen(server_sock, 64);
 
    std::cout << "Waiting client to connect..." << std::endl;

    int waiting = 1;
    while(waiting){
        struct sockaddr_in client_addr;
        //socklen_t present the length of sockaddr_in type 
        socklen_t client_addr_len;

        //create a client to receive the connection
        int client_sock;

        //accept all the connection,failed return -1,没有client连接的话，一直处于主阻塞状态
        //第三个参数传入socklen_t类型指针，需要能提供缓冲区大小（sockaddr_in大小），传处后是客户端实际的大小
        client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_addr_len);

        if(client_sock < 0){
            perror("client accept failed!");
        }

        char client_ip[64];
        //inet_ntop将ipv4/6网络字节序转为十进制ip地址（字符串）,inet_pton正好相反
        const char *ip_trans = inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, client_ip, sizeof(client_ip));
        
        //client connect successful
        if(ip_trans != NULL){
            std::cout << "client ip:" << client_ip << "  port:" << ntohs(client_addr.sin_port) << std::endl;
        }else{
            perror("client inet_ntop failed");
        }

        // receive the data from client
        char buf[256];
        int len;
        len = read(client_sock, buf, sizeof(buf) - 1);
        buf[len] = '\0';
        std::cout << "receive[" << len << "]: " << buf << std::endl;

        //使用recv接受数据，第四个参数用于控制接收行为，如是否阻塞
        //success return length, client close return 0, fail return -1
        //len = recv(client_sock, buf, sizeof(buf), 0);

        //process the data
        for(int i = 0; i < len; i++){
            buf[i] = toupper(buf[i]);
        }

        //response to the client
        len = write(client_sock, buf, len);

        //使用send发送数据
        // len = send(client_sock, buf, strlen(buf), 0);
        std::cout << "write finished. len:" << len << std::endl;

        //close socket
        close(client_sock);
         
    }
    close(server_sock);
    return 0;
}
