def orientation(p, q, r):
  val = (q[1] - p[1]) * (r[0] - q[0]) - (q[0] - p[0]) * (r[1] - q[1])
  if val == 0:
    return 0
  return 1 if val > 0 else 2

def convex_hull(points):
  n = len(points)
  if n < 3:
    return None

  hull = []
  l = 0
  for i in range(1, n):
    if points[i][0] < points[l][0]:
      l = i

  p = l
  while True:
    hull.append(points[p])
    q = (p + 1) % n

    for i in range(n):
      if orientation(points[p], points[i], points[q]) == 2:
        q = i

    p = q

    if p == l:
      break

  return hull

# Example usage:
def main():
  points = [(0, 3), (1, 1), (2, 2), (4, 4), (0, 0), (1, 2), (3, 1), (3, 3)]
  hull = convex_hull(points)
  print("Convex Hull:", hull)

if __name__ == "__main__":
  main()

