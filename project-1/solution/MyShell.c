#include "Prj1header.h"




/* AÇIKLAMA
 *
 * Komut ekranını taklit edebilmek için, kullanıcıdan girdi alır ve bir adet
 * child process üretir. Bu girdiyi, child process üzerinde execlp() fonksiyonu
 * ile calistirir. Main process childi bekler, girdiye göre işlemleri tekrarlar.
 * 
 * 
 * ./MyShell
 * 
 */
int main(int argc, char *argv[])
{
    
    char* buf = malloc(sizeof(char)*1024);
    int pid;
    
    
        
    do {
        
        printf ("> ");
        fgets(buf,1024,stdin);
        buf[strcspn(buf, "\n")] = 0; // "\n" nin neden olduğu bazı hatalara mahal vermemek için.
        
        if (strcmp(buf, "q") == 0) break; // çıkış istenirse forklanmadan döngü kırılıp sonlanır.
        
        pid = fork();
        
        if (pid > 0) { // parent
            wait(NULL); // Childin bitmesi beklenir.
            
            //if (strcmp(buf, "clear") == 0) continue; // clear komutu gelirse bir alttaki printf i yapmamalı. Döngünün başına yönlendirir.
            
            //printf ("\n----------------------------------------------------------------------------------------------------------------------------\n\n\n\n");
            
        } else if (pid == 0) { // child
            //printf ("------------------------------------------------------------| SONUC |-------------------------------------------------------\n\n");
            
            execlp(buf,buf,(char*)0);
            exit(0);
            
        } else { // error
            printf("Process yaratilirken bir hata olustu.\n");
            exit(0);
            
        }
        
    } while (1);
    
    free(buf); // ayrılan alan serbest bırakılıyor.
    
    
    
    return 0;
    
}