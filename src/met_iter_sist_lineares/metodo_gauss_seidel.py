from __future__ import division
import numpy as np


def gauss_seidel(A, b, x0, N):

    A = A.astype('double')
    b = b.astype('double')
    x0 = x0.astype('double')
    n = np.shape(A)[0]
    x = np.copy(x0)
    it = 0
    # iteracoes
    while (it < N):
        it = it + 1
        # iteracao de Gauss Seidel
        for i in np.arange(n):
            x[i] = b[i]
            for j in np.concatenate((np.arange(0, i), np.arange(i + 1, n))):
                x[i] -= A[i, j] * x[j]
            x[i] /= A[i, i]
        # prepara nova iteracao
        x0 = np.copy(x)

    print(x)


def main():
    A = np.array([
        [-1, 0, 0, 1],
        [4, 10, -3, 2],
        [2, 0, 5, -3],
        [4, 1, 0, 6]
    ])

    b = np.array([
        [-2],
        [5],
        [11],
        [7]
    ])

    x0 = np.array([
        [-1],
        [1],
        [-1],
        [-1]
    ])

    N = 1000

    gauss_seidel(A, b, x0, N)


if __name__ == "__main__":
    main()