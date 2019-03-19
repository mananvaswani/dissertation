import matplotlib.pyplot as plt
import numpy as np

from matplotlib.pyplot import figure, show
from matplotlib.ticker import MaxNLocator

x, y = np.loadtxt('timings.csv', delimiter=',', unpack=True)
ax = figure().gca()

ax.plot(x, y)

ax.set_xlabel('n')
ax.set_ylabel('time (in milliseconds)')
plt.title('Number of input modes v. Time taken')

ax.xaxis.set_major_locator(MaxNLocator(integer=True))

show()

# plt.plot(x,y)
#
# plt.xlabel('n')
# plt.ylabel('time (in milliseconds)')
# plt.title('Number of input modes v. Time taken')
#
# gca().get_xaxis().get_major_formatter().set_useOffset(False)
#
# plt.legend()
# plt.show()
