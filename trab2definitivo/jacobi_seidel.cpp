#include<iostream>
#include "jacobi_seidel.h"
/*
O programa tem a possibilidade de calcular o vetor d que a questão pede de duas
formas: método normal A*x = b e usando inversa A^(-1)*b = x, sendo b o vetor
de soluções (no caso é o d da questão).
*/

using std::cin; using std::cout; using std::endl;

// Crio uma classe Vetor, que tem utilidade apenas para guardar matrizes dentro
    // Construtor
Vetor::Vetor(int size){
	this->size = size;
  this->resultado = new double[size]; // Criação do vetor resultado na heap

        // Criação da matriz para a função deepcopy_matriz(). 
  this->matriz = new double*[size];
  for(int i = 0; i < size; i++){ 
    matriz[i] = new double[size];
		}
  };


// Faz uma cópia profunda de uma matriz para outra. Caso contrário, a matriz
// original pode se alterar sempre que eu quiser calcular cada coluna da
// inversa que a questão pede.
Vetor deepcopy_matriz(double* matriz[], const int n){
    Vetor copia(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            copia.matriz[i][j] = matriz[i][j];
        }
    }
    return copia;
}

// Algoritmo que calcula o produto de duas matrizes. Só funciona para matrizes
// que multiplicam (nxn * n).
Vetor* produto_Ab(double* matriz_inversa[], double* b, const int n){
    Vetor* vetor_d = new Vetor(n);
    double somatorio;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            somatorio = 0;
            for(int k = 0; k < n; k++){
                somatorio = somatorio + matriz_inversa[i][k]*b[k];
            }
            vetor_d->resultado[i] = somatorio;
        }
    }
    return vetor_d; // Vou preenchendo o vetor d.
}


// Operador módulo para um valor qualquer.
double abs(double valor){
    if (valor < 0) return -(valor);
    return valor;
}

// Compara o próximo resultado com o anterior, é o teste de parada (norma)
double teste_parada(double matriz[], double v[], int n){
    // Maior numerador e maior denominador
    double maxnum = 0;
    double maxden = 0;

    // Procura o valor máximo de cada matriz
    for(int i = 0; i < n; i++){
        double num = abs(matriz[i]-v[i]);
        if (num > maxnum){
            maxnum = num;
        }
        double den = abs(matriz[i]);
        if (den > maxden){
            maxden = den;
        }
    }
    // Retorna a divisão do maior número de cada matriz
    return maxnum/maxden;
}

// Método numérico Gauss-Seidel.
Vetor* seidel(double* matriz[], double* b, double tol, const int n, bool metodo_jacobi, int limite){
    Vetor* x = new Vetor(n);  // Inicializo o vetor x na heap
    Vetor* v = new Vetor(n);  // Inicializo o vetor v na heap (será o vetor x do passo anterior)
    double d; // distância d (teste de parada)
    double somatorio = 0;
    // Inicializo os vetores vazios com 0 como chute inicial.
    for(int i = 0; i < n; i++) { x->resultado[i] = 0; v->resultado[i] = 0; }


    // Criação de um novo sistema linear no formato
    // x{k+1} = C * x{k} * (b[i]/matriz[i][i])
    // Onde C é a matriz das constantes geradas dividindo
    // todos os elementos matriz[i][j] por matriz[i][i] (menos a diagonal)
    // x{k} é o novo vetor de x a partir desse novo sistema.
    for(int i = 0; i < n; i++){
        for(int j = 0; j<n; j++){
            if(i != j){
                matriz[i][j] = matriz[i][j]/matriz[i][i];
            }
        }
        b[i] = b[i]/matriz[i][i]; // Novo vetor b

        // Se for Jacobi, inicializo o vetor x com aproximação inicial
        // b[i]/matriz[i][i], que já é o próprio b[i] acima
        if(metodo_jacobi){
            x->resultado[i] = b[i];
        }
    }

    Vetor* temp = new Vetor(n);

    // Iterações
    for(int k = 1; k < limite+1; k++){
        for (int i = 0; i < n; i++){
            somatorio = 0;
            for(int j = 0; j < n; j++){
                if(i != j){
                    // Lembrando que o sistema novo criado é no formato
                    // x{k+1} = C * x{k} * (b[i]/matriz[i][i]). Essa
                    // Operação multiplica a matriz C pelo vetor x{k}.
                    somatorio = somatorio + matriz[i][j] * x->resultado[j];
                }
            }

            // Jacobi: preencho o vetor v, que será o vetor anterior.
            // Seidel: Vou preenchendo novo vetor x já recebendo valores anteriores em
            // tempo real para a próxima iteração
            if(metodo_jacobi){ 
                v->resultado[i] = b[i] - somatorio;
            } else{
                x->resultado[i] = b[i] - somatorio;
            }
        }
        
        // Fechou o vetor x ou v, agora faz o teste de parada e compara com o vetor
        // anterior. O teste de parada pra Jacobi é o inverso do de Seidel
        if(metodo_jacobi){
            d = teste_parada(v->resultado, x->resultado, n);
        } else{
            d = teste_parada(x->resultado, v->resultado, n);
        }

        if(d <= tol){ // Se for menor que a tolerância, acabou.
            temp->resultado = v->resultado; // temp.resultado aponta pra onde v.resultado aponta.
            if(metodo_jacobi){
                // Se for Jacobi, retorno o último vetor anterior
                return temp;
            } else {
                // Se for Seidel, retorno o vetor mais atualizado possível.
                return x; 
            }
        }
        // Se não é menor que a precisão, continua o método.


        // Se for Jacobi, x vai receber o novo vetor v que acabei de calcular.
        if (metodo_jacobi){
            for(int copia = 0; copia < n; copia++){
                x->resultado[copia] = v->resultado[copia];
            }
        // Se não for Jacobi, faço uma cópia do vetor x pro vetor anterior. 
        // Pois o novo x será modificado e o atual virará o anterior (v).
        } else{
            for(int copia = 0; copia < n; copia++){
                v->resultado[copia] = x->resultado[copia];
            }
        }
    }
    cout << "Erro! Número máximo de iterações atingido." << endl;
	return x;
}

