#ifndef multmatriz_h__
#define multmatriz_h__

#define MPI
#define OUTPUT

#define M 10

int i, j, k;

extern void GeraMatriz(double *matriz, int m, int n);
extern void GeraMatrizIdentidade(double *matriz, int m, int n);
extern void ImprimeMatriz(double *matriz, int m, int n);
extern double *MultiplicaMatriz(double *matrizA, double *matrizB, int m, int n);

#endif // multmatriz_h__