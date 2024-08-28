class A :
    def __init__(self,a:str,b:int) ->None:
        self.a : str = a
        self.b : int = b
        self.x : list[int] = [1,2,3,4,5]
class B(A) :
    def __init__(self,a:str,b:int,c:int) ->None:
        self.c : int = c
        self.d : int = self.c + 10
        A.__init__(self,a,b)


class C(B):
    def __init__(self,a:str,b:int,c:int,d:int) ->None:
        B.__init__(self,a,b,c)
        self.e : int = d
        self.f : int = self.d + 20

def main():
    alpha : A = A("this is A",10)
    beta : B = B("this is B",9,10)
    gamma : C = C("this is C",8,9,10)
    print(alpha.a)
    print(alpha.b)
    print("alpha.x[4]")
    print(alpha.x[4])
    print(beta.a)
    print(beta.b)
    print(beta.c)
    print(gamma.a)
    print(gamma.b)
    print(gamma.c)
    print(gamma.d)
    print(gamma.e)
    print(gamma.f)
    return

if __name__ == "__main__":
    main()
