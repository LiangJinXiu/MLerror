import matplotlib.pyplot as plt
import numpy as np
import os
import math
from sys import argv
import math
import struct
from pylab import *  #支持中文
plt.rcParams['font.sans-serif']=['SimHei']
plt.rcParams['axes.unicode_minus'] = False

def num_to_string(num):
    numbers = {
        0 : "",
        1 : "sin",
        2 : "sinh",
        3 : "asin",
        4 : "asinh",
        5 : "cos",
        6 : "cosh",
        7 : "acos",
        8 : "acosh",
        9 : "tan",
        10 : "tanh",
        11: "atan",
        12: "atanh",
        13: "exp",
        14: "exp2",
        15: "exp10",
        16: "expm1",
        17: "log",
        18: "log2",
        19: "log10",
        20: "erf",
        21: "erfc",
        22: "j0",
        23: "j1",
        24: "y0",
        25: "y1",
        26: "sqrt",
        27: "cbrt",
        28: "gamma",
        29: "lgamma",

    }
    return numbers.get(num, None)


if __name__ == "__main__":

    f = open('../data/analysis/goodbad/'+argv[1]+argv[2]+'_'+argv[3]+'.txt','r')#'test1.txt'argv[1]

    #1+;2-;3-0;4异常  比例
    list_11_1=[]
    list_12_1=[]
    list_21_1=[]
    list_22_1=[]
    list_31_1=[]
    list_32_1=[]
    list_41_1=[]
    list_42_1=[]
    list_11_2=[]
    list_12_2=[]
    list_21_2=[]
    list_22_2=[]
    list_31_2=[]
    list_32_2=[]
    list_41_2=[]
    list_42_2=[]

    lines=4096
    x1=list(range(0,2048))
    x2=list(range(0,2048))
    #print(x1)
    plt.figure(figsize=(15, 10))
    for i in range(1,lines+1):
        if i <= 2048:
            data = f.readline()
            list = data.strip().split(',')
            if float(list[0])>0 or float(list[1])>0 or float(list[3])>0:
                list_11_1.append(float(list[0]))
                list_21_1.append(float(list[1]))
                list_31_1.append(float(list[2]))
                list_41_1.append(float(list[3]))
                list_12_1.append(float(list[4])*100)
                list_22_1.append(float(list[5])*100)
                list_32_1.append(float(list[6])*100)
                list_42_1.append(float(list[7])*100)
            else:
                x1[i - 1] = -1
        else:
            data = f.readline()
            list = data.strip().split(',')
            if float(list[0]) > 0 or float(list[1]) > 0 or float(list[3]) > 0:
                list_11_2.append(float(list[0]))
                list_21_2.append(float(list[1]))
                list_31_2.append(float(list[2]))
                list_41_2.append(float(list[3]))
                list_12_2.append(float(list[4]))
                list_22_2.append(float(list[5])*100)
                list_32_2.append(float(list[6])*100)
                list_42_2.append(float(list[7])*100)
            else:
                x2[i - 2049] = -1
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
    plt.scatter(x1,list_12_1, color='#FF0000', label='正',s=1, marker='o')
    plt.scatter(x1,list_22_1, color='#00FF00',label='负', s=1, marker='o')
    #plt.plot(x1,list_12_1,color='#FF0000',label='正',linewidth=1.0)
    #plt.plot(x1,list_22_1,color='#00FF00',label='负',linewidth=1.0)
    #plt.plot(x1,list_42_1,color='#0000FF',label='异常',linewidth=1.0)
    plt.xlabel(u'指数', fontsize=12)
    plt.ylabel(u'点对点做差比例', fontsize=12)
    plt.title(u'正数-点对点做差比例与指数的关系（%）'+argv[1]+' '+argv[2]+'-'+argv[3], fontsize=12)#+argv[3]
    plt.legend(fontsize=12)

    plt.subplot(212)
    plt.scatter(x2,list_12_2, color='#FF0000', label='正',s=1, marker='o')
    plt.scatter(x2,list_22_2, color='#00FF00', label='负',s=1, marker='o')
    #plt.plot(x1,list_12_2,color='#FF0000',label='正',linewidth=1.0)
    #plt.plot(x1,list_22_2,color='#00FF00',label='负',linewidth=1.0)
    #plt.plot(x1,list_42_2,color='#0000FF',label='异常',linewidth=1.0)
    plt.xlabel(u'指数', fontsize=12)
    plt.ylabel(u'点对点做差比例', fontsize=12)
    plt.title(u'负数-点对点做差比例与指数的关系（%）'+argv[1]+' '+argv[2]+'-'+argv[3], fontsize=12)#+argv[3]
    plt.legend(fontsize=12)

   # print(argv[1]+' '+argv[2]+'-'+argv[3],"正",sum(list_11_1),(sum(list_11_1)/(51200000*8))*100,"%")     #+argv[3]
    #print(argv[1]+' '+argv[2]+'-'+argv[3],"负",sum(list_21_1),(sum(list_21_1)/(51200000*8))*100,"%")
    #print(argv[1]+' '+argv[2]+'-'+argv[3],"异常",sum(list_41_1),(sum(list_41_1)/(51200000*8))*100,"%" )
    plt.savefig('../data/analysis/goodbad/'+argv[1]+argv[2]+'_'+argv[3]+'.png', bbox_inches='tight')#'./3.png'
    #plt.show()
