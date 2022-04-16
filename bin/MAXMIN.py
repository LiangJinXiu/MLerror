from sys import argv
import numpy as np
import os
import math
import struct

def del_0x(h2):
    return h2[2:]#去掉0x
def hex_to_float(h):
    tuple1=struct.unpack('>d', bytes().fromhex(h.strip().zfill(16)))
    list1 = list(tuple1)
    return float(list1[0])
def float_to_hex(h1):
    return hex(struct.unpack('>Q', struct.pack('>d', h1))[0])

def distribution( ):
    f = open("../data/analysis/Emaxmin/"+argv[1]+argv[2]+".txt",'r')#argv[1]
    lines =4096 #51200000
    f2=open("../data/analysis/MAXMIN/"+argv[1]+argv[2]+"MAXMIN.txt",'a+')#argv[2]
    content=[]
    sum=0.0
    num=0.0
    MAX=[]
    MIN=[]
    for i in range(1,lines+1):
        data=f.readline()
        list = data.strip().split(',')
        #print(data)
        if math.isnan(float(list[0].strip('\n').strip('@')))==True or math.isinf(float(list[0].strip('\n').strip('@')))==True:
            continue
        else:
            sum=sum+float(list[2].strip('\n').strip('@')) * float(list[4].strip('\n').strip('@'))
            num=num+float(list[4].strip('\n').strip('@'))
            MAX.append(float(list[0]))
            MIN.append(float(list[1]))


    
           

    f2.write(argv[1])
    f2.write(",")
    f2.write(str(max(MAX)))
    f2.write(",")
    f2.write(str(min(MIN)))
    f2.write(',')
    f2.write(str(sum/num))    
    f2.write('\n')
    f2.close()
    f.close()
if __name__ == '__main__':
    distribution()
