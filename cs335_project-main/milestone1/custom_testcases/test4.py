class LongestCommonSubsequence:
  def __init__(self, s1, s2):
    self.s1 = s1
    self.s2 = s2

  def find_longest_common(self):
    m = len(self.s1)
    n = len(self.s2)

    # Initialize a table to store lengths of longest common subsequences
    # dp[i][j] will store the length of the longest common subsequence ending at s1[i-1] and s2[j-1]
    dp = []
    for i in range(m + 1):
      inner_list = [0] * (n + 1)
      dp.append(inner_list)

    # Fill dp table bottom-up
    for i in range(1, m + 1):
      for j in range(1, n + 1):
        if self.s1[i - 1] == self.s2[j - 1]:
          dp[i][j] = dp[i - 1][j - 1] + 1
        else:
          dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])

    # Length of longest common subsequence is stored in dp[m][n]
    return dp[m][n]

# Example usage:
def main():
  s1 = "abcdefg"
  s2 = "bcdeft"
  lc_subsequence = LongestCommonSubsequence(s1, s2)
  print("Length of longest common subsequence:", lc_subsequence.find_longest_common())

if __name__ == "__main__":
  main()
