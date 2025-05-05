import numpy as np
import matplotlib.pyplot as plt
import sys


def main():
    arr = np.genfromtxt(sys.stdin, delimiter=", ")
    x = arr[:, 1]
    y = arr[:, 2]

    plt.figure()
    plt.plot(x, y)
    plt.plot([450], [20], "x")
    plt.show()
    plt.close()


if __name__ == "__main__":
    main()
