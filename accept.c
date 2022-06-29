
#include "headers/accept.h"
#define BUFFER 1024+1
int check_if_t(char *buffer,int valread,int *f)
{
	int i=0;
	while(i<BUFFER)
	{
		printf("%c",*(buffer+i));
		if(*(buffer+i)=='\r')
		{
				*f=1;
			printf("***************************************************************************\n");

			return i;
		}
		i++;
	}
	return i;

}

void* handle_request(void *arg)
{

	//printf("\n");
	struct connection *con_obj=malloc(sizeof(struct connection));


	if(con_obj!=NULL)
	{
		//con_obj->server_fd=(int*)arg;
		con_obj=(struct connection *)arg;

		//printf("new_socket get thread : %d\n",*(con_obj->new_socket));
		char *str_array=NULL;
		str_array=malloc(BUFFER+1);
		str_array[0]='\0';
		char buffer[BUFFER] = {0};
		int x=0;
		int check_tp=0;
		int j=0;
		while(x<BUFFER)
		{
			int valread=read(*(con_obj->new_socket),&buffer[x],BUFFER);;
		//	printf("Socket Buffer read valread = %d \n %.*s",(valread-1),(valread-1),buffer);			
			printf("________________________________________________\n%s\n",buffer);	
			int f=0;

			check_tp=check_if_t(buffer,(BUFFER),&f);
			//printf("check_tp = %d\n",check_tp);

			if(f==1)
			{

				strncpy(&str_array[j],&buffer[j],check_tp);
				j=j+check_tp;
				str_array[j]='\0';
				//printf("--->\n");
				//printf("j = %d\n",j);
				//printf("%.*s\n",j,str_array);
				break;
			}
			if(str_array!=NULL)
			strncpy(&str_array[j],&buffer[j],check_tp);
			j=j+check_tp;

			x=x+check_tp;

		}
		x=0;


		if(str_array!=NULL)
		{
			if(strlen(str_array)>0)
				{

					//printf("printing first line = %s | length = %zu j = %d\n ",str_array,strlen(str_array),j);
					pthread_t thread_process;
					con_obj->request_line=malloc(sizeof(char)*j);
					if(con_obj->request_line==NULL)
					{
						while(1)
						{
								printf("handle_request -- heap problem at line 80: con_obj->request_line=malloc(sizeof(char)*j); \n");
						}
					}

					if(j>=BUFFER)
					{
						free(con_obj->request_line);
					//  printf("check line 89 handle_request\n");
						//exit(0);
						j=BUFFER-1;
						con_obj->request_line[j]='\0';
						close(*(con_obj->new_socket));
						free(con_obj);
						return (void*)0;



					}
					memcpy((con_obj->request_line),str_array,sizeof(char)*j);
					con_obj->request_line_size=j;
					pthread_create(&thread_process, NULL, process, (void *)con_obj);


				}
			else{
				//printf("str_array length not found = %zu\n",strlen(str_array));
			}
			free(str_array);
			//

		}
	}
	else
	{
		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		printf("No space for malloc on heap\n");
	}
	return (void*)0;

}

void accept1(int server_fd,struct sockaddr_in address,int addrlen)
{


	while(1)
	{
		int new_socket;
		if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
		(socklen_t*)&addrlen))<0)
		{
			perror("accept");
			exit(EXIT_FAILURE);
		}

		//printf("new_socket just created = %d\n",new_socket);
		pthread_t thread_get;

		struct connection *con_obj=malloc(sizeof(struct connection));
		if(con_obj!=NULL)
		{
			con_obj->new_socket=&new_socket;
			con_obj->address=address;
			//printf("%d hello\n",*(con_obj->new_socket));


			pthread_create(&thread_get, NULL, handle_request, (void *)con_obj);
		}
		else
		{
			printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
			printf("No space for malloc on heap\n");

		}
		int state = 0;
	 	if(setsockopt(new_socket, IPPROTO_TCP, TCP_CORK, &state, sizeof(state)))
	 	{
	 		printf("TCP CORK\n");
	 	}

		state = 1;
	 	if(setsockopt(new_socket, IPPROTO_TCP, TCP_CORK, &state, sizeof(state)))
	 	{
	 		printf("TCP CORK\n");
	 	}
		//printf("After Thread creation\n");
	}

}
