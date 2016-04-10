#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <assert.h>


void run_program(char *str);
int main(int argc, char * argv[]){
    
    pid_t pid;
    
    char line[2000];
    char komutlar[100];
    char *komut;
    char **argv2;
    
    int status=0;
    int i =0;
    
    
    
    while(1){
        
        printf(">");
        fgets(line,sizeof(line), stdin);
        
        //Kullanıcı bir şey girmeden enter 'a basarsa döngüye geri dön.
        if(line[0] == '\n'){
            printf("Bir komut girmeniz gerekli\n");
            continue;
        }
        
        //fgets komutundaki '\0'  karakterini ez.
        
        if(line[strlen(line)-1]== '\n') {
            line[strlen(line)-1] = '\0';
        }
        
        //exit komutu girdiğinde kabuktan çık. Soru 2.3 cevabı:
        if(strcmp(line, "exit")==0){
            printf("Bye!\n");
            break;
        }
        
        /*Eğer 4.soru nun istediği run_program fonksiyonu yazmasaydık bunu kullanabilirdik. Girdiğimiz komutu strtok ile her boşlukta böl
        komut = strtok(line," ");
        char **argv2= argv;
        
        while( komut!= NULL){
            
            *argv2 ++= komut;
            komut = strtok(NULL," ");
            
        }
        //execvp için son  değeri Null yap.
        *argv2 = NULL;
        strcat(komutlar, argv[0]);*/
        
        
        
        
        switch((pid=fork())) {
            case -1:
                perror("error fork");
                exit(EXIT_FAILURE);
                break;
                
            case 0: //child
             
                while(line[i] != '\0'){
                // eğer iki argümanlı bir komut varsa bu şekilde
                    if(line[i] == ' '){
                        run_program(line);
                    }else
                        i ++;
                    
                }
                
                // eğer tek argümanlı komut varsa bu şekilde (2.1'in cevabı ):
                execvp(line,argv);
                
                // Soru 2.2 nin cevabı
                if (errno == ENOENT){
                    printf("command not found!\n");
                    exit(127);
                }
                fprintf(stderr, "Child couldn't do execvp\n");
                exit(EXIT_SUCCESS);
                
            default: //parent
                assert(wait(&status)!= -1);
                if(WIFEXITED(status)){
                    int exit_status = WEXITSTATUS(status);
                    printf("Child terminated with : %d\n", exit_status);
                }
                
                
        }
        
    }
}
// Soru 2.4 'ün cevabı:
void run_program(char *str){
    char *argv[100];
    char *komut;
    char **argv2= argv;
   
    
    komut = strtok(str," ");
    
    while( komut!= NULL){
        
        *argv2 ++= komut;
        komut = strtok(NULL," ");
        
    }
    //execvp için son  değeri Null yap.
    *argv2 = NULL;
    
    //argümanları dizi içine al.
    execvp(argv[0], argv);
  
 
 }
    










