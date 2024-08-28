class Merger:
  def __init__(self, arr1, arr2):
    self.arr1 = arr1
    self.arr2 = arr2

  def merge(self):
    merged = []
    i, j = 0, 0

    while i < len(self.arr1) and j < len(self.arr2):
      if self.arr1[i] < self.arr2[j]:
        merged.append(self.arr1[i])
        i += 1
      else:
        merged.append(self.arr2[j])
        j += 1

    while i < len(self.arr1):
      merged.append(self.arr1[i])
      i += 1

    while j < len(self.arr2):
      merged.append(self.arr2[j])
      j += 1

    return merged

# Example usage:
def main():
  arr1 = [1, 3, 5, 7]
  arr2 = [2, 4, 6, 8]
  merger = Merger(arr1, arr2)
  print("Merged array:", merger.merge())

if __name__ == "__main__":
  main()
