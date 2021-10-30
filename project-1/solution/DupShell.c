#include "Prj1header.h"


char** splitString(char* a_string, const char a_delim);




/* AÇIKLAMA
 *
 * MoreShelle aynı davranışı sergiler ancak yapılan girdide pipe lı bir kullanım
 * var ise gerekli ayrıştırmayı yapar. dup2() fonksiyonu, bir pipe ile aktif edilip
 * ilk komutun çıktısı diğer uçtan yakalanır ve girdi olarak kullanılır.
 * 
 * 
 * ./DupShell
 * 
 */
int main()
{
    
    char* buf = malloc(sizeof(char)*1024);
    
    char** pipeArguments; // pipe lı parametre gelirse, "|" işaretinden 2 ye bölünüp burada tutulur.
    char** leftArguments; // sol taraf kendi içinde pars edlip buraya konulur.
    char** rightArguments; // sağ taraf kendi içinde pars edlip buraya konulur.
    
    int pid1;
    int pid2;
    
    int pipeManager[2];
    bool pipeMode = false; // "|" işaretinin varlığı için.
     
    
        
    do {
        pipe(pipeManager);
        
        printf (">");
        fgets(buf,1024,stdin);
        buf[strcspn(buf, "\n")] = 0; // "\n" nin neden olduğu bazı hatalara mahal vermemek için.
        
        if (strcmp(buf, "q") == 0) break; // çıkış istenirse forklanmadan döngü kırılıp sonlanır.
        
        if (strstr(buf, "|") == NULL){ // "|" karakteri var mı yok mu?
            pipeMode = false;
            
            leftArguments  = splitString(buf, ' '); // yoksa MakeCopy gibi çalıştırılmak üzere parse edilir.
            
        } else { // varsa önce solu ve sağı ayrılır. Sonra kendi içlerinde argumanlarına ayrılır.
            pipeMode = true;
            
            pipeArguments  = splitString(buf, '|');
            leftArguments  = splitString(pipeArguments[0], ' ');
            rightArguments = splitString(pipeArguments[1], ' ');
            
        }

        pid1 = fork();
        
        if (pid1 > 0) { // parent
            pid2 = fork();
            
            if (pid2 > 0) { // parent   
                close(pipeManager[0]);
                close(pipeManager[1]);

                wait(NULL);
                wait(NULL);
                                
                //if (strcmp(buf, "clear") == 0) continue; // clear komutu gelirse bir alttaki printf i yapmamalı. Döngünün başına yönlendirir.
            
                //printf ("\n----------------------------------------------------------------------------------------------------------------------------\n\n\n\n");

            } else if (pid2 == 0) { // child 2
                if(pipeMode == true){
                    fclose(stdin);
                    
                    dup2(pipeManager[0],STDIN_FILENO);
                    
                    close(pipeManager[0]);
                    close(pipeManager[1]);
                                        
                    //printf ("------------------------------------------------------------| SONUC |-------------------------------------------------------\n\n");
                    
                    execvp(rightArguments[0],rightArguments);
                    
                }
		exit(0);

            } else { // error
                printf("Process yaratilirken bir hata olustu.\n");
                exit(0);
             
            }

        } else if (pid1 == 0) { // child 1
            if(pipeMode == true) {  
                fclose(stdout);
                
                dup2(pipeManager[1],STDOUT_FILENO);
                
                close(pipeManager[0]);
                close(pipeManager[1]);
                
            } 
            
            //printf ("------------------------------------------------------------| SONUC |-------------------------------------------------------\n\n");
            
            execvp(leftArguments[0],leftArguments);
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
