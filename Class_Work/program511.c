//Data override

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
    int fd=0;
    int iRet=0;
    char Arr[]="Pune";

    fd = open("JanuaryX.txt",O_RDWR);

    if(fd == -1)
    {
        printf("Unable to Open File\n");
    }   
    else
    {
        printf("File get's Successfully Open with FD : %d\n",fd);
        iRet = write(fd,Arr,3);
        printf("%d bytes gets successfully written into the file : \n",iRet);
        close(fd);
    } 
    
    return 0;
}