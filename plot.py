import matplotlib.pyplot as plt
import numpy as np

from matplotlib.pyplot import figure, show
from matplotlib.ticker import MaxNLocator

#x1, y1 = np.loadtxt('algorithm_b/timings.csv', delimiter=',', unpack=True)
x1, y1 = np.loadtxt('algorithm_b_arma/timings.csv', delimiter=',', unpack=True)

x2, y2 = np.loadtxt('org-r-code/data_r_org.csv', delimiter=',', skiprows=2, unpack=True)
x3, y3 = np.loadtxt('updated-r-code/data_r_new.csv', delimiter=',', skiprows=2, unpack=True)

ax = figure().gca()

ax.plot(x1, y1, 'b', label="Algorithm B, C++")
ax.plot(x2, y2, 'r', label="Algorithm B, original R implementation")
ax.plot(x3, y3, 'g', label="Algorithm B, updated R implementation")

ax.legend()

ax.set_xlabel('n')
ax.set_ylabel('time (in milliseconds)')
plt.title('Number of input modes v. Time taken \n(no parallelisation) \n g++ compiler, 2.9 GHz Intel Core i5 processor, 8GB RAM')

ax.xaxis.set_major_locator(MaxNLocator(integer=True))

show()
