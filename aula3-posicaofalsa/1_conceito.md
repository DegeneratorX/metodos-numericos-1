# Método da Posição Falsa

- Muito semelhante ao método da bisseção. Utiliza uma reta secante que deverá cortar o gráfico da função de forma que essa reta secante seja traçada entre os pontos (a, f(a)) e (b, f(b)) 

- Passos:
    - Entrada: a,b, ε (tolerância), iterMax (máximo número de iterações do algoritmo)
    - Saída: raíz ξ (ksi)

    - Critérios de parada:
        - Módulo do tamanho do intervalo
        - Módulo da função

    - Declarar: Fa, Fb
    - Verificar se o sinal muda de um intervalo pra outro
    - Verificar se o intervalo já atingiu a tolerância
    - Verificar se a raíz é algum dos extremos do intervalo
    - Depois começa a iteração, com k = 1 até iterMax.
    - Calcular x e f(x), mostrar tabela com valores debugados de k, a, Fa, Fb, x, Fx, intervX.
    - Verifico se x é raiz. Se for, retorna.
    - Se não, atualizo os valores de a, Fa ou b, Fb
    - Calculo o tamanho do novo intervalo, e testo se é pequeno suficiente. Se for, retorno x como raíz.
    - incremento k. Se k atingir o iterMax, mostro um erro.