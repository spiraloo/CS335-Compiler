def bubbleSort(array: list[int]) -> None:
  i: int = 0
  l: int = len(array)
  array[i] = i
  bubbleSort(array)

def main():
  data: list[int] = [2, 45, 0, 11, 9]
  bubbleSort(data)

  print('Sorted:')
  i: int = 0
  l: int = len(data)
  
  for i in range(l):
    print(data[i])
