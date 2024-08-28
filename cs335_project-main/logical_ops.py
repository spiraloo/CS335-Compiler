def add(a:int,b:int) -> int:
    return a+b
def main():
    a : int = 5
    array : list[int] = [1,2,3,4,5]
    astr : str = "hello"
    b : int = a > 3
    c : bool = a < 3
    if (b and c):
        print("hello")
    elif (b or c):
        print("world")
    else :
        print("hello world")
    if (astr == "hello"):
        print("strcmpr works fine")
    if (astr == "world"):
        print("strcmpr not working ")
    a  = 1
    b = 2
    print(add(array[(a + (a^b))],array[b]))

if __name__ == "__main__":
    main()
