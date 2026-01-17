#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
    int fd=0;
    int iRet = 0;
    char Buffer[100] = {'\0'};

    fd=open("JanuaryX.txt",O_RDONLY);
    if(fd != -1)
    {
        printf("File get's opened with fd : %d\n",fd);
        iRet = read(fd,Buffer,11);
        printf("Data from file is : %s\n",Buffer);
    }
    return 0;
}