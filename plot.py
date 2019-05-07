import matplotlib.pyplot as plt
import numpy as np

from matplotlib.pyplot import figure, show
from matplotlib.ticker import MaxNLocator

#x1, y1 = np.loadtxt('algorithm_b/timings.csv', delimiter=',', unpack=True)
n1, times1, perms1 = np.loadtxt('timings_parallel.csv', delimiter=',', unpack=True)
# n2, times2 = np.loadtxt('timings_serial.csv', delimiter=',', unpack=True)
# x3, y3 = np.loadtxt('updated-r-code/data_r_new.csv', delimiter=',', skiprows=2, unpack=True)

ax = figure().gca()

ax.plot(n1, times1, 'b', label="C++ implementation")
ax.plot(n1, perms1, 'b', label="C++ implementation")
# ax.plot(x2, y2, 'r', label="Algorithm B, Serial C++ implementation")

ax.legend()

ax.set_xlabel('n')
ax.set_ylabel('time (in milliseconds)')
plt.title('Number of input modes v. Time taken \n(no parallelisation) \n g++ compiler')

ax.xaxis.set_major_locator(MaxNLocator(integer=True))
ax.set_yscale('linear')

show()
