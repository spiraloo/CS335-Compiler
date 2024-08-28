def max(a:int, b:int)->int:
    if a > b:
        return a
    else:
        return b

def knapSack(W :int , wt :list[int], val:list[int], n:int)->int:
    # Base Case
    if n == 0 :
        return 0
    if (W == 0):
        return 0

    # If weight of the nth item is more




    
    # than Knapsack capacity W, then
    # this item cannot be included in the optimal solution
    gamma : int = knapSack(W, wt, val, n - 1)
    if (wt[n - 1] > W):
        print("i am here")
        return gamma

    # Return the maximum of two cases:
    # (1) nth item included
    # (2) not included
    # print("gonna be here")
    cheta : int = 9 + 89
    c : int = knapSack((W - wt[n - 1]), wt, val, n - 1)
    c = c + val[n - 1]
    print("c")
    print(c)
    g : int = 693293293
    f : int = knapSack(W, wt, val, n - 1)
    print(f)
    print("f")
    c = max(c,f)
    return c

# Driver program to test above function
def main():
    val:list[int] = [60, 100, 120]
    wt:list[int] = [10, 20, 30]
    W:int = 50
    n:int = len(val)
    print(n)
    print(knapSack(W, wt, val, n))

if __name__ == "__main__":
    main()
