from numpy import *
from matplotlib import *
from pylab import *
import matplotlib.pyplot as plt
matplotlib.rc('xtick', labelsize=20)
matplotlib.rc('ytick', labelsize=20)
matplotlib.rc('font', size='15')
matplotlib.rc('lines', linewidth=4)
matplotlib.rc('legend', fontsize=15)
matplotlib.rc('legend', loc='upper right')
matplotlib.rc('axes', labelsize=15) #      : medium  # fontsize of the x any y labels
matplotlib.rc('axes', grid=True) #      : medium  # fontsize of the x any y labels


GRAPH = "Scale-14 "
TOT_EDG = 2163244/2
N = 16384
K = 16
FILE = 'fw'
X = genfromtxt(FILE, delimiter=',')
width = 0.35
METIS =  12264
ST=18
END=24

fig, ax = plt.subplots()
ax.set_xticklabels(['GL', 'GE', 'CL', 'CE', 'BB', 'SM'])

ax.set_title("Time taken to run Floyd Warshal on distributed " + GRAPH + " partitioned by us")
ax.set_ylabel("Units of time")

ax.set_xticks(arange(1, 7, 1)*2)

ax.bar(arange(1, 7, 1)*2-0.35, X[ST:END, 0], width, color='m', label="BFS ordering")

width = 0.35
ax.bar(arange(1, 7, 1)*2, X[ST:END, 1], width, color='b', label="DFS ordering")

axhline(y=METIS,  label='Metis', color='g')

legend()
show()
