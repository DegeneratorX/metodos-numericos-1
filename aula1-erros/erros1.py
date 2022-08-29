"""
Na introdução à teoria dos erros,  vamos analisar dois casos de três.

Construir modelo matemático e observar os erros de modelagem: não
Escolher método numérico adequado e observar os erros de aproximação: sim
Implementar método computacionalmente e observar erros de resolução(limitação do equipamento): sim

Cálculo envolvendo números que não podem ser representados por um número finito
de dígitos não fornecerá resultado exato.

Quanto maior o número de dígitos utilizado, maior a precisão.

Entada de Dados (base10) -> Operações no PC (base2) -> Saída de Dados (base10)
Ao fazer a conversão para base 2, pode ocorrer erros.
Um número pode ter representação finita em uma base e não-finita em outras bases.

Podemos representar qualquer número em qualquer base da seguinte forma:

   

"""

# Exemplo: somatório:

sum = 0

for i in range(30000):
    sum = sum + 0.11

print(sum)