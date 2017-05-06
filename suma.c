#include <stdio.h>
#include <math.h>
#include <pthread.h>

#define MAXRECTANGULO 1000000
#define HILOS 10
#define BASE 0.0
#define LIMIT 1.0

double length = LIMIT - BASE;	// Longitud en el eje X.
double sumTotal = 0;	// Variable que tendra la suma total.
double base_length = 0;	// Variable que tiene el ancho de cada rectangulo.
double partialSums[HILOS];	// Variable que tiene la suma parcial de cada hilo.
double numRectxThread = (double)(MAXRECTANGULO / HILOS);	// Cuantos rectangulos por hilo.
// Funcion a la que se le calculara la integral.
double function(double x){
	
	return (x * x); 
}

void *calcular(void *arg){
	
	int id = (int)arg;
	double limites = (base_length * numRectxThread * id);
	partialSums[id] = 0;
	int i = 0;
	
	for(i = 0; i < numRectxThread; i++){
		
		partialSums[id] += (base_length * function(limites));
		limites += base_length;
	}

	printf("El hilo numero  %d determino una suma parcial de %lf.\n", id, partialSums[id]);
	pthread_exit(NULL);
}

int main(int argc, char **argv){
	
	// Vectores para almacenar los identificadores de los hilos.
	pthread_t hilos[HILOS];
	int taskids[HILOS];
	int aux = 0, i = 0;

	base_length = (double)(length / MAXRECTANGULO);
	printf("Base length: %lf y numRectxThread: %lf\n", base_length, numRectxThread);
	
	// Ciclo en donde procedemos a crear los hilos correspondientes y la ejecucion de la funcion plamada
    // anteriormente.

	for (i = 0; i < HILOS; i++){
		
		taskids[i] = i;
		pthread_create(&hilos[i], NULL, calcular, (void *)taskids[i]);
		}
	
	
	//En esta parte se cierra el hilo y se comienza a generar el resultado 
	for(i = 0; i < HILOS; i++){
		
		pthread_join(hilos[i], NULL);
		sumTotal += partialSums[i];
	}
	
	printf("Suma total: %lf\n", sumTotal);
	pthread_exit(NULL);
}
