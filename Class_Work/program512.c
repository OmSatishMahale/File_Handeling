#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
    int fd=0;
    int iRet=0;
    char Arr[]="Maharashtra";

    fd = open("JanuaryX.txt",O_RDWR | O_APPEND);

    if(fd == -1)
    {
        printf("Unable to Open File\n");
    }   
    else
    {
        printf("File get's Successfully Open with FD : %d\n",fd);
        iRet = write(fd,Arr,11);
        printf("%d bytes gets successfully written into the file : \n",iRet);
        close(fd);
    } 
    
    return 0;
}