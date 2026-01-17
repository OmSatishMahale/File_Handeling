#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
    int fd=0;

    //O_RDONLY      O_WRONLY        O_RDWR      O_TRUNC       O_CREAT       O_APPEND
    fd = open("LB.txt",O_RDWR);

    if(fd == -1)
    {
        printf("Unable to Open File\n");
    }   
    else
    {
        printf("File get's Successfully Open with FD : %d\n",fd);
    } 
    
    return 0;
}