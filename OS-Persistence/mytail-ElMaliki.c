#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h> 
#include <stdio.h>  
#include <stdlib.h>

#include <string.h>






int main(int argc, char **argv)
{


  
if ( argc!=3) // ensure right format in inserted for arguments 
{
  printf("Wrong format mate, please input valid paramters");
  return -1;
}

int n; // line to start reading from 
char *placeholder; 
placeholder=argv[1];
placeholder++;
n=atoi(placeholder); //  cast string to int type

FILE *file;
file=fopen(argv[2],"r"); 

if(file==NULL){ printf("couldn't open file \n"); return -2;}

char c; 
int lines=0;

while (!feof(file)){
    c = fgetc(file);
    if(c == '\n'){
      lines++; 
    }
  }

// total number of lines counter in file, time to close it 
fclose(file);

int directacess=lines-n; // mumber of line desired to start printing 


file = fopen(argv[2], "r"); // open file again 

int i=0; // loop to skip all the lines that we do not need 
while (i < directacess){
    c = fgetc(file);
    if(c == '\n'){
      i++;
    }
  }
  // fgets pointer is now pointing to the first character in the desired line, we need to start printing

  while (!feof(file)){
    c = fgetc(file);
    printf("%c", c);  
    
    
      
    
  }
  printf("\n");
  
  fclose(file); // close file
}









