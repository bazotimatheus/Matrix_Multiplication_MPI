Esta pasta possui o programa que multiplica duas matrizes (A x B = C) usando MPI com as diretivas MPI_Send() e MPI_Recv().
Para compilá-lo, digite no terminal:

> make

Será gerado um executável "multmatriz".
Para executá-lo, digite no terminal:

> mpirun -np X ./multmatriz

onde "X" é o número de processos que serão utilizados.

Outra opção para rodar o programa é por meio do script run.sh.
O autor costuma rodar o script da seguinte forma:

> nohup ./run.sh &

Assim os tempos serão salvos em um arquivo nohup.out e o terminal não fica travado.

No arquivo ./lib/multimatriz.h encontram-se 2 defines.
O primeiro habilita a execução em paralelo com MPI e o segundo a impressão na tela das matrizes e do resultado obtido.
Caso queira rodar o programa em serial, comente a linha #define MPI.
Caso queira rodar o programa sem imprimir nada na tela, comente a linha #define OUTPUT.
O tamanho das matrizes também se encontra nesse arquivo, podendo ser feita qualquer alteração caso seja necessário.

No arquivo ./src/main.c é usada a matriz B como a identidade pois facilita na hora de conferir os dados (visto que A x I = A).
Pode-se mudar esta matriz para uma gerada aleatoriamente, basta comentar a função GeraMatrizIdentidade() e descomentar a função GeraMatriz().
