def sum(arr : list[int], n:int) -> int:
    if n == 0:
        return 0
    else :
        return arr[n-1] + sum(arr, n-1)

def main():
    i:int
    arr : list[int] = [1,4,9,12,14]
    print(len(arr))
    result:int = sum(arr, 5)
    print(result)

if __name__ == "__main__":
    main()
