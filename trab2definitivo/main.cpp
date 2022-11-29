#include <iostream>
#include "jacobi_seidel.h"

using std::cout;
using std::cin;
using std::endl;

void imprimir_d(Vetor* d, const int n){
	cout << "[";
	for(int i = 0; i < n; i++){
			if(i == n-1){ // Se for o último elemento
					cout << d->resultado[i]; // Não printa a vírgula
			}
			else{
					cout << d->resultado[i] << ", ";
			}
	}
	cout << "]\n";
}


int main(){
    cout << "PROGRAMA QUE CALCULA O VETOR DE SOLUÇÕES 'd' DE UM SISTEMA LINEAR" << endl;
    cout << "UTILIZANDO A MATRIZ NORMAL OU A INVERSA DA MATRIZ COM ESCOLHA" << endl;
    cout << "DE USAR MÉTODO DE GAUSS-JACOBI OU GAUSS-SEIDEL" << endl;
    double* b_seidel_original;  // Vetor b
		double* b_seidel_inversa;  // Vetor b
		double* b_jacobi_original;  // Vetor b
		double* b_jacobi_inversa;  // Vetor b	
	  int n; // Ordem n do sistema linear
    double** matriz_seidel_original;
		double** matriz_seidel_inversa;
		double** matriz_jacobi_original;
		double** matriz_jacobi_inversa;
    cout << "Digite a ordem N da matriz: " << endl;
    cin >> n;


    // Criação das linhas dessa matriz na heap dinamicamente
    matriz_seidel_original = new double*[n];
		matriz_seidel_inversa = new double*[n];
		matriz_jacobi_original = new double*[n];
		matriz_jacobi_inversa = new double*[n];

    // Criação das colunas dessa matriz na heap dinamicamente
    for(int i = 0; i < n; i++){ 
        matriz_seidel_original[i] = new double[n];
				matriz_seidel_inversa[i] = new double[n];	
				matriz_jacobi_original[i] = new double[n];
				matriz_jacobi_inversa[i] = new double[n];
    }

    // Enfiando dados na matriz
    cout << "Digite os números na matriz A de ordem " << n << endl;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << "Digite o elemento na linha " << i+1 << " Coluna " << j+1 << ": ";
            cin >> matriz_seidel_original[i][j];
						matriz_seidel_inversa[i][j] = matriz_seidel_original[i][j];
						matriz_jacobi_original[i][j] = matriz_seidel_original[i][j];
						matriz_jacobi_inversa[i][j] = matriz_seidel_original[i][j];
        }
    }

    // DEBUG: Mostrando os dados na matriz
    cout << "Matriz completa:" << endl;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << matriz_seidel_original[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;


    // Criando o array b na heap
    b_seidel_original = new double[n]; 
		b_seidel_inversa = new double[n]; 
		b_jacobi_original = new double[n]; 
		b_jacobi_inversa = new double[n]; 


    // Preenchendo o vetor b
    cout << "Digite os elementos do vetor b." << endl;
    for(int i = 0; i < n; i++){
        cout << "Digite o elemento " << i+1 << ": ";
        cin >> b_seidel_original[i];
				b_seidel_inversa[i] = b_seidel_original[i];
				b_jacobi_inversa[i] = b_seidel_original[i];
				b_jacobi_original[i] = b_seidel_original[i];
    }
    cout << endl;


    // DEBUG: Printando o array b
    cout << "Printando o vetor b:" << endl;
    for(int i = 0; i < n; i++){
        cout << b_seidel_inversa[i] << ' ';
    }
    cout << endl;


    // Tolerância desejada
    double tol;
    cout << "\nDigite a tolerância com que se deseja trabalhar (precisão): ";
    cin >> tol;

    /* CÁLCULO DO VETOR d PELA MATRIZ INVERSA */
    
        
			// Crio uma matriz identidade na heap
			double** matriz_identidade_seidel = new double*[n];
			double** matriz_identidade_jacobi = new double*[n];
	
			for(int i = 0; i < n; i++){ 
					matriz_identidade_seidel[i] = new double[n];
					matriz_identidade_jacobi[i] = new double[n];
			}


			// Defino a matriz identidade com 1s na diagonal e 0s no resto dela
			for (int i = 0; i < n; i++){
					for (int j = 0; j < n; j++){
							if(i == j){
									matriz_identidade_seidel[i][i] = 1;
									matriz_identidade_jacobi[i][i] = 1;
							} else{
									matriz_identidade_seidel[i][j] = 0;
									matriz_identidade_jacobi[i][j] = 0;
							}
					}
			}


			// DEBUG: Mostrando os dados na matriz identidade
			cout << "\nMatriz identidade completa:" << endl;
			for (int i = 0; i < n; i++){
					for (int j = 0; j < n; j++){
							cout << matriz_identidade_seidel[i][j] << ' ';
					}
					cout << endl;
			}
			cout << endl;


			// Crio uma matriz inversa na heap
			double** matriz_inversa_seidel = new double*[n];
			for(int i = 0; i < n; i++){ 
					matriz_inversa_seidel[i] = new double[n];
			}

			double** matriz_inversa_jacobi = new double*[n];
			for(int i = 0; i < n; i++){ 
					matriz_inversa_jacobi[i] = new double[n];
			}


			// A questão pede para que seja criado uma coluna da inversa de cada vez
			// utilizando uma coluna da matriz identidade de cada vez. E isso é feito
			// usando múltiplos métodos de Gauss-Seidel.
			for(int i = 0; i < n; i++){
					// Vetor identidade será cada coluna de uma matriz identidade
					double* vetor_identidade_seidel = new double[n];
					double* vetor_identidade_jacobi = new double[n];

					for(int j = 0; j < n; j++){
							// Capturo uma coluna apenas e armazeno no vetor identidade
							vetor_identidade_seidel[j] = matriz_identidade_seidel[j][i];
							vetor_identidade_jacobi[j] = matriz_identidade_jacobi[j][i];
					}

					// Passo diretamente uma cópia da matriz original usando 
					// deepcopy_matriz().matriz, assim a matriz original não se perde.
					Vetor* res_seidel = seidel(deepcopy_matriz(matriz_seidel_inversa, n).matriz, vetor_identidade_seidel, tol, n, false);
					Vetor* res_jacobi = seidel(deepcopy_matriz(matriz_jacobi_inversa, n).matriz, vetor_identidade_jacobi, tol, n, true);

					// Deleto e vou criando outra coluna identidade pra não encher a memória
					delete[] vetor_identidade_seidel;
					delete[] vetor_identidade_jacobi;

					// Com o x que armazena o resultado do método de Gauss-Seidel, vou
					// preenchendo a matriz inversa zerada coluna por coluna.
					for (int j = 0; j < n; j++){
							matriz_inversa_seidel[j][i] = res_seidel->resultado[j];
							matriz_inversa_jacobi[j][i] = res_jacobi->resultado[j];
					}
			}


			// Mostrando os dados na matriz inversa (a questão pede)
			cout << "\nMatriz inversa (Metodo Seidel) completa:" << endl;
			for (int i = 0; i < n; i++){
					cout << "[";
					for (int j = 0; j < n; j++){
							cout << matriz_inversa_seidel[i][j] << ' ';
					}
					cout << "]";
					cout << endl;
			}
			cout << endl;

			cout << "\nMatriz inversa (Metodo Jacobi) completa:" << endl;
			for (int i = 0; i < n; i++){
					cout << "[";
					for (int j = 0; j < n; j++){
							cout << matriz_inversa_jacobi[i][j] << ' ';
					}
					cout << "]";
					cout << endl;
			}

			double somatorio;

			// Faço o produto de A^(-1)*b e obtenho o vetor d de incógnitas.
			Vetor* vetor_d_seidel = produto_Ab(matriz_inversa_seidel, b_seidel_inversa, n);
			Vetor* vetor_d_jacobi = produto_Ab(matriz_inversa_jacobi, b_jacobi_inversa, n);
			

			// Mostrando os dados da matriz d de incógnitas (a questão pede)
			cout << "\nUsando matriz inversa\n";
			cout << "Vetor d seidel:" << endl;
			imprimir_d(vetor_d_seidel, n);
			cout << "Vetor d jacobi: " << endl;
			imprimir_d(vetor_d_jacobi, n);


			/* DELETANDO TUDO QUE FOI CRIADO NESSE CONDICIONAL */

			// Deletando as linhas dessas matrizes
			for (int i = 0; i < n; i++){
					//delete[] matriz_identidade[i];
					delete[] matriz_inversa_jacobi[i];
					delete[] matriz_inversa_seidel[i];
			}

			// Deletando as colunas dessas matrizes
			//delete[] matriz_identidade;
			delete[] matriz_inversa_seidel;
			delete[] matriz_inversa_jacobi;

			// Deletando o vetor de resultados, já que não usarei mais
			delete[] vetor_d_seidel;
			delete[] vetor_d_jacobi;
			// Deletando o objeto res

	 /* CÁLCULO DO VETOR d PELA MATRIZ ORIGINAL */
    
			
		Vetor* vetor_d_seidel_original = seidel(deepcopy_matriz(matriz_seidel_original, n).matriz, b_seidel_original, tol, n, false);
		Vetor* vetor_d_jacobi_original = seidel(deepcopy_matriz(matriz_jacobi_original, n).matriz, b_jacobi_original, tol, n, true);

		// Mostrando os dados da matriz d de incógnitas (a questão pede)
		cout << "\nUsando matriz original\n";
		cout << "Vetor d seidel:" << endl;
		imprimir_d(vetor_d_seidel_original, n);
		cout << "Vetor d jacobi: " << endl;
		imprimir_d(vetor_d_jacobi_original, n);
		cout << "\n\n";
		// Deletando o vetor de resultados e o objeto res
		//delete vetor_d_seidel_original;
		delete vetor_d_jacobi_original;
}