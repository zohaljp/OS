#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h> 
#include <stdio.h>  
#include <stdlib.h>
#include <dirent.h>
#include <string.h>




void printfiledetails(char *filename) // use previous code from my stat-ElMaliki 
{

  struct stat mystat;
  stat(filename, &mystat);

  printf("File  or Directory requested:  %s\n", filename);
  printf("File Size:  %d Bytes\n",mystat.st_size);
  printf("Number of Blocks Allocated:  %d\n",mystat.st_blocks);
  printf("Number of Links:  %d\n",mystat.st_nlink);


  printf("File Permissions:   ");
  printf( (S_ISDIR(mystat.st_mode))  ? "d" : "-"); //is it a directory? 
  printf( (mystat.st_mode & S_IRUSR) ? "r" : "-"); // can user read
  printf( (mystat.st_mode & S_IWUSR) ? "w" : "-"); // can user write
  printf( (mystat.st_mode & S_IXUSR) ? "x" : "-");// can user execute?
  printf( (mystat.st_mode & S_IRGRP) ? "r" : "-"); // can group read?
  printf( (mystat.st_mode & S_IWGRP) ? "w" : "-");// can group write
  printf( (mystat.st_mode & S_IXGRP) ? "x" : "-");// can group execute?
  printf( (mystat.st_mode & S_IROTH) ? "r" : "-"); // can others read?
  printf( (mystat.st_mode & S_IWOTH) ? "w" : "-"); // can others write?
  printf( (mystat.st_mode & S_IXOTH) ? "x" : "-"); // can others execute?
  printf("\n");
  

  printf("File Inode: %u\n",mystat.st_ino);



}








int main(int argc, char **argv)
{

// get directory names and paramters
DIR *dir;
if (argc==1) // no arguments
{
  dir = opendir(".");
}

if( argc==2){ // 1 argument 

    if (strcmp(argv[1], "-l") != 0){
      dir = opendir(argv[1]);
      }
    if(strcmp(argv[1], "-l") == 0 )
    {
      dir = opendir(".");

    }
      
}

if( argc==3) // 2 arguments 
{
  if (strcmp(argv[1], "-l") == 0){
      dir = opendir(argv[2]);
      }
  if (strcmp(argv[1], "-l") != 0){
    printf("Wrong format mate, please rerun and enter valid arguments");


}
}

// read directories and display info accordingly 
  

struct dirent* dirnt=readdir(dir);

for(; dirnt!= NULL; dirnt=readdir(dir))
{

    if( argc==1) // no arguments
    {
      printf("%s\n", dirnt->d_name);

    }

    if( argc==2) // 1 argument
    {
       if (strcmp(argv[1], "-l") == 0){
        printfiledetails(dirnt->d_name);
       }
       else
        printf("%s\n", dirnt->d_name);

    }

    if( argc==3) // 2 arguments 
    {
       if (strcmp(argv[1], "-l") == 0){
          printfiledetails(dirnt->d_name);
          }
       else 
       printf("%s\n", dirnt->d_name);

    }




dirnt = readdir(dir);

}

close(dir);


}