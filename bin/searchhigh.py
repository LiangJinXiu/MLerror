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
    f = open("../data/sampleResult1.txt",'r')#argv[1] input1
    f1 = open("../data/error/"+argv[3]+argv[4]+".txt", 'r')  # argv[2] input2
    lines1 =int(argv[1])*4096 #51200000


    f2=open("../data/analysis/higherror/"+argv[3]+argv[4]+"_"+argv[2]+".txt",'a+')

    for i in range(1, lines1 + 1):
        data1 = f.readline()
        data2 = f1.readline()
        flag=float(argv[2])#1.0e-15
        if math.isinf(hex_to_float(data2))==True:
            continue
        elif hex_to_float(data2)==1.0 or hex_to_float(data2)==-1.0:
            continue
        elif math.fabs(hex_to_float(data2)) >= flag:
            f2.write(data1.strip())
            f2.write(',')
            f2.write(data2.strip())
            f2.write(',')
            f2.write(str(hex_to_float(data2)))
            f2.write('\n')
        else:
            continue
    #print("111")
    f.close()
    f1.close()
    f2.close()
if __name__ == '__main__':
    distribution()
