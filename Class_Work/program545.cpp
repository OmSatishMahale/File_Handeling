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
    strncpy(uareaobj.ProcessName, "Myexe", sizeof(uareaobj.ProcessName)-1);
    uareaobj.ProcessName[sizeof(uareaobj.ProcessName)-1] = '\0';
    int i =0;

    for(i=0;i<MAXOPENFILES;i++)
    {
        uareaobj.UFDT[i] = NULL;
    }
        printf("Marvellous CVFS : UAREA gets initalised Sccessfully\n");
        fflush(stdout);

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

        strcpy(newn->FileName,"\0");
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
//  Function Name : StartAuxillaryDataInitialisation
//  Description :   It is used to call all such function which are used to initialise Auxillary data
//  Author :        Om Satish Mahale
//  Date :          13/01/2026
//
/////////////////////////////////////////////////////////////////
void StartAuxillaryDataInitialisation()
{
    strcpy(bootobj.Information,"Booting process of Marvellous CVFS is Done");
    printf("%s",bootobj.Information);

    IntialiseSuperBlock();
    CreateDILB();
    IntialiseUAREA();
    printf("Marvellous CVFS : Auxillary data initialised Successfully\n");
}

/////////////////////////////////////////////////////////////////
//
//  Function Name : DisplayHelp
//  Description :   It is used to Display the help page
//  Author :        Om Satish Mahale
//  Date :          14/01/2026
//
/////////////////////////////////////////////////////////////////
void DisplayHelp()
{
    printf("-------------------------------------------------------\n");
    printf("--------------- Marvellous CVFS Help Page--------------\n");
    printf("-------------------------------------------------------\n");

    printf("man     : It is used to Display Manual Page\n");
    printf("clear   : It is used to clear the terminal\n");
    printf("create  : It is used to create new File\n");
    printf("write   : It is used to write the data into the File\n");
    printf("read    : It is used to read the data from the File\n");
    printf("stat    : It is used to Display Statistical Information\n");
    printf("unlink  : It is used to delete the file\n");
    printf("exit    : It is used to terminate Marvellous CVFS\n");

    printf("-------------------------------------------------------\n");
}


/////////////////////////////////////////////////////////////////
//
//      Entry Point Function of project
//
/////////////////////////////////////////////////////////////////
int main()
{
    char str[80] = {'\0'};
    char Command[5][20] = {{'\0'}};
    int iCount=0;

    StartAuxillaryDataInitialisation();

    printf("-------------------------------------------------------\n");
    printf("---------- Marvellous CVFS started Successfully--------\n");
    printf("-------------------------------------------------------\n");

    // Infinite Listening shell
    while(1)
    {
        fflush(stdin);
        strcpy(str,"");
        printf("\n Marvellous CVFS : > ");
        fgets(str,sizeof(str),stdin);  
        
        iCount = sscanf(str,"%s %s %s %s %s",Command[0],Command[1],Command[2],Command[3],Command[4]);

        fflush(stdin);

        if(iCount == 1)
        {
            if(strcmp("exit",Command[0]) == 0)
            {
                printf("Thank you for using Marvellous CVFS\n");
                printf("Deallocating all the allocated Resources\n");

                break;
            }
            else if(strcmp("ls",Command[0])==0)
            {
                printf("Inside ls\n");
            }
            else if(strcmp("help",Command[0])==0)
            {
                DisplayHelp();
            }
        }//End of else if 1
        else if(iCount == 2)
        {

        }//End of else if 2
        else if(iCount == 3)
        {

        }//End of else if 3
        else if(iCount == 4)
        {

        }//End of else if 4
        else
        {
            printf("Command not found\n");
            printf("Please refer help option to get more information\n");
        }//End of else
    }//End of While

    return 0;
}//End of main