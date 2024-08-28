class Chessboard:
  def __init__(self, size=8):
    self.board_size = size
    self.board = []
    for _ in range(size):
      self.board.append([0] * size)

  def display_board(self):
    for row in self.board:
      print(" ".join(map(str, row)))

  def is_valid_position(self, row, col):
    return 0 <= row < self.board_size and 0 <= col < self.board_size

  def get_possible_moves(self, row, col):
    possible_moves = []
    knight_moves = [(2, 1), (1, 2), (-1, 2), (-2, 1), (-2, -1), (-1, -2), (1, -2), (2, -1)]
    for dx, dy in knight_moves:
      new_row, new_col = row + dx, col + dy
      if self.is_valid_position(new_row, new_col):
        possible_moves.append((new_row, new_col))
    return possible_moves

  def get_possible_moves_b(self, row, col):
    possible_moves = []
    for i in range(1, self.board_size):
      directions = [(-i, -i), (-i, i), (i, -i), (i, i)]
      for dx, dy in directions:
        new_row, new_col = row + dx, col + dy
        if self.is_valid_position(new_row, new_col):
          possible_moves.append((new_row, new_col))
    return possible_moves

  def get_possible_moves_rook(self, row, col):
    possible_moves = []
    for i in range(1, self.board_size):
      directions = [(0, i), (0, -i), (i, 0), (-i, 0)]
      for dx, dy in directions:
        new_row, new_col = row + dx, col + dy
        if self.is_valid_position(new_row, new_col):
          possible_moves.append((new_row, new_col))


# Example usage:
def main():
  chessboard = Chessboard()
  print("Knight moves at (3, 3):", chessboard.get_possible_moves_k(3, 3))
  print("Bishop moves at (4, 4):", chessboard.get_possible_moves_b(4, 4))
  print("Rook moves at (5, 5):", chessboard.get_possible_moves_rook(5, 5))

if __name__ == "__main__":
  main()
