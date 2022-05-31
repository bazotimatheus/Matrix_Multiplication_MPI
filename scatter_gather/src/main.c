#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#include "../lib/multmatriz.h"

int main(int argc, char **argv) {
	double *A, *B, *C;
	double soma;

#ifdef MPI
	/* variaveis mpi */
	int mpi_root = 0;
	int my_id, num_procs;
	int tag = 1, mpi_err;
	MPI_Status rstatus;

	int num_tiras, num_elemt;
	double *recA, *recC;
#endif

	A = (double *)malloc(M*M*sizeof(double));
	B = (double *)malloc(M*M*sizeof(double));
	C = (double *)malloc(M*M*sizeof(double));

	srand(time(NULL));
	
/* Gera matrizes aleatorias */
	GeraMatriz(A, M, M);
	//GeraMatriz(B, M, M);
	GeraMatrizIdentidade(B, M, M);

#ifdef MPI
/* Abre regiao paralela */
	mpi_err = MPI_Init(&argc, &argv);
    mpi_err = MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    mpi_err = MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

#ifdef OUTPUT
	if(my_id == mpi_root) {
		printf("\nA primeira matriz:\n");
		ImprimeMatriz(A, M, M);
		printf("\nA segunda matriz:\n");
		ImprimeMatriz(B, M, M);
		printf("\n");
	}
#endif

/* Calcula o numero de tiras e o numero de elementos de cada tira */
	num_tiras = M / num_procs;
	num_elemt = M * num_tiras;

/* Aloca tiras */
	recA = (double *)malloc(num_elemt*sizeof(double));
	recC = (double *)malloc(num_elemt*sizeof(double));

/* Envia tiras para cada processo */
	mpi_err = MPI_Scatter(A, num_elemt, MPI_DOUBLE, recA, num_elemt, MPI_DOUBLE, mpi_root, MPI_COMM_WORLD);

/* Envia matriz B para todos os processos */
	mpi_err = MPI_Bcast(B, M*M, MPI_DOUBLE, mpi_root, MPI_COMM_WORLD);

/* Realiza a multiplicacao das matrizes */
	for(i = 0; i < num_tiras; i++) {
		for(j = 0; j < M; j++) {
			soma = 0;

			for(k = 0; k < M; k++) soma += recA[i*M+k] * B[j+k*M];

			recC[i*M+j] = soma;
		}
	}

/* Junta os resultados obtidos por cada processo */
	mpi_err = MPI_Gather(recC, num_elemt, MPI_DOUBLE, C, num_elemt, MPI_DOUBLE, mpi_root, MPI_COMM_WORLD);

/* barreira para que todos os dados sejam devidamente enviados e recebidos */
	mpi_err = MPI_Barrier(MPI_COMM_WORLD);

	free(recA);
	free(recC);

	/* imprime matriz resultante */
	#ifdef OUTPUT
		if(my_id == mpi_root) {
			printf("\nA matriz resultante:\n");
			ImprimeMatriz(C, M, M);
		}
	#endif // OUTPUT

	mpi_err = MPI_Finalize();
#else // SERIAL
	#ifdef OUTPUT
		printf("\nA primeira matriz:\n");
		ImprimeMatriz(A, M, M);
		printf("\nA segunda matriz:\n");
		ImprimeMatriz(B, M, M);
		printf("\n");
	#endif

	/* Realiza a multiplicacao das matrizes */
	for(i = 0; i < M; i++) {
		for(j = 0; j < M; j++) {
			soma = 0;

			for(k = 0; k < M; k++) soma += A[i*M+k] * B[j+k*M];

			C[i*M+j] = soma;
		}
	}

	/* imprime matriz resultante */
	#ifdef OUTPUT
		printf("\nA matriz resultante:\n");
		ImprimeMatriz(C, M, M);
	#endif // OUTPUT
#endif // MPI

	free(A);
	free(B);
	free(C);

	return 0;
}