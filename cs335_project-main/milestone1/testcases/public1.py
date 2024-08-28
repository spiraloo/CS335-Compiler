def bubbleSort(array: list[int]) -> None:
  i: int = 0
  l: int = len(array)
  for i in range(l):
    swapped: bool = False
    j: int = 0
    m: int = l - i - 1
    for j in range(0, m):
      if array[j] > array[j + 1]:
        temp: int = array[j]
        array[j] = array[j + 1]
        array[j + 1] = temp
        swapped = True


def main():
  data: list[int] = [2, 45, 0, 11, 9]
  bubbleSort(data)

  print('Sorted:')
  i: int = 0
  l: int = len(data)
  
  for i in range(l):
    print(data[i])


if __name__ == "__main__":
  main()
