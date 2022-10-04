from math import e as euler, sin, cos

def f(x): return -((euler**x)/2) + 2*cos(x)

def bissecao(f, a, b, tol, aprox = 4, max_iter = 50):  # f = função. a,b = intervalo, tol = tolerância (limite), max_iter = máxima iteração possível. Para evitar loopings infinitos.
    Fa = round(f(a), aprox)
    Fb = round(f(b), aprox)

    if Fa * Fb > 0:  # Se multiplicar esses dois e não mudar de sinal, significa que ou os dois são positivos ou são negativos. Portanto, o intervalo [a,b] não possui linha que cruza a absissa (raíz).
        print("Erro, a função não muda de sinal.")
        return (False, None)  # Portanto, o intervalo não possui raíz.

    print("k\t a\t\t b\t\t x\t\t fx")

    intervX = round(abs(b - a), aprox)  # abs = módulo, valor absoluto. Intervalo real entre a e b.
    x = round((a+b)/2, aprox)  # Ponto médio entre o intervalo
    Fx = round(f(x), aprox)  # Vejo o novo valor a partir do ponto médio para criar um novo intervalo.
    k = 0
    print("%d\t%e\t%e\t%e\t%e" % (k, a, b, x, Fx))

    if (intervX <= tol):  # Se o intervalo entre a e b for maior que a tolerância, então ainda tem mais coisas pra checar. Se não, então já achou a raíz (por sorte, em 1 iteração apenas)
        return (True, x)
    
    k = 1  # A partir do caso base acima, vamos iterar mais vezes até achar a raíz desejada, começando com k = 1.

    while k <= max_iter:  # Enquanto esse k não atingir o máximo de iterações definido pelo usuário (ou ficará em um loop eterno se não achar nada...)
        if Fa * Fx > 0:  # Vejo se a raíz pode estar entre a e x ou entre x e b (pra esquerda ou pra direita).
            a = x  # Se a raíz está pro lado esquerdo, a se torna o novo x.
            Fa = Fx  # E obviamente, a função aplicada também se torna a mesma.
        else:  
            b = x  # Se não, então b se torna o novo x.
            Fb = Fx

        intervX = round(abs(b - a), aprox)  # Refaço o intervalo novo
        x = round((a+b)/2, 4)
        Fx = round(f(x), 4)

        print("%d\t%e\t%e\t%e\t%e" % (k, a, b, x, Fx))

        if (intervX <= tol):  # Se o novo intervalo estiver dentro da tolerância, então a raíz está encontrada.
            return (True, x)

        k = k+1
    print("Erro, número máximo de iterações atingido")
    return (False, x)


a = float(input("Digite o a: "))
b = float(input("Digite o b: "))
tol = float(input("Digite a tolerância: "))
aprox = int(input("Digite o número de casas decimais a ser trabalhada: "))


(sem_erro, raiz) = bissecao(f, a, b, tol, aprox)

if sem_erro == False:
    print("O método retornou um erro.")
if raiz is not None:
    print(f"Raíz: {raiz}")