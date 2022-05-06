#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h> 
#include <stdio.h>        



int main(int argc, char **argv){

  struct stat mystat; 
  stat(argv[1],&mystat); // cal stat and populate struct mystat

  if( argv[1]==NULL)
  {
      printf("File Does not exist");
      return -1;
  }

  printf("File  or Directory requested:  %s\n", (argv[1]));
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