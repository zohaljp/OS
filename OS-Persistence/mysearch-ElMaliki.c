#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

#ifndef MAX_BUF
#define MAX_BUF 200
#endif

// this code is based from the lecture code provided in class, little modification was done to the base recursion case to satisfy assignment requirment 

typedef struct dirent Dir;

char* newString(int length)
{
    return (char*)malloc(length*sizeof(char));
}
char* getFolderName(char* parentFolder, char* childFolder)
{
    char* name=newString(strlen(parentFolder)+1+strlen(childFolder));
    sprintf(name, "%s/%s", parentFolder, childFolder); return name;
}
void listFolder(char* pathName, char* folderName, int indent)

{

    printf("%*s%s\n", indent*4, " ", folderName); Dir* dir;
    DIR* rootDir=opendir(pathName); if(!(rootDir=opendir(folderName)))return; // return when reach the root again- base case
    for(dir=readdir(rootDir); dir!=NULL; dir=readdir(rootDir))
{
        if(strcmp(dir->d_name, ".")==0||strcmp(dir->d_name, "..")==0)continue;
        listFolder(getFolderName(pathName, dir->d_name), dir->d_name, 
        indent+1);
}
    closedir(rootDir); 
}
int main(int argc, char *argv[])
{
    char path[MAX_BUF];

    getcwd(path, MAX_BUF);

if( argc==1) // no arguments, use current directory 
{
    printf(" Current working Directory: %s", path);
    listFolder(".", ".", 0);
}
if (argc==2) // go to directory specified by argument
{   printf(" Current working Directory: %s", path);
    listFolder(".", argv[1], 0);
}


}



