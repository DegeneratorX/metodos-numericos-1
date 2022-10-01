from math import e as euler, cos, sin

class MetodosBasicos:
    # Atributos private

    def __init__(self, x, tol) -> None:
        self.__x = x
        self.__tol = tol


    def __f(x):
        return -((euler**x)/2) + 2*cos(x)


    def __dxf(x):
        return -((4*sin(x)+euler**x)/2)

    # Atributos public

    @property
    def get_x(self):
        return self.x


    @get_x.setter
    def set_x(self, x):
        self__x = x


    def bissecao(f, a, b, tol, max_iter = 50):  # f = função. a,b = intervalo, tol = tolerância (limite), max_iter = máxima iteração possível. Para evitar loopings infinitos.
        Fa = f(a)
        Fb = f(b)

        if Fa * Fb > 0:  # Se multiplicar esses dois e não mudar de sinal, significa que ou os dois são positivos ou são negativos. Portanto, o intervalo [a,b] não possui linha que cruza a absissa (raíz).
            print("Erro, a função não muda de sinal.")
            return (False, None)  # Portanto, o intervalo não possui raíz.

        print("k\t a\t\t fa\t\t b\t\t fb\t\t x\t\t fx\t\tintervX")

        intervX = abs(b - a)  # abs = módulo, valor absoluto. Intervalo real entre a e b.
        x = (a+b)/2  # Ponto médio entre o intervalo
        Fx = f(x)  # Vejo o novo valor a partir do ponto médio para criar um novo intervalo.

        print("-\t%e\t%e\t%e\t%e\t%e\t%e\t%e" % (a, Fa, b, Fb, x, Fx, intervX))

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

            intervX = abs(b - a)  # Refaço o intervalo novo
            x = (a+b)/2
            Fx = f(x)

            print("%d\t%e\t%e\t%e\t%e\t%e\t%e\t%e" % (k, a, Fa, b, Fb, x, Fx, intervX))

            if (intervX <= tol):  # Se o novo intervalo estiver dentro da tolerância, então a raíz está encontrada.
                return (True, x)

            k = k+1
        print("Erro, número máximo de iterações atingido")
        return (False, x)


    def posicao_falsa(f, a, b, tol, iter_max = 20):
        Fa = f(a)
        Fb = f(b)
        if Fa * Fb > 0:
            print("Erro, a função não muda de sinal")
            return (False, None)

        intervX = abs(b-a)

        if intervX <= tol:
            return (True, x)
        if abs(f(a)) <= tol:
            return (True, a)
        if abs(f(b)) <= tol:
            return (True, b)

        k = 1

        print("k\t a\t\t fa\t\t b\t\t fb\t\t x\t\t fx\t\tintervX")

        while k <= iter_max:
            x = (a * f(b) - b * f(a))/(f(b) - f(a))
            Fx = f(x)

            print("%d\t%e\t%e\t%e\t%e\t%e\t%e\t%e" % (k, a, Fa, b, Fb, x, Fx, intervX))

            if abs(Fx) <= tol:
                return (True, x)

            if Fa * Fx > 0:
                a = x
                Fa = Fx
            else:
                b = x
                Fb = Fx
            
            intervX = abs(b-a)

            if intervX <= tol:
                return (True, x)
            k += 1

        print("Erro, número máximo de iterações atingido")
        return (False, x)

        