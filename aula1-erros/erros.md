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

    - (13.25)₁₀ = ?