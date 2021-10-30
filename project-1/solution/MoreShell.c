#include "Prj1header.h"


char** splitString(char* a_string, const char a_delim);




/* AÇIKLAMA
 *
 * MyShelle aynı davranışı sergiler ancak yapılan girdide opsiyonlu bir kullanım
 * var ise gerekli ayrıştırmayı yapar ve execvp() fonksiyonu ile çalıştırır.
 * 
 * 
 * ./MoreShell
 *  
 */
int main()
{
    
    char* buf = malloc(sizeof(char)*1024);
    
    char** arguments;
    
    int pid;
    
     
        
    do {
        
        printf (">");
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

            arguments = splitString(buf, ' ');
            
            execvp(arguments[0],arguments);
            exit(0);
            
        } else { // error
            printf("Process yaratilirken bir hata olustu.\n");
            exit(0);
             
        }
        
    } while (1);
    
    free(buf); // ayrılan alan serbest bırakılıyor.
    
    
    
    return 0;
    
}





char** splitString(char* a_string, const char a_delim) {
    
    int delimCount = 0; // Ayarç karakterinin adedi için
    
    char* string = strdup(a_string); // daha sonrasında stringlerle ilgili işlem yaparken hata almamak için strdup() fonksiyonuna veriyoruz.
    
    char* delim  = strdup(&a_delim); // daha sonrasında stringlerle ilgili işlem yaparken hata almamak için strdup() fonksiyonuna veriyoruz.
    
    
    
    for (int i = 0; string[i] != '\0'; i++){ // Split için verilen karakterden kaç adet olduğunu bulur.
        if (string[i] == *delim){
            if (string [i+1] == *delim) continue; // Arka arkaya aynı karakterden varsa tek bir sefer saymak için.
            delimCount++;
        }
    }
    delimCount += 2; // Split karakter sayısından 1 fazla kadar arguman vardır. 1 adet de NULL için. Toplamda split karakter + 2 kadar yer lazım.
    
    char** result = malloc(sizeof(char*) * delimCount);
    
    int i=0;
    char* token = strtok(string, delim);
    while( token != NULL ) { // argumanlar burada pars edilir.
       result[i] = strdup(token);
       token = strtok(NULL, delim);
       i++;
    }
    
    result[i] = NULL; // dizinin en sonuna eklenir.

    
    
    return result;
}