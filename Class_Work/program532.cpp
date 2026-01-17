/////////////////////////////////////////////////////////////////
//
//      Header file inclusion
//
/////////////////////////////////////////////////////////////////
#include<stdio.h>           //printf scanf
#include<stdlib.h>          //malloc free
#include<unistd.h>
#include<stdbool.h>         
#include<string.h>


/////////////////////////////////////////////////////////////////
//
//      User Defined Macros
//
/////////////////////////////////////////////////////////////////
#define MAXFILESIZE 50          //Maximum file size that we allowed in project

#define MAXOPENFILES 20

#define MAXINODE 5

#define READ 1
#define WRITE 2
#define EXECUTE 4

#define START 0
#define CURRENT 1
#define END 2

#define EXECUTE_SUCCESS 0


/////////////////////////////////////////////////////////////////
//
//      User Defined Structures
//
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
//
//  Structure Name :    BootBlock 
//  Description :       Holds the information to boot the OS
//
/////////////////////////////////////////////////////////////////
struct BootBlock
{
    char Information[100];
};

/////////////////////////////////////////////////////////////////
//
//  Structure Name :    SuperBlock 
//  Description :       Holds the information about File System
//
/////////////////////////////////////////////////////////////////
struct SuperBlock
{
    int TotalInodes;
    int FreeInodes;
};

/////////////////////////////////////////////////////////////////
//
//  Structure Name :    Inode 
//  Description :       Holds the information about the file
//
/////////////////////////////////////////////////////////////////
#pragma pack(1)
struct Inode
{
    char FileName[20];
    int InodeNumber;
    int FileSize;
    int ActualFileSize;
    int ReferenceCount;
    int Permission;
    char *Buffer;
    struct Inode *next;
};

typedef struct Inode INODE;
typedef struct Inode * PINODE;
typedef struct Inode ** PPINODE;
/////////////////////////////////////////////////////////////////
//
//  Structure Name :    FileTable 
//  Description :       Holds the information about opened Files
//
/////////////////////////////////////////////////////////////////
struct FileTable
{
    int ReadOffset;
    int WriteOffset;
    int Mode;
    PINODE ptrinode;
};

typedef FileTable FILETABLE;
typedef FileTable * PFILETABLE;
/////////////////////////////////////////////////////////////////
//
//  Structure Name :    UAREA
//  Description :       Holds the information about Process
//
/////////////////////////////////////////////////////////////////
struct UAREA
{
    char ProcessName[20];
    PFILETABLE UFDT[MAXOPENFILES];
};


/////////////////////////////////////////////////////////////////
//
//  Global Variable or objects used in project
//
/////////////////////////////////////////////////////////////////
BootBlock bootobj;
SuperBlock superobj;
UAREA uareaobj;

PINODE head = NULL;

/////////////////////////////////////////////////////////////////
//
//  Function Name : IntialiseUAREA
//  Description :   It is used to initialise UAREA members
//  Author :        Om Satish Mahale
//  Date :          13/01/2026
//
/////////////////////////////////////////////////////////////////
void IntialiseUAREA()
{
    strcpy(uareaobj.ProcessName,"Myexe");
    int i =0;

    for(i=0;i<MAXOPENFILES;i++)
    {
        uareaobj.UFDT[i] = NULL;
    }
        printf("Marvellous CVFS : UAREA gets initalised Sccessfully\n");

}

/////////////////////////////////////////////////////////////////
//
//  Function Name : IntialiseSuperBlock
//  Description :   It is used to initialise Super Block
//  Author :        Om Satih Mahale
//  Date :          13/1/2026
//
/////////////////////////////////////////////////////////////////
void IntialiseSuperBlock()
{
    superobj.TotalInodes = MAXINODE;
    superobj.FreeInodes = MAXINODE;

    printf("Marvellous CVFS : Super Block gets initalised Sccessfully\n");
}

/////////////////////////////////////////////////////////////////
//
//  Function Name : CreateDILB
//  Description :   It is used to create Linked list of inodes
//  Author :        Om Satih Mahale
//  Date :          13/1/2026
//
/////////////////////////////////////////////////////////////////
void CreateDILB()
{
    int i =1;
    PINODE newn = NULL;
    PINODE temp = head;

    for(i=1;i<=MAXINODE;i++)
    {
        newn = (PINODE)malloc(sizeof(INODE));

        strcpy(newn->FileName,'\0');
        newn->InodeNumber = i;
        newn->FileSize = 0;
        newn->ActualFileSize = 0;
        newn->ReferenceCount=0;
        newn->Permission=0;
        newn->Buffer=0;
        newn->next=NULL;

        if(temp==NULL)      //LL is empty
        {
            head=newn;
            temp=head;
        }
        else                //LL contains atleast 1 node
        {
            temp->next=newn;
            temp=temp->next;
        }
    }
    printf("Marvellous CVFS : DILB created Successfully\n");
}

/////////////////////////////////////////////////////////////////
//
//      Entry Point Function of project
//
/////////////////////////////////////////////////////////////////
int main()
{

    return 0;
}