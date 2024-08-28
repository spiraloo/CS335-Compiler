# Python3 program to sort an array using
# merge sort such that merge operation
# takes O(1) extra space.

def max(array:list[int], n: int) ->int:
#   """Finds the maximum element of an array.

#   Args:
#     array: A list of numbers.

#   Returns:
#     The maximum element of the array.
#   """
  max_element: int = array[0]
  element:int 
  i : int 
  for i in range(n):
    element = array[i]
    if element > max_element:
      max_element = element
  return max_element

def merge(arr: list[int], beg: int, mid: int , end: int, maxele: int) -> None:

  i:int = beg
  j:int = mid + 1
  k:int = beg
  while (i<=mid and j<=end):
    if (arr[i] % maxele <= arr[j] % maxele):
      arr[k] = arr[k] + ((arr[i] % maxele) * maxele)
      k += 1
      i += 1
    else:
      arr[k] = arr[k] + ((arr[j] % maxele) * maxele)
      k += 1
      j += 1
  while (i <= mid):
    arr[k] = arr[k] + ((arr[i] % maxele) * maxele)
    k += 1
    i += 1
  while (j <= end):
    arr[k] = arr[k] + ((arr[j] % maxele) * maxele)
    k += 1
    j += 1

    # Obtaining actual values
  end+=1
  for i in range(beg, end):
    arr[i] = arr[i] / maxele

  return

# Recursive merge sort with extra 
# parameter, naxele
def mergeSortRec(arr:list[int], beg:int, end:int, maxele:int):

  if beg < end:
    mid : int = (beg + end) / 2
    mergeSortRec(arr, beg, mid, maxele)
    mergeSortRec(arr, mid + 1, end, maxele)
    merge(arr, beg, mid, end, maxele)
  return

# This functions finds max element and 
# calls recursive merge sort.
def mergeSort(arr: list[int], n: int)-> None:

  maxele: int = max(arr, n) + 1
  mergeSortRec(arr, 0, n - 1, maxele)
  return

def main():
  arr:list[int] = [ 999, 612, 589, 856, 56, 945, 243 ]
  n:int = len(arr)
  mergeSort(arr, n)

  print("Sorted array")
  i : int 
  
  for i in range(n):
    print(arr[i])
# Driver Code
if __name__ == '__main__':
  main()

