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
    f = open("../data/analysis/pointcompare/"+argv[2]+argv[3]+"_"+argv[4]+".txt",'r')#argv[1]
    lines =int(argv[1])*4096 #51200000
    f2=open("../data/analysis/goodbad/"+argv[2]+argv[3]+"_"+argv[4]+".txt",'w+')#argv[2]
    content=[]
    num= np.zeros(4)
    for i in range(1,lines+1):
        data=f.readline()
        #print(data)
        if i%int(argv[1])!=0 :#100000
            if math.isnan(hex_to_float(data))==True or math.isinf(hex_to_float(data))==True:
                num[3]=num[3]+1
                continue
            else:
                if hex_to_float(data)>0:
                    num[0] = num[0] + 1
                if hex_to_float(data)<0:
                    num[1] = num[1] + 1
                if hex_to_float(data)==0:
                    num[2] = num[2] + 1
        else:
            if math.isnan(hex_to_float(data)) == False and math.isinf(hex_to_float(data)) == False:
                if hex_to_float(data)>0:
                    num[0] = num[0] + 1
                if hex_to_float(data)<0:
                    num[1] = num[1] + 1
                else:
                    num[2] = num[2] + 1
            else:
                num[3] = num[3] + 1
            f2.write(str(num[0]))#正
            f2.write(',')
            f2.write(str(num[1]))#负
            f2.write(',')
            f2.write(str(num[2]))#0
            f2.write(',')
            f2.write(str(num[3]))#异常值100000-num[0]-num[1]-num[2]
            f2.write(',')
            f2.write(str(num[0]/ int(argv[1])))
            f2.write(',')
            f2.write(str(num[1] / int(argv[1])))
            f2.write(',')
            f2.write(str(num[2] / int(argv[1])))
            f2.write(',')
            f2.write(str(num[3]/int(argv[1])))#(100000 - num[0] - num[1] - num[2])
            f2.write('\n')
            num = np.zeros(4)
    #
    f2.close()
    f.close()
if __name__ == '__main__':
    distribution()
