import matplotlib.pyplot as plt
import numpy as np

from matplotlib.pyplot import figure, show
from matplotlib.ticker import MaxNLocator

n1, times1, perms1 = np.loadtxt('test_serial.csv', delimiter=',', unpack=True)

timesList = []
temp = []
for i in range(n1.size):
    temp.append(times1[i])
    if i ==(n1.size-1) or n1[i]!=n1[i+1]:
        timesList.append(temp)
        temp = []

meanTimesList = []
stdDevList = []
for ele in timesList:
    meanTimesList.append(np.mean(ele))
    stdDevList.append(np.std(ele))

print (stdDevList)

n = list(range (2, len(meanTimesList) + 2))

ax = figure().gca()

# ax.plot(n, meanTimesList, 'b', label="C++ implementation")
ax.errorbar(n, meanTimesList, yerr=stdDevList, label = "", linestyle='-')
# ax.plot(x2, y2, 'r', label="Algorithm B, Serial C++ implementation")

ax.legend()

ax.set_xlabel('n')
ax.set_ylabel('time (in milliseconds)')
plt.title('Number of input modes v. Time taken \n(no parallelisation) \n g++ compiler')

ax.xaxis.set_major_locator(MaxNLocator(integer=True))
ax.set_yscale('log')

show()
