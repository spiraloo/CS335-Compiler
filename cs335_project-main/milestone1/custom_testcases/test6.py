class InfixToPostfix:
  def __init__(self):
    self.operators = ['+', '-', '*', '/', '^']
    self.precedence = [0, 0, 0, 0, 0]  # Precedence array corresponding to operators
    self.precedence[self.operators.index('+')] = 1
    self.precedence[self.operators.index('-')] = 1
    self.precedence[self.operators.index('*')] = 2
    self.precedence[self.operators.index('/')] = 2
    self.precedence[self.operators.index('^')] = 3

  def is_operator(self, token):
    for op in self.operators:
      if op == token:
        return True
    return False

  def is_higher_precedence(self, op1, op2):
    idx_op1 = -1
    idx_op2 = -1
    for i in range(len(self.operators)):
      if self.operators[i] == op1:
        idx_op1 = i
      if self.operators[i] == op2:
        idx_op2 = i
    return (self.precedence[idx_op1] > self.precedence[idx_op2] or (self.precedence[idx_op1] == self.precedence[idx_op2] and self.associativity[op1] == 'LR'))

  def infix_to_postfix(self, infix_expression):
    postfix_expression = []
    operator_stack = []

    for token in infix_expression.split():
      if token.isdigit():
        postfix_expression.append(token)
      elif token == '(':
        operator_stack.append(token)
      elif token == ')':
        while operator_stack and operator_stack[-1] != '(':
          postfix_expression.append(operator_stack.pop())
        operator_stack.pop()  # Discard '('
      elif self.is_operator(token):
        while (operator_stack and operator_stack[-1] != '(' and self.is_higher_precedence(operator_stack[-1], token)):
          postfix_expression.append(operator_stack.pop())
        operator_stack.append(token)

    while operator_stack:
      postfix_expression.append(operator_stack.pop())

    return ' '.join(postfix_expression)


# Example usage:
def main():
  infix_expr = "3 + 4 * 2"
  converter = InfixToPostfix()
  postfix_expr = converter.infix_to_postfix(infix_expr)
  print("Infix expression:", infix_expr)
  print("Postfix expression:", postfix_expr)

if __name__ == "__main__":
  main()

