#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <assert.h>

int main(int argc,char **argv){
int x;
int status = 0;
pid_t p;

    switch(p = fork())
    {
        case -1:
            printf("fork erreur");
            exit(EXIT_FAILURE);
        
        case 0 :
        
           // srand(time(NULL));  bu fonksiyonu sağlayan <conio.h> kütüphanesi macte çalışmadığı için yorum olarak bırakmak zorunda kaldım //
            x=rand()%11;
            sleep(3);
            exit(x);
        
        default:
           assert(wait(&status)!= -1);
            
            if(WIFEXITED(status))
            {
                int exit_status = WEXITSTATUS(status);
                printf("PidID'si %d olan cocuk %d degeriyle cıkıs yapıyor\n", p, exit_status);
            }
            
            
    }
    
}