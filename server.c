#include "headers/accept.h"

int main()
{
	pthread_t thread_css;
	pthread_t thread_html;
	pthread_t thread_get;
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	char *hello = "Hello from server";
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("socket failed\n");
		exit(EXIT_FAILURE);
	}
	printf("server_fd = %d\n",server_fd);
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
			                          &opt, sizeof(opt)))
	{
		printf("setsockopt\n");
		exit(EXIT_FAILURE);
 }

 int state = 1;
	if(setsockopt(server_fd, IPPROTO_TCP, TCP_CORK, &state, sizeof(state)))
	{
		printf("TCP CORK\n");
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );
    // Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr *)&address,
		                 sizeof(address))<0)
	{
		printf("bind failed\n");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0)
	{
		printf("listen\n");
		exit(EXIT_FAILURE);
	}
	accept1(server_fd,address,addrlen);
	return 0;





}
