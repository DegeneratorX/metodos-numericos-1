- Na introdução à teoria dos erros,  vamos analisar dois casos de três.

    - Construir modelo matemático e observar os erros de modelagem: não

    - Escolher método numérico adequado e observar os erros de aproximação: sim
    
    - Implementar método computacionalmente e observar erros de resolução(limitação do equipamento): sim

- Cálculo envolvendo números que não podem ser representados por um número finito de dígitos não fornecerá resultado exato. Quanto maior o número de dígitos utilizado, maior a precisão.

- Entada de Dados (base10) -> Operações no PC (base2) -> Saída de Dados (base10)

    - Ao fazer a conversão para base 2, pode ocorrer erros.
    
    - Um número pode ter representação finita em uma base e não-finita em outras bases.

- Podemos representar qualquer número real (base 10) em qualquer base da seguinte forma:

    - #TODO: Botar imagem da fórmula do somatório.

- Exemplos:

    - (1011)₂ = 1 * 2⁰ + 1 * 2¹ + 0 * 2² + 1 * 2³

    - (111.01)₂ = 1 * 2⁻² + 0 * 2⁻¹ + 1 * 2⁰ + 1 * 2¹ + 1 * 2²

    - (231)₁₀ = 1 * 10⁰ + 3 * 10¹ + 2 * 10²

    - (231.35)₁₀ = 5 * 10⁻² + 3 * 10⁻¹ + 1 * 10⁰ + 3 * 10¹ + 2 * 10²

- Mudança de base binária pra decimal:

    - Procedimento: somar os valores acima.
    - (1011)₂ = 1 * 2⁰ + 1 * 2¹ + 0 * 2² + 1 * 2³ = 11
    - (111.01)₂ = 1 * 2⁻² + 0 * 2⁻¹ + 1 * 2⁰ + 1 * 2¹ + 1 * 2²

- Base decimal para base binária (inteira e fracionária):

    - (13.25)₁₀ = 13 + 0.25
    - 13/2, resto 1, resultado 6.
    - 6/2, resto 0, resultado 3.
    - 3/2, resto 1, resultado 1.
    - Pega o último resultado, e depois os restos de trás pra frente.
    - (13)₁₀ = (1101)₂.
    - Realizando agora a parte fracionária, realizamos o inverso. Multiplicamos por 2 até a parte fracionária chegar em 0.
    - Temos: 0.25*2 = 0.50. Parte inteira de 0.5 = 0. Fracionária = 0.5
    - 0.50*2 = 1.0. Parte inteira de 1.0 = 1. Fracionária = 0.0
    - Pego em ordem a parte inteira, esse serão os bits.
    - Conclusão: 13.25 = 1101.01

- Agora a mágica: base decimal para binária usando esse número: (0.11)₁₀

    - 0.11*2 = 0.22
    - 0.22*2 = 0.44
    - 0.44*2 = 0.88
    - 0.88*2 = 1.76
    - 0.76*2 = 1.52
    - 0.52*2 = 1.04
    - 0.04*2 = 0.08
    - Assim vai infiinitamente. Ou seja, precirei truncar. Não é exatamente representável. Com os valores acima, representamos como (0.11)₁₀ = (0.0001110)₂