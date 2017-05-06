#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <math.h>


void* worktodo(void * n) {
    printf( "hola %ld\n", (long)pthread_self());
    pthread_exit(NULL);
}

int main(int argc, char** argv) {
    int i, hilos;
    
   hilos = atoi(argv[1]);
   pthread_t id[hilos];   
    
    if (argc != 2) {
		printf("Por favor digite un numero hilos a usar\n");
		printf("\t%s <numhilos>\n",argv[0]);
                exit(-1);
	}
	
   if (hilos == 0) {
		printf("Ingresa una cantidad de hilos valida");
		exit(-1);
        }
   
    for (i = 0; i < hilos; i++) {
  	pthread_create(&id[i],NULL, worktodo, NULL);
    
	}

        for (i = 0; i < hilos; i++) {
		pthread_join(id[i], NULL);
}
    pthread_exit (NULL); 
}

