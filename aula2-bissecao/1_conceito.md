# Método da bisseção

- O objetivo é encontrar ξ (ksi). ξ é uma raíz aproximada da raíz verdadeira de uma equação qualquer. Usamos vários métodos para tentar encontrar.
    - Um deles é o método da bisseção.
    - Dada uma função f, estipulamos um intervalo [a,b], definimos uma tolerância máxima ε e um número máximo de iterações para achar o valor próximo da raíz. Se o valor estiver dentro da tolerância, imediatamente teremos um ξ de mesmo valor.
    - Se f(a) ∙ f(b) < 0 (negativo), significa que um dos dois é negativo exclusivo. Ou seja, entre o intervalo [a,b], o gráfico corta as absissas. Isso é sinal de que nesse intervalo tem uma raíz.
    - Se f(a) ∙ f(b) > 0 (positivo), significa que os dois são positivos ou negativos. Existem três interpretações:
        - O gráfico não corta as absissas;
        - Mais de uma raíz dentro desse intervalo [a,b];
        - Só uma raíz, mas o gráfico tangencia a absissa.
    - Para garantir que o intervalo [a,b] escolhido tenha apenas 1 raíz, derivamos a função. A função derivada, ao substituir x por valores entre a e b, se sempre o resultado se manter > 0 OU < 0, isso garante que só existe uma raíz.

- Passos do método da bisseção
    - f(a)∙f(b) < 0? Se sim, então a função muda de sinal. E geralmente foi dado que existe uma única raíz nesse intervalo. Se não, então nesse intervalo não tem raíz.
    - |b - a| ≤ ε? Se sim, então é hora de parar, pois atingiu a tolerância, não há a necessidade de mais aproximação. Se não, o método irá continuar.

- Iteração Teórica. Dados a, b e a tolerância ε...
    - Verificar o ponto médio x₀ = (a₀ + b₀)/2
    - Verificar pra qual lado a função muda de sinal. Se é entre [a₀,x₀] ou [x₀,b₀]. Pra isso, verifica: f(a₀), f(b₀) e f(x₀). 
    - Criando um exemplo agora, supondo que f(a₀) > 0, f(b₀) < 0 e f(x₀) < 0, observamos que f(a₀) comparado com f(x₀) muda de sinal. Já f(b₀) comparado com f(x₀), não muda. Ou seja, descartemos o intervalo [x₀,b₀].
    - Sabemos agora que ξ está entre [a₀,x₀]. Criamos novos valores a₁ e b₁.
    - O a₁ será o novo a₀ e o b₁ será o novo x₀. O processo se repete até que |bₖ - aₖ| ≤ ε.
    - No momento que |bₖ - aₖ| ≤ ε, a iteração para. O valor do meu ξ será qualquer valor que estiver nesse último intervalo [aₖ,bₖ].

- Estimativa do número de iterações
    - O único método capaz de estimar o número de iterações é o da bisseção.
    - Ou seja, o valor de k para iterações até que (bₖ - aₖ) ≤ ε
    - Somando todos os pontos médios, temos que bₖ - aₖ = (b₀-a₀)/2ᵏ ≤ ε.
    - Algebricando, chegamos a k ≥ [log(b₀ - a₀) - log(ε)] / log(2)
    - Exemplo: f(x) = x²-1, onde a = -0.25, b = 1.25 e ε = 0.2.
    - k ≥ [log(1.25+0.25) - log(0.2)]/log(2)
    - k ≥≈ 2.907. O menor inteiro que satisfaz essa inequação é k = 3.

- Vantagens:
    - Convergência garantida. Se mudar de sinal, é garantido que tem uma raíz.
    - Método robusto. Pouca chance ou nenhuma de erro.
    - Posso determinar o número de iterações antes mesmo de começar o método.

- Desvantagens:
    - Não é eficiente devido a convergência lenta, pois f(x) não decresce monotonicamente. Ou seja, sempre fica pulando de um lado pra outro no intervalo. Por exemplo, ele tá de um lado positivo, de repente ele estará no outro lado, como um pêndulo. Ou seja, ele dificilmente vai se aproximar da raíz por um só lado.
    - É preciso o isolamento prévio de cada raiz em um intervalo [a,b]