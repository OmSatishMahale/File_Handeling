#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
    int fd=0;
    fd = creat("LB.txt",0777);

    if(fd == -1)
    {
        printf("Unable to create File\n");
    }   
    else
    {
        printf("File get's Successfully created with FD : %d\n",fd);
    } 
    
    return 0;
}