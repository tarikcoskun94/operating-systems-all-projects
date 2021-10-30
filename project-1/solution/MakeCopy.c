#include "Prj1header.h"


int isFileEmpty (FILE *theFile);




/* AÇIKLAMA
 *
 * Komut ekranından girilen argümanlara göre, bir kaynak dosyadaki bulunan tüm
 * içeriği, verilen buffer boyutunun limitleri ile kaynak dosyaya kopyalar.
 *
 * 
 * ./MakeCopy <sourceFile> <destinationFile> <bufferSize>
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
    

    
    char* buf = malloc(sizeof(char)*bufferSize);
    char oneCharBuf;
    
    FILE *sourceFile, *destFile;
    
     
    
    sourceFile = fopen(argv[1], "r");

    if (sourceFile != NULL) { // Kaynak dosya açıldıysa devam eder.
        if (isFileEmpty(sourceFile) == -1) {  // Dosya boşsa işlem devam etmez.
            printf("Kaynak dosya icerigi bos.\n");
            exit(0);
            
        }

        destFile = fopen(argv[2], "w");

        if (destFile != NULL) { // Hedef dosya açıldıysa devam eder.
            if (bufferSize == 1) { // buffer 1 ise, karakter karakter kopyalanıyor.
                oneCharBuf = fgetc(sourceFile);
                
                while(oneCharBuf != EOF){ // kaynak dosyanın sonuna kadar okur ve her bir veriyi hedef dosyaya yazar.   
                    fputc(oneCharBuf, destFile);
                    oneCharBuf = fgetc(sourceFile);
                }
                
            } else { // buffer 1 den daha fazla ise buffer kadar karakter kopyalanıyor.
                while(fgets(buf, bufferSize, sourceFile) != NULL){ // kaynak dosyanın sonuna kadar okur ve her bir veriyi hedef dosyaya yazar.
                    fputs(buf, destFile);
                }
                
            }
                        
            free(buf); // ayrılan alan serbest bırakılıyor.
                
        }else { // destFile hata.
            printf("%s acilamadi.\n", argv[2]);
            exit(0);
                
        }

    }else { // sourceFile hata.
        printf("%s acilamadi.\n", argv[1]);
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