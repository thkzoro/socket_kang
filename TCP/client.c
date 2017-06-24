#include <sys/types.h>          /* socket ,bind, listen */
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

#define SERVER_PORT 8888
int main(int argc, char const *argv[])
{
	int isocketclient;
	struct sockaddr_in tsocketserveraddr;

	int iret;
	char ucsendbuf[1000];
	int isendlen;
	if (argc != 2) {
		printf("usage:\n");
		printf("%s <server_ip>\n", argv[0]);
		return -1;
	}

	isocketclient = socket(AF_INET, SOCK_STREAM, 0);
	tsocketserveraddr.sin_family		=AF_INET;
	tsocketserveraddr.sin_port			=htons(SERVER_PORT);
	/* return 1 if the supplied string was successfully interpreted, 
	 * or 0 if the string is invalid (errno is not set on error).*/
	iret = inet_aton(argv[1], &tsocketserveraddr.sin_addr);
	if (iret ==  0)	{
		printf("服务器ip,无效\n");
		return -1;
	}
	memset(tsocketserveraddr.sin_zero, 0 ,8);

	iret = connect(isocketclient, (const struct sockaddr *)&tsocketserveraddr, sizeof(struct sockaddr));
	if (iret == -1) {
		printf("连接错误！\n");
		return -1;
	}

	while (1) {
		if (fgets(ucsendbuf, 999, stdin)) {
			isendlen = send(isocketclient, ucsendbuf, strlen(ucsendbuf), 0);
			if (isendlen <= 0) {
				close(isocketclient);
				return -1;
			}
		}
	}
	return 0;
}