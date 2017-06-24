#include <sys/types.h>          /* socket ,bind, listen */
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

/*socket 
 *
 *
 *
 */
#define SERVER_PORT 8888
#define BACKLOG 10
int main(int argc, char const *argv[])
{
	int isocketserver;
	int isocketclient;
	int iclientnum = -1;
	struct sockaddr_in tsocketserveraddr;
	struct sockaddr_in tsocketclientaddr;
	int iret;
	int iaddrlen;

	int rcevlen;
	char ucrecvbuf[1000];

	signal(SIGCHLD, SIG_IGN);
	
	isocketserver = socket(AF_INET, SOCK_STREAM, 0);
	
	if (isocketserver == -1) {
		printf("socket 错误！\n");
		return -1;
	}

 	tsocketserveraddr.sin_family	  = AF_INET;
 	tsocketserveraddr.sin_addr.s_addr = INADDR_ANY;
	tsocketserveraddr.sin_port	 	  = htons(SERVER_PORT);	
 	memset( tsocketserveraddr.sin_zero, 0, 8);

	iret = bind(isocketserver, (const struct sockaddr *) &tsocketserveraddr, sizeof(struct sockaddr));
	if (iret == -1) {
		printf("bind 错误！\n");
		return -1;
	}

	iret = listen(isocketserver, BACKLOG);
	if (iret == -1)
	{
		printf("listen 错误！\n");
		return -1;
	}

	while(1) {
		iaddrlen = sizeof(struct sockaddr);
		isocketclient =  accept(isocketserver, (struct sockaddr *) &tsocketclientaddr, &iaddrlen);
		if (isocketclient != -1) {
			iclientnum++;
			printf("客户端已连接 %d : %s\n", iclientnum, inet_ntoa(tsocketclientaddr.sin_addr));
			if (!fork()) {
				/* 子进程，fock父进程*/
				while (1) {
					/* 接收客户端发来的数据并显示 */
					rcevlen = recv(isocketclient, ucrecvbuf, 999, 0);
					if (rcevlen <=0 ) {
						close(isocketclient);
						return -1;
					} else {
						ucrecvbuf[rcevlen] = '\0';
						printf("%d 客户端消息：%s\n", iclientnum, ucrecvbuf);
					}
				}
			}

		}
	}

	close(isocketserver);
	return 0;
}