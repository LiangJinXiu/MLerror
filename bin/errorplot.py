import matplotlib.pyplot as plt
import numpy as np
import fileinput
import os
import struct
from sys import argv
from pylab import *  #支持中文
plt.rcParams['font.sans-serif']=['SimHei']
plt.rcParams['axes.unicode_minus'] = False

def del_0x(h2):
    return h2[2:]#去掉0x
def hex_to_float(h):
    tuple1=struct.unpack('>d', bytes().fromhex(h.strip().zfill(16)))
    list1 = list(tuple1)
    return float(list1[0])
if __name__ == '__main__':
    #使用numpy数组，比列表更加快速
    lines=int(argv[1])*4096
    num=0
    list_x=[]
    list_y=[]

    f = open('../data/samplelong1.txt', 'r')  # 'test1.txt'a
    f1 = open('../data/error/'+argv[2]+argv[3]+'.txt', 'r')  # 'test1.txt'
    for j in range(0,lines):
        data=f.readline()
        data1=f1.readline()
        a = float(data)
        b = hex_to_float(data1)
        if math.isnan(b) == True or math.isinf(b) == True or b==1.0 or b==-1.0:
            continue
        else:
            list_x.append(a)
            list_y.append(b)
    f.close()
    f1.close()
    #print(argv[1])
    #print(str(min(list_y)))
    #print(str(max(list_y)))    
    
#print(list_x)
    plt.figure(figsize=(10, 6))
    plt.xlim(0,1.85e+19)    
#plt.scatter(list_x, list_y, color='k', s=16, marker='o')  # 散点图
    plt.plot(list_x,list_y,marker='o',markersize=2,ls='')
    plt.axhline(y=0, color='k',lw='1')
    plt.xlabel(u'输入浮点数(无符号整数)', fontsize=12)
    plt.ylabel(u'相对误差', fontsize=12)
    plt.title(u'相对误差总体分布图' + argv[4]+argv[3]+argv[2], fontsize=12)  # +argv[3]
    plt.savefig("../data/analysis/errorplot/"+argv[2]+argv[4]+argv[3]+".png", bbox_inches='tight')  # './3.png'
    #print(list_x.shape())
   # print(list_y.shape())    
#plt.show()
