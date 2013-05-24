from pylab import *
from matplotlib import *
from matplotlib.pyplot import *
from numpy import *

def draw(Xrel1, Met, index, graphname , k=10):
    fig = figure()
    
    ax = fig.add_subplot(111)
    ax.set_title("Fraction of edges cut for " + graphname)
    ax.set_ylabel("Fraction of edges cut")

    width = 0.2
    ind = arange(6)
    ylim([0, 1.3])
    ax.set_xticks(ind + width)
    ax.set_xticklabels(('GL', 'GE', 'CL', 'CE', 'BB', 'SM'))

    br = bar(arange(6), array(Xrel1[index])[0], width=0.2)
    metline, = plot(arange(6), tile(Met[index], 6), color="r", linewidth=5)
    randline, = plot(arange(6), tile([(k-1)/float(k)], 6), color="g", linewidth=5)

    ax.legend((metline, br, randline), ('Metis', 'Stream', 'Random'))
