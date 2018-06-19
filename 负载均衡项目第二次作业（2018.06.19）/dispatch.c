#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
const char * IP = "127.0.0.1";
int PORT = 7800;
void send_response(int fd, int code, const char *url) 
{
	char buf[1024] = "";
	char scode[16] = "";
	char status[32] = "Moved Permanently";
	// response proto
	strcat(buf, "HTTP/1.0");
	sprintf(scode, "%d", code);
	strcat(buf, " ");
	strcat(buf, scode);
	strcat(buf, " ");
	strcat(buf, status);
	strcat(buf, "\r\n");// server msg
	strcat(buf, "Server: ");
	strcat(buf, "Hgg-server");
	strcat(buf, "\r\n");
	// Location
	strcat(buf, "Location: ");
	strcat(buf, url);
	strcat(buf, "\r\n");
	strcat(buf, "\r\n");
	int res = send(fd, buf, strlen(buf), 0);
	printf("send status %d\n", res);
} 
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
		assert (c != -1);
		char buf[128] = "";
		int size = recv(c, buf, 127, 0);
		printf("%s", buf);
		fflush(stdout);
		int code = 301;
		const char *url = "http://127.0.0.1:8800/";
		send_response(c, code, url);
		close(c);
	} 
	close(sockfd);
	return 0;
}