from copy import deepcopy


"""
Gauss Seidel (Bônus Gauss Jordan). Feito por Victor Martins

O programa tem a possibilidade de calcular o vetor d que a questão pede de duas
formas: método normal A*x = b e usando inversa A^(-1)*b = x, sendo b o vetor
de soluções (no caso é o d da questão).

Fiz esse programa primeiro em python para testar a lógica e os resultados, 
depois portei pro C++. Portanto, usei biblioteca nesse.

É impressionante a quantidade de linhas economizadas para fazer exatamente a
mesma coisa. E como o Python possui garbage collector, ou seja, não precisei 
deletar objetos na memória alocados na Heap.
"""


# Algoritmo que calcula o produto de duas matrizes. Só funciona para matrizes
# que multiplicam (nxn * n).
def produto_ab(matriz_inversa, b, n):
    vetor_d = [0 for i in range(n)]
    for i in range(n):
        for j in range(n):
            somatorio = 0
            for k in range(n):
                somatorio = somatorio + matriz_inversa[i][k]*b[k]
            vetor_d[i] = somatorio
    return vetor_d

# Compara o próximo resultado com o anterior, é o teste de parada
def teste_parada(v, x, n):
    # Maior numerador e maior denominador
    maxnum = 0
    maxden = 0

    # Procura o valor máximo de cada matriz
    for i in range(0, n):
        num = abs(v[i] - x[i])
        if num > maxnum:
            maxnum = num
        den = abs(v[i])
        if den > maxden:
            maxden = den

    # Retorna a divisão do maior número de cada matriz
    return maxnum / maxden


# Método numérico Gauss-Seidel.
def seidel(A, b, epsilon, n, metodo_jacobi, limite=50):
    x = n * [0] # Inicializo o vetor x
    v = n * [0] # Inicializo o vetor v (vetor x anterior) e a distância d (teste de parada)

    
    # Criação de um novo sistema linear no formato
    # x{k+1} = C * x{k} * (b[i]/matriz[i][i])
    # Onde C é a matriz das constantes geradas dividindo
    # todos os elementos matriz[i][j] por matriz[i][i] (menos a diagonal)
    # x{k} é o novo vetor de x a partir desse novo sistema.
    for i in range(0, n):
        for j in range(0, n):
            # Ignoro a diagonal dos elementos de C, pois C não terá diagonal definida
            if i != j:
                A[i][j] = A[i][j] / A[i][i]
        b[i] = b[i] / A[i][i]

        # Se for Jacobi, inicializo o vetor x com aproximação inicial
        # b[i]/matriz[i][i], que já é o próprio b[i] acima
        if metodo_jacobi:
            x[i] = b[i]

        
    # Iterações
    for k in range(1, limite + 1):
        for i in range(0, n):
            somatorio = 0
            for j in range(0, n):
                # Ignoro a diagonal dos elementos de C, pois C não tem diagonal definida
                if i != j:
                    # Lembrando que o sistema novo criado é no formato
                    # x{k+1} = C * x{k} * (b[i]/matriz[i][i]). Essa
                    # Operação multiplica a matriz C pelo vetor x{k}.
                    somatorio = somatorio + A[i][j] * x[j]
            # Jacobi: preencho o vetor v, que será o vetor anterior.
            # Seidel: Vou preenchendo novo vetor x já recebendo valores anteriores em
            # tempo real para a próxima iteração
            if metodo_jacobi:
                v[i] = b[i] - somatorio
            else:
                x[i] = b[i] - somatorio

        # Fechou o vetor x ou v, agora faz o teste de parada e compara com o vetor
        # anterior. O teste de parada pra Jacobi é o inverso do de Seidel
        if metodo_jacobi:
            d = teste_parada(v, x, n)
        else:
            d = teste_parada(x, v, n)

        if d <= epsilon: # Se for menor que a tolerância, acabou.
            if metodo_jacobi:
                # Se for Jacobi, retorno o último vetor calculado (v)
                return v
                # Se for Seidel, retorno o vetor mais atualizado possível.
            else: 
                return x
        # Se não é menor que a precisão, continua o método.


        # Se for Jacobi, x vai receber o novo vetor v que acabei de calcular.
        if metodo_jacobi:
            x = v[:]
        # Se for Seidel, faço uma cópia do vetor x pro vetor anterior. 
        # Pois o novo x será modificado e o atual virará o anterior (v).
        else:
            v = x[:]
        # Uso slice para fazer uma cópia profunda para evitar referências em python.

    print("Erro! Número máximo de iterações atingido.")
    return


n = int(input("Digite a ordem N da matriz: "))

matriz = [[0 for x in range(n)] for y in range(n)]  # Inicializo a matriz vazia via list comprehension
b = [0 for x in range(n)]
matriz_identidade = deepcopy(matriz) # Faço uma cópia para não precisar fazer list comp. mais de uma vez
matriz_inversa = deepcopy(matriz)

# Enfiando dados na matriz
print(f" Digite os número na matriz A de ordem {n}")
for i in range(n):
    for j in range(n):
        matriz[i][j] = float(input(f"Digite o elemento na linha {i + 1} e coluna {j + 1}: "))

# Preenchendo o vetor b
print("Digite os elementos do vetor b.")
for i in range(n):
    b[i] = float(input(f"Digite o elemento {i + 1}: "))

    
# Tolerância
tol = float(input("\nDigite a tolerância com que se deseja trabalhar (precisão): "))

# Qual método o usuário quer utilizar
metodo_jacobi = False
print("\nVocê deseja calcular o vetor de soluções através do método de Gauss-Jacobi ou método de Gauss-Seidel?")
print("\n1 - Método de Gauss-Jacobi\n2 - Método de Gauss-Seidel\nQualquer outro valor - Sair\n")
metodo_escolhido = int(input("Digite aqui: "))
if metodo_escolhido == 1: 
    metodo_jacobi = True 
elif metodo_escolhido == 2:
    pass
else: exit()


# O que o usuário deseja fazer
print("\nVocê deseja calcular o vetor de soluções através do método normal Ad = b ou pela inversa A^(-1)*b = d?")
print("1 - Usando Inversa")
print("2 - Usando Matriz Normal")

escolha = int(input("Digite aqui: "))
print()


# CÁLCULO DO VETOR d PELA MATRIZ INVERSA #
if (escolha == 1):

    # Defino a matriz identidade com 1s na diagonal e 0s no resto dela
    for i in range(n):
        for j in range(n):
            if i == j:
                matriz_identidade[i][i] = 1
            else:
                matriz_identidade[i][j] = 0

    
    # A questão pede para que seja criado uma coluna da inversa de cada vez
    # utilizando uma coluna da matriz identidade de cada vez. E isso é feito
    # usando múltiplos métodos de Gauss-Seidel.
    for i in range(n):
        # Vetor identidade será cada coluna de uma matriz identidade
        vetor_identidade = [0 for x in range(n)]

        for j in range(n):
            # Capturo uma coluna apenas e armazeno no vetor identidade
            vetor_identidade[j] = matriz_identidade[j][i]

        # Passo diretamente uma cópia da matriz original usando 
        # deepcopy, assim a matriz original não se perde.
        # No python, listas(arrays) pode sofrer mudanças por referência,
        # mesmo a linguagem não possuindo ponteiros. Porém, por trás existe
        # ponteiros. É um dos raros objetos, assim como dicionários, que
        # possuem esse comportamento.
        x = seidel(deepcopy(matriz), vetor_identidade, tol, n, metodo_jacobi)

        # Com o x que armazena o resultado do método de Gauss-Seidel, vou
        # preenchendo a matriz inversa zerada coluna por coluna.
        for j in range(n):
            matriz_inversa[j][i] = x[j]

            
    # Mostrando os dados da matriz inversa
    print("Matriz inversa completa: ")
    for i in range(n):
        print(matriz_inversa[i])

    # Faço o produto de A^(-1)*b e obtenho o vetor d de incógnitas.
    vetor_d = produto_ab(matriz_inversa, b, n)

    # Mostrando os dados do vetor d de incógnitas
    print(f"VETOR d: \n{vetor_d}")


# CÁLCULO DO VETOR d PELA MATRIZ ORIGINAL #
elif escolha == 2:
    x = seidel(deepcopy(matriz), b, tol, n, metodo_jacobi)

    # Mostrando os dados da matriz d de incógnitas
    print(f"VETOR d: \n{x}")


# QUALQUER OUTRA COISA DIGITADA SAI DO PROGRAMA #
else:
    print("Erro: valor inválido. Saíndo...")
    exit()