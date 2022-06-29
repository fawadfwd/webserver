

#include <fcntl.h>
#include  <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "headers/accept.h"
#include <sys/types.h>




#include <stdlib.h>



#include <errno.h>

#include <unistd.h>
#include <fcntl.h>
#include <time.h>
int get_file_type(char *path,char *file)
{
  int i=0;
  printf("%zu \n",strlen(path));
  while(i<strlen(path))
  {
    if(path[i]=='?')
    {
      //query string
      int j=0;
      strcpy(file,&path[i+1]);
      file[strlen(path)]='\0';

      return TYPE_QUERY;
    }
    if(strncmp(&path[i],"html9.html",strlen(path))==0)
    {

      strcpy(file,"/ ");
      return TYPE_MAIN;
    }
    if(strncmp(&path[i],".css",4)==0)
    {
      int j=strlen(path);
      while(j>0)
      {
        if(path[j]=='/')
        {
          strcpy(&file[0],&path[j]);
          break;
        }

        j--;
      }
    //  file[j]='\0';
      return TYPE_CSS;
    }
    i++;

  }
  return 0;

}
/*<-whether found return 1; else 0;*/
int getfile_data(char *path,char *file)
{


  int ret=get_file_type(path,file);
  printf("request found !!! %s\n",file);
  if(ret==TYPE_MAIN)
  {
    printf("responding with main page\n" );
    return TYPE_MAIN;

  }
  else if(ret ==TYPE_CSS)
  {
    printf("responding with css\n");
    return TYPE_CSS;
  }
  else if(ret ==TYPE_QUERY)
  {
    printf("finally saving data and redirecting user to main with message\n" );
    return TYPE_QUERY;
  }
  else{
    return 0;
  }




  //strncpy(**file,"fwd",4);

}

int get_dirs_file( char *path,char *file)
{
  printf("in get_dirs_file");
  int ret=getfile_data(path,file);
  return ret;


}

  //Gettting file
