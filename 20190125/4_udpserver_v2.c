#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{	
	//AF_INET:ipv4
	//不可靠传输:SOCK_DGRAM   --> udp
	//0表示使用默认的传输协议
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == sockfd)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in servaddr;
	servaddr.sin_family = AF_INET;   //使用ipv4协议
	//将点分十进制字符串表示的ip转换成整型存放
	//servaddr.sin_addr.s_addr = inet_addr("192.168.1.92");
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//将本地字节序转换成网络字节序
	servaddr.sin_port = htons(8888);
	memset(servaddr.sin_zero, 0, 8);

	bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	
	struct sockaddr_in clientaddr;
	char caMsg[64] = {'\0'};
	int iLen = 0;
	while (1)
	{
		memset(caMsg, 0, sizeof(caMsg));
		recvfrom(sockfd, caMsg, sizeof(caMsg), 0
			   , (struct sockaddr *)&clientaddr, &iLen);
		printf("ip:%s, port:%d, msg --> %s\n"
			   , inet_ntoa(clientaddr.sin_addr)
			   , ntohs(clientaddr.sin_port)
			   , caMsg);

		strcat(caMsg, " 老铁, 6666 --> ^_^");
		sendto(sockfd, caMsg, strlen(caMsg), 0
			   , (struct sockaddr *)&clientaddr, iLen);
	}


	return 0;
}
