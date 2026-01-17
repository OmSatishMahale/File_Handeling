#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
    int fd=0,iRet = 0;

    char Fname[100]={'\0'};

    printf("Enter the name of File : \n");
    scanf("%s",Fname);

    fd=open(Fname,O_RDWR);

    if(fd!=-1)
    {
        printf("File Successfully opened\n");
        close(fd);
    }
    else
    {
        printf("No such file exist\n");
    }
    
    
    return 0;
}