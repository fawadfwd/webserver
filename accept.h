#ifndef SERVER
#define SERVER

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <malloc.h>

#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netinet/tcp.h>
#include <time.h>

#define PORT 80
void accept1(int server_fd,struct sockaddr_in address,int addrlen);

struct connection
{
	int *new_socket;
	int type;
	struct sockaddr_in address;
	char *request_line;
	int request_line_size;
	int server_fd;

};

struct lh
{
	int adid;
	char title[250];
	float price;
	char city[75];
	char state[125];
	char country[125];


};
void *handle_request(void *arg);
void *process(void *p);
int handle_process(struct connection *con_obj,char **path,char **request_type);


int get_dirs_file( char *path,char *file);
int respond_main(struct connection *con_obj,int response_type);
ssize_t sendfile(int out_fd, int in_fd, off_t *offset, size_t count);

//request type

#define TYPE_MAIN 2

#define TYPE_CSS 3

#define TYPE_QUERY 4


//reply type

#define RESPONSE_MAIN_HTML 2

#define RESPONSE_MAIN_CSS 3

#define RESPONSE_MIAN_QUERY 4

//

#define BUF_SIZE 20000

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2


//HTTP RESPONSE

#define HTTP_OK_200 200

#define CSS_PATH "/home/fawad/Desktop/C-work/css/style9.css"
#define HTML_PATH "/home/fawad/Desktop/C-work/html9.html"

#endif
