#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <string.h>
#include <math.h>
#include <malloc.h>
#include<gsl/gsl_math.h>
#include<gsl/gsl_sf.h>
#include<gsl/gsl_sf_gamma.h>
#include<gsl/gsl_sf_bessel.h>
#include<gsl/gsl_sf_erf.h>
#include<gsl/gsl_sf_trig.h>
#include<gsl/gsl_sf_log.h>
#include<gsl/gsl_sf_exp.h>
#define PRECISION 200


using namespace std;
char str[50];
FILE *fp;
FILE *fwp_out;


typedef union DoubleUnio {
double value;
struct {
unsigned long int sw;
} parts;
} dbu;


char *get_fun_name(int i) {
	switch (i) {
	case 0:
        return "0";
		break;
    case 1:
		return "1";
		break;
	case 2:
		return "2";
		break;
	case 3:
		return "3";
		break;
	case 4:
		return "4";
		break;
	case 5:
		return "5";
		break;
	case 6:
		return "6";
		break;
	case 7:
		return "7";
		break;
	case 8:
		return "8";
		break;
	case 9:
		return "9";
		break;
	case 10:
		return "10";
		break;
	case 11:
		return "11";
		break;
	case 12:
		return "12";
		break;
	case 13:
		return "13";
		break;
	case 14:
		return "14";
		break;
	case 15:
		return "15";
		break;
	case 16:
		return "16";
		break;
	case 17:
		return "17";
		break;
	case 18:
		return "18";
		break;
	case 19:
		return "19";
		break;
	case 20:
		return "20";
		break;
	case 21:
		return "21";
		break;
	case 22:
		return "22";
		break;
	case 23:
		return "23";
		break;
	case 24:
		return "24";
		break;
	case 25:
		return "25";
		break;
	case 26:
		return "26";
		break;
	case 27:
		return "27";
		break;
	case 28:
		return "28";
		break;
	case 29:
		return "29";
		break;
	case 30:
		return "30";
		break;
	case 31:
		return "31";
		break;
	case 32:
		return "32";
		break;
	case 33:
		return "33";
		break;
	case 34:
		return "34";
		break;
	case 35:
		return "35";
		break;
	case 36:
		return "36";
		break;
	case 37:
		return "37";
		break;
	case 38:
		return "38";
		break;
	case 39:
		return "39";
		break;
	}
}
char *get_file_name(const char *str1, const char *str2, const char *str3) {

	int size = 100;
	char *buffer = (char *)malloc(size);
	while (1) {
		int nchars = snprintf(buffer, size, "%s%s%s", str1, str2, str3);
		if (nchars < size)
			return buffer;
		size *= 2;
		free(buffer);
		buffer = (char *)malloc(size);
	}
}
/*
void run_fun(int function, double &res, double  arg1, double arg2, double arg3) {
	long q = 0;
	int temp = 0;
	switch (function) {
	case 1:
		res=sin(arg1);
		break;
	case 2:
		res=sinh(arg1);
		break;
	case 3:
		res=asin(arg1);
		break;
	case 4:
		res=asinh(arg1);
		break;
	case 5:
		res=cos(arg1);
		break;
	case 6:
		res=cosh(arg1);
		break;
	case 7:
		res=acos(arg1);
		break;
	case 8:
		res=acosh(arg1);
		break;
	case 9:
		res=tan(arg1);
		break;
	case 10:
		res=tanh(arg1);
		break;
	case 11:
		res=atan(arg1);
		break;
	case 12:
		res=atanh(arg1);
		break;
	case 13:
		res=exp(arg1);
		break;
	case 14:
		res=exp2(arg1);
		break;
	case 15:
		res=exp10(arg1);
		break;
	case 16:
		res=expm1(arg1);
		break;
	case 17:
		res=log(arg1);
		break;
	case 18:
		res=log2(arg1);
		break;
	case 19:
		res=log10(arg1);
		break;
	case 20:
		res=erf(arg1);
		break;
	case 21:
		res=erfc(arg1);
		break;
	case 22:
		res=j0(arg1);
		break;
	case 23:
		res=j1(arg1);
		break;
	case 24:
		res=y0(arg1);
		break;
	case 25:
		res=y1(arg1);
		break;
	case 26:
		res=sqrt(arg1);
		break;
	case 27:
		res=cbrt(arg1);
		break;
	case 28:
		res=tgamma(arg1);
		break;
	case 29:
		res=lgamma(arg1);
		break;
	default:
		printf("sorry! there is no method of mpfr to calculate this function\n");
		break;
	}

}
*/

void run_fun(int function, double &res, double  arg1, double arg2, double arg3) {
	long q = 0;
	int temp = 0;
	switch (function) {
	case 1:
		res = gsl_sf_sin(arg1);
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		res = gsl_asinh(arg1);
		break;
	case 5:
		res = gsl_sf_cos(arg1);
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		res = gsl_acosh(arg1);
		break;
	case 9:
		break;
	case 10:
		break;
	case 11:
		break;
	case 12:
		res = gsl_atanh(arg1);
		break;
	case 13:
		res = gsl_sf_exp(arg1);
		break;
	case 14:
		break;
	case 15:
		break;
	case 16:
		res = gsl_expm1(arg1);
		break;
	case 17:
		res = gsl_sf_log(arg1);
		break;
	case 18:
		break;
	case 19:
		break;
	case 20:
		res = gsl_sf_erf(arg1);
		break;
	case 21:
		res = gsl_sf_erfc(arg1);
		break;
	case 22:
		res = gsl_sf_bessel_J0(arg1);
		break;
	case 23:
		res = gsl_sf_bessel_J1(arg1);
		break;
	case 24:
		res = gsl_sf_bessel_Y0(arg1);
		break;
	case 25:
		res = gsl_sf_bessel_Y1(arg1);
		break;
	case 26:
		break;
	case 27:
		break;
	case 28:
		res = gsl_sf_gamma(arg1);
		break;
	case 29:
		res = gsl_sf_lngamma(arg1);
		break;
	default:
		printf("sorry! there is no method of mpfr to calculate this function\n");
		break;
	}

}

int main(int argc, char** argv) {
	static int size = 1000;

	char *outfilename= (char *)malloc(size);
	char *fm = (char *)malloc(size);
	
	dbu test, test1,tes;
	double a,b,c;
	int sum1 = 0;
int i;
if(strcmp(argv[1],"sin")==0) i=1;
else if (strcmp(argv[1],"sinh")==0) i=2;
else if (strcmp(argv[1],"asin")==0) i=3;
else if (strcmp(argv[1],"asinh")==0) i=4;
else if (strcmp(argv[1],"cos")==0) i=5;
else if (strcmp(argv[1],"cosh")==0) i=6;
else if (strcmp(argv[1],"acos")==0) i=7;
else if (strcmp(argv[1],"acosh")==0) i=8;
else if (strcmp(argv[1],"tan")==0) i=9;
else if (strcmp(argv[1],"tanh")==0) i=10;
else if (strcmp(argv[1],"atan")==0) i=11;
else if (strcmp(argv[1],"atanh")==0) i=12;
else if (strcmp(argv[1],"exp")==0) i=13;
else if (strcmp(argv[1],"exp2")==0) i=14;
else if (strcmp(argv[1],"exp10")==0) i=15;
else if (strcmp(argv[1],"expm1")==0) i=16;
else if (strcmp(argv[1],"log")==0) i=17;
else if (strcmp(argv[1],"log2")==0) i=18;
else if (strcmp(argv[1],"log10")==0) i=19;
else if (strcmp(argv[1],"erf")==0) i=20;
else if (strcmp(argv[1],"erfc")==0) i=21;
else if (strcmp(argv[1],"j0")==0) i=22;
else if (strcmp(argv[1],"j1")==0) i=23;
else if (strcmp(argv[1],"y0")==0) i=24;
else if (strcmp(argv[1],"y1")==0) i=25;
else if (strcmp(argv[1],"sqrt")==0) i=26;
else if (strcmp(argv[1],"cbrt")==0) i=27;
else if (strcmp(argv[1],"gamma")==0) i=28;
else if (strcmp(argv[1],"lgamma")==0) i=29;
else i=0;
		int column_size = 0;
		fm = get_fun_name(i);
        fm=get_file_name("../data/glibc", argv[2], "/");
		outfilename=get_file_name(fm, argv[1], ".txt");
		fp = fopen("../data/sampleResult1.txt", "rt");
		fwp_out = fopen(outfilename, "wb+");
	
		double result;
		while ((!feof(fp))) {
			fscanf(fp, "%16lX", &test.parts.sw);
			if (!feof(fp)) {
				a = test.value;	
				run_fun(i, result, a, c, b);
				tes.value = result;
				fprintf(fwp_out, "%16lX\n", tes.parts.sw);
			}
		}
		fclose(fp);
		fclose(fwp_out);
	return 0;
}

