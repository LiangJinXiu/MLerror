import matplotlib.pyplot as plt
import numpy as np
import os
import math
from sys import argv
from pylab import *  #支持中文
plt.rcParams['font.sans-serif']=['SimHei']
plt.rcParams['axes.unicode_minus'] = False
f = open("../data/analysis/Emaxmin/"+argv[1]+argv[2]+".txt",'r')#'test1.txt'
list_max1=[]
list_max2=[]
list_min1=[]
list_min2=[]
list_mean1=[]
list_mean2=[]
list_median1=[]
list_median2=[]
lines=4096
x1=list(range(0,2048))
x2=list(range(0,2048))
#print(x1)
plt.figure(figsize=(15, 10))
for i in range(1,lines+1):
    if i<=2048:
        data=f.readline()
        list = data.strip().split(',')
        if math.isnan(float(list[0].strip('\n').strip('@')))==True or math.isinf(float(list[0].strip('\n').strip('@')))==True:
            x1[i-1]=-1
        else:
            list_max1.append(float(list[0]))
            list_min1.append(float(list[1]))
            list_mean1.append(float(list[2]))
            list_median1.append(float(list[3]))
    else:
        data = f.readline()
        #print(data)
        list = data.strip().split(',')
        if math.isnan(float(list[0].strip('\n').strip('@'))) == True or math.isinf(float(list[0].strip('\n').strip('@'))) == True:
            x2[i - 2049]=-1
        else:
            list_max2.append(float(list[0]))
            list_min2.append(float(list[1]))
            list_mean2.append(float(list[2]))
            list_median2.append(float(list[3]))
j=0
for i in range(0,2048):
    if x1[j]==-1:
        x1.pop(j)
    else:
        j+=1
j=0
for i in range(0,2048):
    if x2[j]==-1:
        x2.pop(j)
    else:
        j+=1
x1[:]=[x -1023 for x in x1]
x2[:]=[x -1023 for x in x2]
plt.subplot(211)
plt.plot(x1,list_max1,color='#FF0000',label='最大值',linewidth=1.0)
plt.plot(x1,list_min1,color='#00FF00',label='最小值',linewidth=1.0)
plt.plot(x1,list_mean1,color='#0000FF',label='平均值',linewidth=1.0)
plt.plot(x1,list_median1,color='#000F0F',label='中位数',linewidth=1.0)
plt.xlabel(u'指数', fontsize=12)
plt.ylabel(u'相对误差', fontsize=12)
plt.title(u'正数-相对误差与指数的关系'+argv[3]+argv[2]+argv[1], fontsize=12)#+argv[3]
plt.legend(fontsize=12)
plt.xlim(-1023,1024)
x_major_locator=MultipleLocator(250)
ax=plt.gca()
ax.xaxis.set_major_locator(x_major_locator)

plt.subplot(212)
plt.plot(x2,list_max2,color='#FF0000',label='最大值',linewidth=1.0)
plt.plot(x2,list_min2,color='#00FF00',label='最小值',linewidth=1.0)
plt.plot(x2,list_mean2,color='#0000FF',label='平均值',linewidth=1.0)
plt.plot(x2,list_median2,color='#000F0F',label='中位数',linewidth=1.0)
plt.xlabel(u'指数', fontsize=12)
plt.ylabel(u'相对误差', fontsize=12)
plt.title(u'负数-相对误差与指数的关系'+argv[3]+argv[2]+argv[1], fontsize=12)#+argv[3]
plt.legend(fontsize=12)
#my_x_ticks=np.arange(-1023,1025,256)
#plt.xticks(my_x_ticks)
plt.xlim(-1023,1024)
x_major_locator=MultipleLocator(250)
ax=plt.gca()
ax.xaxis.set_major_locator(x_major_locator)

plt.savefig("../data/analysis/Emaxmin/"+argv[1]+argv[3]+argv[2]+".png", bbox_inches='tight')#'./3.png'
#plt.show()
