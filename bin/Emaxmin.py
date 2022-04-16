
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
    num=int(argv[1])
    f = open("../data/error/"+argv[2]+argv[3]+".txt",'r')#argv[1]
    lines =4096*num #51200000
    f2=open("../data/analysis/Emaxmin/"+argv[2]+argv[3]+".txt",'a+')#argv[2]
    content=[]
    for i in range(1,lines+1):
        data=f.readline()
        #print(data)
        if i%num!=0 :#100000
            if math.isnan(hex_to_float(data))==True or math.isinf(hex_to_float(data))==True or hex_to_float(data)==1.0 or hex_to_float(data)==-1.0:
                continue
            else:
                content.append(math.fabs(hex_to_float(data)))#
        else:
            if math.isnan(hex_to_float(data))==False and math.isinf(hex_to_float(data))==False and hex_to_float(data)!=1.0 and hex_to_float(data)!=-1.0:
                content.append(math.fabs(hex_to_float(data)))
            #print(content)
            #print(len(content))
            if len(content)==0:
                f2.write('@NaN@,@NaN@,@NaN@,@NaN@,@NaN@\n')
            else:
                f2.write(str(max(content)))
                f2.write(',')
                f2.write(str(min(content)))
                f2.write(',')
                f2.write(str(np.mean(content)))
                f2.write(',')
                f2.write(str(np.median(content)))
                f2.write(',')
                f2.write(str(len(content)))
                f2.write('\n')
            content=[]
    #
    f2.close()
    f.close()
if __name__ == '__main__':
    distribution()
