#ifndef JACOBI_SEIDEL_H
#define JACOBI_SEIDEL_H

class Vetor{
public:
    double** matriz; 
    double* resultado;
    int size;

    Vetor(int size);
};

Vetor deepcopy_matriz(double* matriz[], const int n);

Vetor* produto_Ab(double* matriz_inversa[], double* b, const int n);

double abs(double valor);

double teste_parada(double matriz[], double v[], int n);

Vetor* seidel(double* matriz[], double* b, double tol, const int n, bool metodo_jacobi, int limite = 500);

#endif