#include<iostream>

/*

Gauss Seidel (Bônus Gauss Jordan) em C++. Feito por Victor Martins e Daniel

O programa tem a possibilidade de calcular o vetor d que a questão pede de duas
formas: método normal A*x = b e usando inversa A^(-1)*b = x, sendo b o vetor
de soluções (no caso é o d da questão).

Evitei ao máximo o uso de bibliotecas. O código ainda precisaria ser melhorado
bastante, além da otimização de memória. Mas o programa está cumprindo seu
papel, e portanto acho que seria suficiente para a resolução da questão.

*/

using std::cin; using std::cout; using std::endl;

// Crio uma classe Vetor, que tem utilidade apenas para guardar matrizes dentro
// de um objeto e retornar o objeto com a matriz, já que em C e C++ não é 
// possível retornar arrays diretamente, apenas endereços.
class Vetor{
public:
    double** matriz; // Usado apenas para a função deepcopy_matriz()
    double* resultado; // vetor de resultados
    int size; // Ordem do vetor/matriz

    // Construtor
    Vetor(int size){
        this->size = size;
        this->resultado = new double[size]; // Criação do vetor resultado na heap

        // Criação da matriz para a função deepcopy_matriz(). 
        // TODO: Poderia ficar em um método separado, se puderem otimizar 
        // essa parte, agradeço.
        this->matriz = new double*[size];
        for(int i = 0; i < size; i++){ 
            matriz[i] = new double[size];
        }
    }
};


// Faz uma cópia profunda de uma matriz para outra. Caso contrário, a matriz
// original pode se alterar sempre que eu quiser calcular cada coluna da
// inversa que a questão pede. Por isso preciso dessa aqui auxiliar.
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
Vetor* seidel(double* matriz[], double* b, double tol, const int n, bool metodo_jacobi, int limite = 500){
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
                // Ignoro a diagonal dos elementos de C, pois C não terá diagonal definida
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

    Vetor* temp = new Vetor(n); // Variável auxiliar, não sei se precisa, mas
    // pra garantir a não ocorrência de possíveis erros, coloquei

    // Iterações
    for(int k = 1; k < limite+1; k++){
        for (int i = 0; i < n; i++){
            somatorio = 0;
            for(int j = 0; j < n; j++){
                // Ignoro a diagonal dos elementos de C, pois C não tem diagonal definida
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
            temp->resultado = v->resultado; // temp.resultado aponta pra onde v.resultado aponta. Coloquei pra evitar possíveis erros.
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
}

int main(){
    cout << "PROGRAMA QUE CALCULA O VETOR DE SOLUÇÕES 'd' DE UM SISTEMA LINEAR" << endl;
    cout << "UTILIZANDO A MATRIZ NORMAL OU A INVERSA DA MATRIZ COM ESCOLHA" << endl;
    cout << "DE USAR MÉTODO DE GAUSS-JACOBI OU GAUSS-SEIDEL" << endl;
    double* b;  // Vetor b
    int n; // Ordem n do sistema linear
    double** matriz;
    cout << "Digite a ordem N da matriz: " << endl;
    cin >> n;


    // Criação das linhas dessa matriz na heap dinamicamente
    matriz = new double*[n];

    // Criação das colunas dessa matriz na heap dinamicamente
    for(int i = 0; i < n; i++){ 
        matriz[i] = new double[n];
    }

    // Enfiando dados na matriz
    cout << "Digite os números na matriz A de ordem " << n << endl;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << "Digite o elemento na linha " << i+1 << " Coluna " << j+1 << ": ";
            cin >> matriz[i][j];
        }
    }

    // DEBUG: Mostrando os dados na matriz
    cout << "Matriz completa:" << endl;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << matriz[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;


    // Criando o array b na heap
    b = new double[n]; 


    // Preenchendo o vetor b
    cout << "Digite os elementos do vetor b." << endl;
    for(int i = 0; i < n; i++){
        cout << "Digite o elemento " << i+1 << ": ";
        cin >> b[i];
    }
    cout << endl;


    // DEBUG: Printando o array b
    cout << "Printando o vetor b:" << endl;
    for(int i = 0; i < n; i++){
        cout << b[i] << ' ';
    }
    cout << endl;


    // Tolerância desejada
    double tol;
    cout << "\nDigite a tolerância com que se deseja trabalhar (precisão): ";
    cin >> tol;


    // Qual método o usuário quer utilizar
    bool metodo_jacobi = false;

    cout << "\nVocê deseja calcular o vetor de soluções através do método de Gauss-Jacobi ou método de Gauss-Seidel?";
    cout << "\n1 - Método de Gauss-Jacobi\n2 - Método de Gauss-Seidel\nQualquer outro valor - Sair\n";
    int metodo_escolhido;
    cout << "Digite aqui: ";
    cin >> metodo_escolhido;
    if (metodo_escolhido == 1) {metodo_jacobi = true;} else if (metodo_escolhido == 2){} else{exit(0);}

    // O que o usuário deseja fazer.
    cout << "\nVocê deseja calcular o vetor de soluções através do método normal Ad = b ou pela inversa A^(-1)*b = d?";
    cout << "\n1 - Usando Inversa\n2 - Usando Matriz Normal\n";
    int input;
    cout << "Digite aqui: ";
    cin >> input;


    /* CÁLCULO DO VETOR d PELA MATRIZ INVERSA */
    if (input == 1){
        
        // Crio uma matriz identidade na heap
        double** matriz_identidade = new double*[n];
        for(int i = 0; i < n; i++){ 
            matriz_identidade[i] = new double[n];
        }


        // Defino a matriz identidade com 1s na diagonal e 0s no resto dela
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if(i == j){
                    matriz_identidade[i][i] = 1;
                } else{
                    matriz_identidade[i][j] = 0;
                }
            }
        }


        // DEBUG: Mostrando os dados na matriz identidade
        cout << "\nMatriz identidade completa:" << endl;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                cout << matriz_identidade[i][j] << ' ';
            }
            cout << endl;
        }
        cout << endl;


        // Crio uma matriz inversa na heap
        double** matriz_inversa = new double*[n];
        for(int i = 0; i < n; i++){ 
            matriz_inversa[i] = new double[n];
        }


        // A questão pede para que seja criado uma coluna da inversa de cada vez
        // utilizando uma coluna da matriz identidade de cada vez. E isso é feito
        // usando múltiplos métodos de Gauss-Seidel.
        for(int i = 0; i < n; i++){
            // Vetor identidade será cada coluna de uma matriz identidade
            double* vetor_identidade = new double[n]; 

            for(int j = 0; j < n; j++){
                // Capturo uma coluna apenas e armazeno no vetor identidade
                vetor_identidade[j] = matriz_identidade[j][i]; 
            }

            // Passo diretamente uma cópia da matriz original usando 
            // deepcopy_matriz().matriz, assim a matriz original não se perde.
            Vetor* res = seidel(deepcopy_matriz(matriz, n).matriz, vetor_identidade, tol, n, metodo_jacobi);

            // Deleto e vou criando outra coluna identidade pra não encher a memória
            delete[] vetor_identidade;

            // Com o x que armazena o resultado do método de Gauss-Seidel, vou
            // preenchendo a matriz inversa zerada coluna por coluna.
            for (int j = 0; j < n; j++){
                matriz_inversa[j][i] = res->resultado[j];
            }
        }


        // Mostrando os dados na matriz inversa (a questão pede)
        cout << "\nMatriz inversa completa:" << endl;
        for (int i = 0; i < n; i++){
            cout << "[";
            for (int j = 0; j < n; j++){
                cout << matriz_inversa[i][j] << ' ';
            }
            cout << "]";
            cout << endl;
        }
        cout << endl;

        double somatorio;

        // Faço o produto de A^(-1)*b e obtenho o vetor d de incógnitas.
        Vetor* vetor_d = produto_Ab(matriz_inversa, b, n);
        

        // Mostrando os dados da matriz d de incógnitas (a questão pede)
        cout << "\nVETOR d:" << endl;
        cout << "[";
        for(int i = 0; i < n; i++){
            if(i == n-1){ // Se for o último elemento
                cout << vetor_d->resultado[i]; // Não printa a vírgula
            }
            else{
                cout << vetor_d->resultado[i] << ", ";
            }
        }
        cout << "]";


        /* DELETANDO TUDO QUE FOI CRIADO NESSE CONDICIONAL */

        // Deletando as linhas dessas matrizes
        for (int i = 0; i < n; i++){
            delete[] matriz_identidade[i];
            delete[] matriz_inversa[i];
        }

        // Deletando as colunas dessas matrizes
        delete[] matriz_identidade;
        delete[] matriz_inversa;

        // Deletando o vetor de resultados, já que não usarei mais
        delete[] vetor_d;

     /* CÁLCULO DO VETOR d PELA MATRIZ ORIGINAL */
    } else if (input == 2){
        Vetor* res = seidel(deepcopy_matriz(matriz, n).matriz, b, tol, n, metodo_jacobi);

        // Mostrando os dados da matriz d de incógnitas (a questão pede)
        cout << "\nVETOR d:" << endl;
        cout << "[";
        for(int i = 0; i < n; i++){
            if(i == n-1){ // Se for o último elemento
                cout << res->resultado[i]; // Não printa a vírgula
            }
            else{
                cout << res->resultado[i] << ", ";
            }
        }
        cout << "]";

        // Deletando o vetor de resultados e o objeto res
        delete res;


    /* QUALQUER OUTRA COISA DIGITADA SAI DO PROGRAMA */
    } else{
        cout << "Erro: valor inválido. Saíndo..." << endl;
        exit(0);
    }


    /* DELETANDO TUDO CRIADO NA HEAP DA MEMÓRIA */

    // Deletando as linhas da matriz original
    for (int i = 0; i < n; i++){
        delete[] matriz[i];
    }

    // Deletando as colunas da matriz original
    delete[] matriz;


    // Deletando vetor b
    delete[] b;

}