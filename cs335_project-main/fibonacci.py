def recursive_fibonacci(n:int) ->int:
  if n <= 1:
      return n
  else:
      return(recursive_fibonacci(n-1) + recursive_fibonacci(n-2))
def main():
  n_terms : int = 10
  if n_terms <= 0:
    print("Invalid input ! Please input a positive value")
  else:
    print("Fibonacci series:")
  i : int = 0
  for i in range(n_terms):
      print(recursive_fibonacci(i))

if __name__ == "__main__":
  main()
