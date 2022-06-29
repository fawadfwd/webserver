#include <stdio.h>
#include "headers/accept.h"
/*void tm(char ***path)
{
	*(*(*path)+1) = '0';
}*/
//fetch null terminated string values
// void get_dirs_file(char *path,	char **dirs,char **file)
// {
// 	printf("getting directories and file for path = %s \n",path);
//
// }

int handle_process(struct connection *con_obj,char **path,char **request_type)
{
	int i=0;
	request_type[0]='\0';
	int method=0;

	while(i<(con_obj->request_line_size))
	{
		//printf("%c",(con_obj->request_line[i]));
		if(strncmp(&(con_obj->request_line[i]),"GET",3)==0)
		{

			method=3;
			*request_type=malloc(sizeof(char)*4);
			strncpy(*request_type,"GET",sizeof(char)*4);
			char *temp=con_obj->request_line+4;
			if(strncmp(temp,"/ ",2)==0)
			{
				*path=malloc(sizeof(char)*strlen("html9.html"));
				strncpy(*path,"html9.html",strlen("html9.html")+1);


				break;
			}
			if(strncmp(temp,"/add?",sizeof(char)*5)==0)
			{
				int j=0;
				while(j<strlen(temp))
				{
					if(temp[j]==' ')
					{
						break;
					}
					j++;
				}
				*path =malloc(sizeof(char)*j+1);
				strncpy(*path,temp,sizeof(char)*j);

				(*(path+j))='\0';
				//tm((&path));
				//printf("hello line now -------> %s\n",*path);

				break;


			}
			if(strncmp(temp,"/css/",sizeof(char)*5)==0)
			{
				int j=0;

				while(j<strlen(temp))
				{
					if(temp[j]==' ')
					{
						break;
					}

					j++;
				}
				*path=malloc(sizeof(char)*j+1);
				strncpy(*path,temp,sizeof(char)*j);
				(*(path+j))='\0';
				//printf("hello line now -------> %s\n",*path);
			}			//return strlen("GET");
		}
		i++;
	}
	printf("data in line now -------> path = %s request_type = %s\n",*path,*request_type);
	if(method==0)
	return 0;
	return strlen(*request_type);
}


void *process(void *p)
{	//printf("hello in process thread\n");
	int r=0;
	struct connection *con_obj=malloc(sizeof(struct connection));
	if (con_obj != NULL)
	{
		printf("\n\n");
		printf("------------------------------------------------------------------------------------\n");
		con_obj=(struct connection *)p;
		//printf("In process thread | new_socket = %d\n",*(con_obj->new_socket));

		//printf("j = %d | request_line = %s\n",(con_obj->request_line_size),(con_obj->request_line));
		char *path=NULL;
		char*request_type=NULL;

		//path will be allocated and get null ['\0'] terminated in handle_process
		//printf("before handle_process\n");
		int request_type_size=handle_process(con_obj,&path,&request_type);
		if(request_type_size==0)
		{
			//different request_type
			close(*(con_obj->new_socket));
			if(path!=NULL)
			free(path);
			if(request_type!=NULL)
			free(request_type);
			free(con_obj);
			return (void*)0;
		}
   // printf("after handle_process\n" );
		if(path!=NULL)
		{
			//printf("in handle_process  Path Len = %zu Request Path = '%s'\n",strlen(path),path);
		}

		if(request_type!=NULL)
		{
			//printf("in handle_process  Type Len = %zu Request Type = '%s'\n",strlen(request_type),request_type);
		}
		if(path!=NULL && request_type!=NULL)
		{
			if(strncmp(request_type,"GET",request_type_size)==0)
			{
				//printf("inside GET in process func\n");
				char *dirs;
				char *file;
				file=malloc(sizeof(char)*strlen(path));

        // get_dirs_file: returns '/ ' for TYPE_MAIN | 'style9.css' for TYPE_CSS | 'title=&price=' for TYPE_QUERY
				r=	get_dirs_file(&path[0],file);//get null terminated string values
				//printf("\n\npath to follow -- = 'path = %s' 'file = %s'\n\n",path,file);
				if(r == TYPE_MAIN)
				{
					respond_main(con_obj,RESPONSE_MAIN_HTML);
				}
				else if(r== TYPE_CSS)
				{
					respond_main(con_obj,RESPONSE_MAIN_CSS);

				}
				else if(r=TYPE_QUERY)
				{
					respond_main(con_obj,RESPONSE_MIAN_QUERY);
				}
				free(file);
			}
		}

		close(*(con_obj->new_socket));
		free(con_obj);

		printf("------------------------------------------------------------------------------------\n");
	}
	else
	{
		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		printf("No space for malloc on heap\n");
	}

	return (void *)0;
}
