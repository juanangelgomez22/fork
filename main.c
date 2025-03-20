#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    pid_t pid;
    int pipefd[2];

    // 1. se crea el pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid = fork();
    if (pid == 0) { // Proceso hijo
        // 3. Cerrar el extremo de escritura (el hijo lee)
        close(pipefd[1]);

        char buf[256];
        ssize_t bytes_read;

        // 4. Leer del pipe pasandole los parametros correspondientes
        bytes_read = read(pipefd[0], buf, sizeof(buf));
        if (bytes_read == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
                //aca entra al proceso hijo
        printf("proceso hijo con pid: ",getpid());
        
        close(pipefd[0]); // Cerrar el extremo de lectura    
        //proceso hijo termina
        return 0;
    }
    else if (pid > 0)
    {
        //entra al proceso padre
        printf("proceso padre con id: ",getpid());

        // 3. Cerrar el extremo de lectura (el padre escribe)
        close(pipefd[0]);



        // 4. Escribir en el pipe
        write(pipefd[1], message, strlen(message));
        //entra al proceso padre
        printf("proceso padre con id: ",getpid());
        close(pipefd[1]); // Cerrar el extremo de escritura
        wait(NULL); // Esperar a que el hijo termine
        exit(EXIT_SUCCESS);
    }
    return 0
}
