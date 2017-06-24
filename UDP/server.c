#include <sys/types.h>          /* socket ,bind, listen */
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

/*socket 
 *bind
 *sendto/recvfrom
 */
#define SERVER_PORT 8888

int main(int argc, char const *argv[])
{
	int serv_sockfd;
	int client_sockfd;
	struct sockaddr_in tsocketserveraddr;
	struct sockaddr_in tsocketclientaddr;
	int ret_val;
	int addrlen;

	int recvlen;
	char ucrecvbuf[1000];
	
	serv_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	if (serv_sockfd == -1) {
		printf("socket 错误！\n");
		return -1;
	}

 	tsocketserveraddr.sin_family	  = AF_INET;
 	tsocketserveraddr.sin_addr.s_addr = INADDR_ANY;
	tsocketserveraddr.sin_port	 	  = htons(SERVER_PORT);	
 	memset( tsocketserveraddr.sin_zero, 0, 8);

	ret_val = bind(serv_sockfd, (const struct sockaddr *) &tsocketserveraddr, sizeof(struct sockaddr));
	if (ret_val == -1) {
		printf("bind 错误！\n");
		return -1;
	}
	
	while(1) {
		addrlen = sizeof(struct sockaddr);
		recvlen = recvfrom(serv_sockfd, ucrecvbuf, 999, 0, (struct sockaddr *)&tsocketclientaddr, &addrlen);
		if (recvlen >0) {
			ucrecvbuf[recvlen] = '\0';
			printf("client:%s message:%s\n",inet_ntoa(tsocketclientaddr.sin_addr), ucrecvbuf);
		}

	}

	close(serv_sockfd);
	return 0;
}