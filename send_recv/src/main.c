#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#include "../lib/multmatriz.h"

int main(int argc, char **argv) {
	double *A, *B, *C;
	double soma;

#ifdef MPI
	/* variaveis globais mpi */
	int mpi_root = 0;
	int my_id, num_procs;
	int tag = 1, mpi_err;
	MPI_Status rstatus;
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

/* Realiza a multiplicacao das matrizes */
	for(i = my_id; i < M; i += num_procs) {
		for(j = 0; j < M; j++) {
			soma = 0;

			for(k = 0; k < M; k++) soma += A[i*M+k] * B[j+k*M];

			C[i*M+j] = soma;
		}
	}

/* procs mandam as linhas calculadas para o root */
	if(my_id != mpi_root) {
		for(i = my_id; i < M; i += num_procs)
			MPI_Ssend(&C[i*M], M, MPI_INT, mpi_root, tag, MPI_COMM_WORLD);
	}

/* root recebe as linhas calculadas pelos procs */
	if(my_id == mpi_root) {
		for(j = 1; j < num_procs; j++)
			for(i = j; i < M; i += num_procs)
				MPI_Recv(&C[i*M], M, MPI_INT, j, tag, MPI_COMM_WORLD, &rstatus);
	}

/* barreira para que todos os dados sejam devidamente enviados e recebidos */
	mpi_err = MPI_Barrier(MPI_COMM_WORLD);

	/* imprime matriz resultante */
	#ifdef OUTPUT
		if(my_id == mpi_root) ImprimeMatriz(C, M, M);
	#endif // OUTPUT

	MPI_Finalize();
#else // SERIAL
	C = MultiplicaMatriz(A, B, M, M);

	/* imprime matriz resultante */
	#ifdef OUTPUT
		ImprimeMatriz(C, M, M);
	#endif // OUTPUT
#endif // MPI

	free(A);
	free(B);
	free(C);

	return 0;
}