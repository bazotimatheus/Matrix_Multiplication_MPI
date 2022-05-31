#include <stdio.h>
#include <stdlib.h>

#include "../lib/multmatriz.h"

void GeraMatriz(double *matriz, int m, int n) {
	for(i = 0; i < m; i++)
		for(j = 0; j < n; j++) {
			matriz[i*m+j] = (double)rand()/RAND_MAX;
	}
}

void GeraMatrizIdentidade(double *matriz, int m, int n) {
	for(i = 0; i < m; i++)
	for(j = 0; j < n; j++) {
		if(i == j) matriz[i*m+j] = 1.0;
		else matriz[i*m+j] = 0.0;		
	}
}

void ImprimeMatriz(double *matriz, int m, int n) {
	for(i = 0; i < m; i++) {
		for(j = 0; j < n; j++)
			printf("%.2f ", matriz[i*m+j]);
		puts("");
	}
}

double *MultiplicaMatriz(double *matrizA, double *matrizB, int m, int n) {
	double soma, *resultado;
	for(i = 0; i < m; i++) {
		for(j = 0; j < n; j++) {
			soma = 0;

			for(k = 0; k < n; k++) soma += matrizA[i*n+k] * matrizB[j+k*n];

			resultado[i*n+j] = soma;
		}
	}
	return resultado;
}
