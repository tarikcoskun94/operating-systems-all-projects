#include "Prj1header.h"

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
        
    }
    
    //WRITE YOUR CODE
    
    return 0;
    
}
