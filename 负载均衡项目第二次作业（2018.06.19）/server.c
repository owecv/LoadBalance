#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
const char * IP = "127.0.0.1";
int PORT = 8800;
int main() 
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	assert(sockfd != -1);
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(IP);
	server_addr.sin_port = htons(PORT);
	int res = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(struct
	sockaddr_in));
	assert (res != -1);
	res = listen(sockfd, 5);
	assert (res != -1);
	struct sockaddr_in addr;
	int len = sizeof(addr);
	memset(&addr, 0, len);
	while (true) 
	{
		int c = accept(sockfd, (struct sockaddr*)&addr, &len);
		printf("Get one link\n");
		assert (c != -1);
		char buf[128] = "";
		while (true) 
		{
			int size = recv(c, buf, 127, 0);
			if (size == 0) 
			{
				break;
			}
			else 
			{
				printf("%s", buf);
				fflush(stdout);
				memset(buf, 0, strlen(buf));
			}
		}
		close(c);
	} 
	close(sockfd);
	return 0;
}
