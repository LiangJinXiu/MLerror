#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <string.h>
#include <malloc.h>
#include <cmath>



using namespace std;
char str[50];
FILE *fp=fopen("../data/sampleResult1.txt","r");

FILE *fp_out=fopen("../data/samplelong1.txt","w+");//



typedef union DoubleUnio {
double value;
struct {
unsigned long int sw;
} parts;
} dbu;
int main(){
    dbu test, test1;
    while (!feof(fp)) {
        fscanf(fp, "%16lX", &test.parts.sw);
        fprintf(fp_out, "%lu\n", test.parts.sw);
    }
    return 0;
}

