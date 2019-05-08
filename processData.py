import matplotlib.pyplot as plt
import numpy as np

from matplotlib.pyplot import figure, show
from matplotlib.ticker import MaxNLocator

n1, times1, perms1 = np.loadtxt('timings/org/gcc_noflags_serial.csv', delimiter=',', unpack=True)
n2, times2, perms2 = np.loadtxt('timings/org/intel_noflags_2_serial.csv', delimiter=',', unpack=True)
# n2, times3, perms1 = np.loadtxt('timings/threads/intel/intel_4thread_parallel.csv', delimiter=',', unpack=True)
# n2, times4, perms1 = np.loadtxt('timings/threads/intel/intel_8thread_parallel.csv', delimiter=',', unpack=True)
# n2, times5, perms1 = np.loadtxt('timings/threads/intel/intel_16thread_parallel.csv', delimiter=',', unpack=True)
# n2, times6, perms1 = np.loadtxt('timings/threads/intel/intel_28thread_parallel.csv', delimiter=',', unpack=True)

# # ########################################
# l1 = times1
# timesList1 = []
# temp = []
# len = 27
# for i in range(len):
#     for j in range(5):
#         temp.append(l1[i])
#     timesList1.append(temp)
#     temp = []
#
# meanTimesList1 = []
# stdDevList1 = []
# for ele in timesList1:
#     meanTimesList1.append(np.mean(ele))
#     stdDevList1.append(np.std(ele))
#
# # ########################################
# l2 = times2
# timesList2 = []
# temp = []
# len = 27
# for i in range(len):
#     for j in range(5):
#         temp.append(l2[i])
#     timesList2.append(temp)
#     temp = []
#
# meanTimesList2 = []
# stdDevList2 = []
# for ele in timesList2:
#     meanTimesList2.append(np.mean(ele))
#     stdDevList2.append(np.std(ele))

# ########################################
l1 = times1
timesList1 = []
temp = []
for i in range(n1.size):
    temp.append(l1[i])
    if i ==(n1.size-1) or n1[i]!=n1[i+1]:
        timesList1.append(temp)
        temp = []

meanTimesList1 = []
stdDevList1 = []
for ele in timesList1:
    meanTimesList1.append(np.mean(ele))
    stdDevList1.append(np.std(ele))

#########################################
l2 = perms1
timesList2 = []
temp = []
for i in range(n1.size):
    temp.append(l2[i])
    if i ==(n1.size-1) or n1[i]!=n1[i+1]:
        timesList2.append(temp)
        temp = []

meanTimesList2 = []
stdDevList2 = []
for ele in timesList2:
    meanTimesList2.append(np.mean(ele))
    stdDevList2.append(np.std(ele))
#
# ########################################
l3 = times2
timesList3 = []
temp = []
for i in range(n1.size):
    temp.append(l3[i])
    if i ==(n1.size-1) or n1[i]!=n1[i+1]:
        timesList3.append(temp)
        temp = []

meanTimesList3 = []
stdDevList3 = []
for ele in timesList3:
    meanTimesList3.append(np.mean(ele))
    stdDevList3.append(np.std(ele))

########################################
l4 = perms2
timesList4 = []
temp = []
for i in range(n1.size):
    temp.append(l4[i])
    if i ==(n1.size-1) or n1[i]!=n1[i+1]:
        timesList4.append(temp)
        temp = []

meanTimesList4 = []
stdDevList4 = []
for ele in timesList4:
    meanTimesList4.append(np.mean(ele))
    stdDevList4.append(np.std(ele))

# ########################################
# l5 = times5
# timesList5 = []
# temp = []
# for i in range(n1.size):
#     temp.append(l5[i])
#     if i ==(n1.size-1) or n1[i]!=n1[i+1]:
#         timesList5.append(temp)
#         temp = []
#
# meanTimesList5 = []
# stdDevList5 = []
# for ele in timesList5:
#     meanTimesList5.append(np.mean(ele))
#     stdDevList5.append(np.std(ele))
#
# #########################################
# l6 = times6
# timesList6 = []
# temp = []
# for i in range(n1.size):
#     temp.append(l6[i])
#     if i ==(n1.size-1) or n1[i]!=n1[i+1]:
#         timesList6.append(temp)
#         temp = []
#
# meanTimesList6 = []
# stdDevList6 = []
# for ele in timesList6:
#     meanTimesList6.append(np.mean(ele))
#     stdDevList6.append(np.std(ele))
#
# #########################################


n = list(range (2, len(meanTimesList1) + 2))
#n = list(range (2, 29))

print (stdDevList1)
print (stdDevList3)

ax = figure().gca()

# ax.plot(n, meanTimesList, 'b', label="C++ implementation")
ax.errorbar(n, meanTimesList1, yerr=stdDevList1, label = "gcc: total time taken", linestyle='-')
ax.errorbar(n, meanTimesList2, yerr=stdDevList2, label = "gcc: time spent in computing permanents", linestyle='-')
ax.errorbar(n, meanTimesList3, yerr=stdDevList3, label = "intel: total time taken", linestyle='-')
ax.errorbar(n, meanTimesList4, yerr=stdDevList4, label = "intel: time spent in computing permanents", linestyle='-')
# ax.plot(n, meanTimesList1, label="gcc compiler")
# ax.plot(n, meanTimesList2, label="intel compiler")
# ax.plot(n, meanTimesList2, label="2 threads")
# ax.plot(n, meanTimesList3, label="4 threads")
# ax.plot(n, meanTimesList4, label="8 threads")
# ax.plot(n, meanTimesList5, label="16 threads")
# ax.plot(n, meanTimesList6, label="28 threads")


ax.legend()

ax.set_xlabel('n')
ax.set_ylabel('time (in milliseconds)')
plt.title('Input size n v. Time taken \n Parallel implementation, 28 threads, all flags enabled')

ax.xaxis.set_major_locator(MaxNLocator(integer=True))
ax.set_yscale('log')

show()
