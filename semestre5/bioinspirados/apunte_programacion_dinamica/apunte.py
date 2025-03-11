import numpy as np

i = (1, 2, 3)
v = (6, 10, 12)
w = (1, 2, 3)

R = 5
N = len(i)

m = np.zeros((N+1, R+1), dtype=int)

print(m)


for row in range(1, N+1):
    for col in range(1, R+1):
        if w[row-1] > col:
            m[row][col] = m[row-1][col]
        