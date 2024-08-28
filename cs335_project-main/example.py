# def bubbleSort(array: list[int]) -> None:
#   i: int = 0
#   for i in range(len(array)):
#     swapped: bool = False
#     j: int = 0
#     for j in range(0, len(array) - i - 1):
#       if array[j] > array[j + 1]:
#         temp: int = array[j]
#         array[j] = array[j + 1]
#         array[j + 1] = temp
#         swapped = True
#     if not swapped:
#       break


# def main():
#   data: list[int] = [-2, 45, 0, 11, -9]
#   bubbleSort(data)

#   print('Sorted Array in Ascending Order:')
#   i: int = 0
#   for i in range(len(data)):
#     print(data[i])


# if __name__ == "__main__":
#   main()

class A:
    def __init__(self,x:int,y:int,z:str)->None:
        self.a : int = x
        self.b : int = y
        self.z : str = z
    def add(self):
        return 5

# class B(A):
#     def __init__(self):
#         self.chap : float = 30
#     def subtract(self):
#         return self.c - self.b

# # def amay(alpha : int,beta: float,gamma: bool) -> list[int]:
# #     # a : A = A()
# #     # def __init__(self,x:int,y:int,z:str)->None:
# #       # self.x : int = x
# #       # self.chap : int = x
# #       # self.y : int = y
# #       # self.z : str = z
# #     # print("amay")
# #     # print(a.add())
# # #     return a

# def add(a:int,b:int) -> int:
#     a = 10
#     b = 20
#     return a+b

# # def subtract (a:int,b:int) -> int:
# #     c: int = add(a,b)
# #     return c - b

# # def main():
# #     a: int = 10
# #     b: int = 20
# #     c.x: int = add(a,b)
# #     print(c)
# #     d: int = subtract(a,b)
# #     print(d)
# #     print("Hello World")



def main():
  a : int = 10
  # alpha : A = A()
  # beta : B = B()
  # b : float = 16.00
  # c : str = "rajani"
  # A.x[5] = 10
  alpha : list[int] = [1,2,3,4,5,6]
  alpha[5] = 10
  # add(alpha[3],alpha[4])
  # a : A = A

  # for i in range(3,10):
  #   print(30)
  # amay(1,2.0,False)
  # b : int = amay(3,4.0,True)
  print("bho")

if __name__ == "__main__":
    main()                                                                      
