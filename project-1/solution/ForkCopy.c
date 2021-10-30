#include "Prj1header.h"




/* AÇIKLAMA
 *
 * Main process, bir adet child process yaratır ve MakeCopy programı üzerinden
 * child processe kopyalama yaptırır. Child process bitene kadar bekler.
 *
 * 
 * ./ForkCopy <sourceFile> <destinationFile> <bufferSize>
 * 
 */
int main(int argc, char *argv[])
{

    if(argc!=4)/*4 because the executables name string is on argc*/
    {
        printf("Error: Inputs-> sourceFile destFile blockSize\n");
        exit(-1);
    }
    
    int bufferSize = atoi(argv[3]);
    if (bufferSize<=0)
    {
        printf("Error: Wrong buffer size\n");
        exit(-1);
    }
    
    

    int pid = fork();

    
    
    if (pid > 0) { // parent
        wait(NULL); // Childin bitmesi beklenir.

    }else if (pid == 0) { // child
        execl("MakeCopy", "MakeCopy", argv[1], argv[2], argv[3], NULL);

    }else { // error
        printf("Process yaratilirken bir hata olustu.\n");
        exit(0);

    }
    
    
    
    return 0;
    
}