//for fullfilling user requests
#include <stdio.h>
#include "headers/accept.h"
int respond_main(struct connection *con_obj,int response_type)
{
  char *html_header = "HTTP/1.1 200 Okay\r\nContent-Type: text/html; charset=ISO-8859-4 \r\n\r\n";
  char *css_header = "HTTP/1.1 200 Okay\r\nContent-Type: text/css\r\n\r\n";
  char *data_saved_message="HTTP/1.1 200 Okay\r\nContent-Type: text/html; charset=ISO-8859-4 \r\n\r\n<html><body>add posted. will appear in 24 hours on listhell <a href=\"http://listhell.com/\">go to main page</a></body></html>";
  if(response_type==RESPONSE_MAIN_HTML)
  {
    struct stat sb_html;
    send(*(con_obj->new_socket) , html_header , strlen(html_header) , 0 );
    sleep(10);
    int fd_in_html=open(HTML_PATH,O_RDONLY);
    const char* filename_html=HTML_PATH;
    if(fd_in_html!=-1)
    {
      if (stat(filename_html, &sb_html) == -1)
  		{
  			printf("stat error %d\n",errno);

  		}
      int x3=sendfile(*(con_obj->new_socket),fd_in_html,0,sb_html.st_size);
      close(fd_in_html);

      return HTTP_OK_200;

  }


  }
  else if(response_type==RESPONSE_MAIN_CSS)
  {
    struct stat sb_css;
    int fd_in_css=open(CSS_PATH,O_RDONLY);
    if(fd_in_css!=-1)
    {
      const char* filename_css=CSS_PATH;
      if (stat(filename_css, &sb_css) == -1)
			{
				printf("stat error %d\n",errno);
				exit(EXIT_FAILURE);
			}
      sendfile(*(con_obj->new_socket),fd_in_css,0,sb_css.st_size);
      close(fd_in_css);
      return HTTP_OK_200;


    }

  }
  else if(response_type==RESPONSE_MIAN_QUERY)
  {
    //
      send(*(con_obj->new_socket) , data_saved_message , strlen(data_saved_message) , 0 );
      //send(*(con_obj->new_socket) , data_saved_message , 200 , 0 );
      //send(*(con_obj->new_socket) , data_saved_message , 200 , 0 );
    //data_saved_message
    printf("data saved\n");
    return HTTP_OK_200;

  }
  return 0;
}
