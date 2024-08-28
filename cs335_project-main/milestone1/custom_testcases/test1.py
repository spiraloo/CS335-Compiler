def merge_sort(arr):
  if len(arr) <= 1:
    return arr

  # Split the array into two halves
  mid = len(arr) // 2
  left_half = arr[:mid]
  right_half = arr[mid:]
  # Recursively sort each half
  left_half = merge_sort(left_half)
  right_half = merge_sort(right_half)
  
  # Merge the sorted halves
  return merge(left_half, right_half)

def merge(left_half, right_half):
  merged = []
  left_index, right_index = 0, 0
 
  # Compare elements from both halves and merge them in sorted order
  while left_index < len(left_half) and right_index < len(right_half):
    if left_half[left_index] < right_half[right_index]:
      merged.append(left_half[left_index])
      left_index += 1
    else:
      merged.append(right_half[right_index])
      right_index += 1

  # Append remaining elements from the left half
  while left_index < len(left_half):
    merged.append(left_half[left_index])
    left_index += 1

  # Append remaining elements from the right half
  while right_index < len(right_half):
    merged.append(right_half[right_index])
    right_index += 1

  return merged

# Example usage:
def main():
  arr = [12, 11, 13, 5, 6, 7]
  sorted_arr = merge_sort(arr)
  print("Sorted array:", sorted_arr)

if __name__ == "__main__":
  main()

