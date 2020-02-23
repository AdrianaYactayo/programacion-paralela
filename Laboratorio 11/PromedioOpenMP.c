/*
 ============================================================================
 Name        : PromedioOpenMP.c
 Author      : Adriana Yactayo y Bryan Gama
 Version     :
 Copyright   : Your copyright notice
 Description : Hello OpenMP World in C
 Indicate number of Threads 'n' in Code:
 ============================================================================
 */
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double suma;
double promedio;
int n;
int p;
int *arreglo;

/**
 * Hello OpenMP World prints the number of threads and the current thread id
 */
int main(int argc, char *argv[]) {

n = 10000;
p = 4;
arreglo = malloc(sizeof(int) * n);
suma = 0;

srand(time(NULL));

// Generar arreglo
for(int i=0; i < n; i++){
//arreglo[i] = rand()%255;
arreglo[i] = i + 1;
}

printf("\n 01 Fuera de la region Paralela ...\n\n");

//omp_set_num_threads(8);

/* This constructor for parallel threads  */
#pragma omp parallel num_threads(p)
{
int id = omp_get_thread_num();
int nt = omp_get_num_threads();
int local_n = n/nt;
printf("\n %d %d %d ...\n\n", id, nt, local_n);
for(int i=id*local_n; i<(id+1)*local_n; i++){
suma+=arreglo[i];
}
}

promedio = suma / n;

printf("\n La suma es %f...\n\n", suma);
printf("\n El promedio es %f...\n\n", promedio);

}



