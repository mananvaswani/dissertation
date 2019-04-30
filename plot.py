import matplotlib.pyplot as plt
import numpy as np

from matplotlib.pyplot import figure, show
from matplotlib.ticker import MaxNLocator

#x1, y1 = np.loadtxt('algorithm_b/timings.csv', delimiter=',', unpack=True)
x1, y1 = np.loadtxt('timings_parallel.csv', delimiter=',', unpack=True)
x2, y2 = np.loadtxt('timings_serial.csv', delimiter=',', unpack=True)
# x3, y3 = np.loadtxt('updated-r-code/data_r_new.csv', delimiter=',', skiprows=2, unpack=True)

ax = figure().gca()

ax.plot(x1, y1, 'b', label="Algorithm B, Parallelised C++ implementation, 32 threads")
ax.plot(x2, y2, 'r', label="Algorithm B, Serial C++ implementation")

ax.legend()

ax.set_xlabel('n')
ax.set_ylabel('time (in milliseconds)')
plt.title('Number of input modes v. Time taken \n(no parallelisation) \n g++ compiler')

ax.xaxis.set_major_locator(MaxNLocator(integer=True))
ax.set_yscale('linear')

show()
