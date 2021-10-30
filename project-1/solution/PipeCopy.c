#include "Prj1header.h"


int isFileEmpty (FILE *theFile);




/* AÇIKLAMA
 *
 * Main process, bir adet pipe oluşturur ve ardından iki adet child process
 * yaratır. Child processlerden biri okuma ucu, diğeri ise yazma ucu olarak
 * veri aktarımı yapar ve dosyadan dosyaya aynı şekilde içeriği kopyalar.
 * 
 * 
 * ./PipeCopy <sourceFile> <destinationFile> <bufferSize>
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
    
    
    
    int pid1;
    int pid2;
    
    int pipeManager[2];
    
    char* buf = malloc(sizeof(char)*bufferSize);
    char* readBuf = malloc(sizeof(char)*bufferSize);
    char oneCharBuf;
    
    FILE *sourceFile, *destFile;
    
    
    
    sourceFile = fopen(argv[1], "r");
    
    if (sourceFile == NULL){ // sourceFile hata.
        printf("%s acilamadi.\n", argv[1]);
        exit(0);
        
    }
    
    if (isFileEmpty(sourceFile) == -1) {  // Dosya boşsa işlem devam etmez.
            printf("Kaynak dosya icerigi bos.\n");
            exit(0);
            
    }
        
    destFile = fopen(argv[2], "w");
    
    if (destFile == NULL){ // destFile hata.
        printf("%s acilamadi.\n", argv[2]);
        exit(0);
        
    }

    pipe(pipeManager);

    pid1 = fork();

    if (pid1 > 0){ // parent
        pid2 = fork();

        if (pid2 > 0) { // parent  
            close(pipeManager[0]);
            close(pipeManager[1]);
            
            wait(NULL);
            wait(NULL);

        } else if (pid2 == 0) { // child 2
            close(pipeManager[1]);
            
            while (read(pipeManager[0], readBuf, bufferSize) > 0) { // read işlemi bitene kadar pipe verileri alınır ve hedef dosyaya yazılır.
                fputs(readBuf, destFile); 
            }
            
            close(pipeManager[0]);

            free(readBuf); // ayrılan alan serbest bırakılıyor.
            exit(0);

        } else { // error
            printf("Process yaratilirken bir hata olustu.\n");
            exit(0);  

        }       

    }else if (pid1 == 0){ // child 1
        close(pipeManager[0]);

        if (bufferSize == 1) { // buffer 1 ise, karakter karakter kopyalanıyor.
            while ((oneCharBuf = fgetc(sourceFile)) != EOF){ // kaynak dosyanın sonuna kadar okur ve her bir veriyi write kanalına basar.              
                write(pipeManager[1], &oneCharBuf, 1);
            }

        } else { // buffer 1 den daha fazla ise buffer kadar karakter kopyalanıyor.
            while (fgets(buf, bufferSize, sourceFile) != NULL){ // kaynak dosyanın sonuna kadar okur ve her bir veriyi write kanalına basar.                
                write(pipeManager[1], buf, bufferSize);
            }            
            
        }
        
        close(pipeManager[1]);

        free(buf); // ayrılan alan serbest bırakılıyor.
        exit(0);  

    }else { // error
        printf("Process yaratilirken bir hata olustu.\n");
        exit(0);

    }
    
    fclose(sourceFile);
    fclose(destFile);
    
    
    
    return 0;
    
}





int isFileEmpty (FILE *theFile) { // Dosyanın karakter sayısını döndürür.
      
    char theChar = fgetc(theFile);
    
    
    
    rewind(theFile); // Karakter pointerını resetler. Başa taşır.
    
    if (theChar != EOF)
        return 1; // Dolu ise
             
    
    
    return -1; // Boş ise
        
}
