#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpfr.h>
#include <string>
#include <string.h>
#include <malloc.h>

#define PRECISION 200


using namespace std;
char str[50];
FILE *fp;
FILE *fwp_out_real;


typedef union DoubleUnio {
	double value;
	struct {
		unsigned long int sw;
	} parts;
} dbu;

/*
void mpfr_myw(mpfr_t *data, int prec, FILE *fout){
	char *tmpData, tmpc;
	long expptr = 0, tmpe;
	int  i, j;
	tmpData = mpfr_get_str(NULL, &expptr, 2, 0, *data, MPFR_RNDD);
	if (strcmp(tmpData, "@NaN@") == 0){ fprintf(fout, "%c", 0xB0); return; }
	if (strcmp(tmpData, "@Inf@") == 0){ fprintf(fout, "%c", 0xC0); return; }
	if (strcmp(tmpData, "-@Inf@") == 0){ fprintf(fout, "%c", 0xC1); return; }
	
	if (tmpData[0] == '-'){
		fprintf(fout, "%c", 0xA0);    
		tmpData++;
	}
	else                  fprintf(fout, "%c", 0x90);    
	for (i = 0; i < prec; i += 7){
		tmpc = 0;
		for (j = 0; j < 7; j++)
			if (j + i < prec) tmpc += (tmpData[j + i] - '0') << (6 - j);
		fprintf(fout, "%c", (char)tmpc);
	}
	fprintf(fout, "%c", 0x80);                         
	
	if (expptr < 0)  fprintf(fout, "%c", 0xA0);        
	else            fprintf(fout, "%c", 0x90);         
	expptr = abs(expptr);
	tmpe = 0;
	do{
		tmpe = expptr % 128;  
		expptr = expptr / 128;
		fprintf(fout, "%c", (char)tmpe);
	} while (expptr > 0);
	fprintf(fout, "%c", 0x80);                        
}

void mpfr_myr(mpfr_t *data, int prec, FILE *fin){
	char tmpData[prec + 16];    memset(tmpData, 0, sizeof(tmpData));
	char c, fs;
	long expptr = 0;
	int  i, j = 0;

	fscanf(fin, "%c", &c);
	if (c == (char)0xA0)  tmpData[j++] = '-';
	if (c == (char)0xB0) { mpfr_set_nan(*data);     return; }  
	if (c == (char)0xC0) { mpfr_set_inf(*data, 1); return; }  
	if (c == (char)0xC1) { mpfr_set_inf(*data, -1); return; }  

	tmpData[j++] = '0';
	tmpData[j++] = '.';
	do{
		fscanf(fin, "%c", &c);
		if (c == (char)0x80) break;
		for (i = 6; i >= 0; i--)
			tmpData[j++] = '0' + (c & (1 << i)) / (1 << i);
	} while (true);
	
	tmpData[j] = 'e';
	fscanf(fin, "%c", &fs);
	for (i = 0;; i += 7){
		fscanf(fin, "%c", &c);
		if (c == (char)0x80) break;
		expptr += ((long)c) << i;
	}
	if (fs == (char)0xA0) expptr = -expptr;
	strcat(tmpData, to_string(expptr).c_str());
	mpfr_set_str(*data, tmpData, 2, MPFR_RNDD);
}
*/

void mpfr_myw(mpfr_t *data, int prec, FILE *fout){
	char *tmpData, tmpc;
	long expptr = 0, tmpe;
	int  i, j;
	tmpData = mpfr_get_str(NULL, &expptr, 2, 0, *data, MPFR_RNDD);
	if (strcmp(tmpData, "@NaN@") == 0){ fprintf(fout, "%c", 0xB0); return; }
	if (strcmp(tmpData, "@Inf@") == 0){ fprintf(fout, "%c", 0xC0); return; }
	if (strcmp(tmpData, "-@Inf@") == 0){ fprintf(fout, "%c", 0xC1); return; }
	if (tmpData[0] == '-'){
		fprintf(fout, "%c", 0xA0);
		tmpData++;
	}
	else                  fprintf(fout, "%c", 0x90);
	for (i = 0; i < prec; i += 7){
		tmpc = 0;
		for (j = 0; j < 7; j++)
			if (j + i < prec) tmpc += (tmpData[j + i] - '0') << (6 - j);
		fprintf(fout, "%c", (char)tmpc);
	}
	fprintf(fout, "%c", 0x80); 
	
	if (expptr < 0)  fprintf(fout, "%c", 0xA0);       
	else            fprintf(fout, "%c", 0x90);     
	expptr = abs(expptr);
	tmpe = 0;
	do{
		tmpe = expptr % 128; 
		expptr = expptr / 128;
		fprintf(fout, "%c", (char)tmpe);
	} while (expptr > 0);
	fprintf(fout, "%c", 0x80);                      
}

void mpfr_myr(mpfr_t *data, int prec, FILE *fin){
	char tmpData[prec + 16];    memset(tmpData, 0, sizeof(tmpData));
	char c, fs;
	long expptr = 0;
	int  i, j = 0;

	fscanf(fin, "%c", &c);
	if (c == (char)0xA0)  tmpData[j++] = '-';
	if (c == (char)0xB0) { mpfr_set_nan(*data);     return; } 
	if (c == (char)0xC0) { mpfr_set_inf(*data, 1); return; } 
	if (c == (char)0xC1) { mpfr_set_inf(*data, -1); return; }  

	tmpData[j++] = '0';
	tmpData[j++] = '.';
	do{
		fscanf(fin, "%c", &c);
		if (c == (char)0x80) break;
		for (i = 6; i >= 0; i--)
			tmpData[j++] = '0' + (c & (1 << i)) / (1 << i);
	} while (true);

	tmpData[j] = 'e';
	fscanf(fin, "%c", &fs);
	for (i = 0;; i += 7){
		fscanf(fin, "%c", &c);
		if (c == (char)0x80) break;
		expptr += ((long)c) << i;
	}
	if (fs == (char)0xA0) expptr = -expptr;
	strcat(tmpData, to_string(expptr).c_str());
	mpfr_set_str(*data, tmpData, 2, MPFR_RNDD);
}


char *get_fun_name(int i) {
	switch (i) {
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
void run_fun(int function, mpfr_t &res, mpfr_t arg1, mpfr_t arg2, mpfr_t arg3) {
	long q = 0;
	int temp = 0;
	mpfr_exp_t expt;
	switch (function) {
	case 1:
		mpfr_sin(res, arg1, MPFR_RNDD);
		break;
	case 2:
		mpfr_sinh(res, arg1, MPFR_RNDD);
		break;
	case 3:
		mpfr_asin(res, arg1, MPFR_RNDD);
		break;
	case 4:
		mpfr_asinh(res, arg1, MPFR_RNDD);
		break;
	case 5:
		mpfr_cos(res, arg1, MPFR_RNDD);
		break;
	case 6:
		mpfr_cosh(res, arg1, MPFR_RNDD);
		break;
	case 7:
		mpfr_acos(res, arg1, MPFR_RNDD);
		break;
	case 8:
		mpfr_acosh(res, arg1, MPFR_RNDD);
		break;
	case 9:
		mpfr_tan(res, arg1, MPFR_RNDD);
		break;
	case 10:
		mpfr_tanh(res, arg1, MPFR_RNDD);
		break;
	case 11:
		mpfr_atan(res, arg1, MPFR_RNDD);
		break;
	case 12:
		mpfr_atanh(res, arg1, MPFR_RNDD);
		break;
	case 13:
		mpfr_exp(res, arg1, MPFR_RNDD);
		break;
	case 14:
		mpfr_exp2(res, arg1, MPFR_RNDD);
		break;
	case 15:
		mpfr_exp10(res, arg1, MPFR_RNDD);
		break;
	case 16:
		mpfr_expm1(res, arg1, MPFR_RNDD);
		break;
	case 17:
		mpfr_log(res, arg1, MPFR_RNDD);
		break;
	case 18:
		mpfr_log2(res, arg1, MPFR_RNDD);
		break;
	case 19:
		mpfr_log10(res, arg1, MPFR_RNDD);
		break;
	case 20:
		mpfr_erf(res, arg1, MPFR_RNDD);
		break;
	case 21:
		mpfr_erfc(res, arg1, MPFR_RNDD);
		break;
	case 22:
		mpfr_j0(res, arg1, MPFR_RNDD);
		break;
	case 23:
		mpfr_j1(res, arg1, MPFR_RNDD);
		break;
	case 24:
		mpfr_y0(res, arg1, MPFR_RNDD);
		break;
	case 25:
		mpfr_y1(res, arg1, MPFR_RNDD);
		break;
	case 26:
		mpfr_sqrt(res, arg1, MPFR_RNDD);
		break;
	case 27:
		mpfr_cbrt(res, arg1, MPFR_RNDD);
		break;
	case 28:
		mpfr_gamma(res, arg1, MPFR_RNDD);
		break;
	case 29:
		mpfr_lgamma(res, &temp, arg1, MPFR_RNDD);
		break;
	default:
		printf("sorry! there is no method of mpfr to calculate this function\n");
		break;
	}

}

int main(int argc, char** argv) {
	
//	int num_start=atoi(argv[1]);
//	int num_end=atoi(argv[2]);
	static int size = 1000;
	char *outfilename_real = (char *)malloc(size);
	char *fm = (char *)malloc(size);
	dbu test;double a;
	mpfr_t ma, mc, mb, mpfr_result, experiment_result;
	mpfr_inits2(PRECISION, mc, ma, mb, mpfr_result, experiment_result,
		(mpfr_ptr)0);
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

//printf("%d\n",i);
//	for (int i = num_start; i <= num_end; i++) {
	//	int column_size = 0;
		fm = get_fun_name(i);
		
		outfilename_real = get_file_name("../data/oracle/", argv[1], ".txt");
//printf("%s\n",outfilename_real);		
fwp_out_real = fopen(outfilename_real, "wb+");
		fp = fopen("../data/sampleResult1.txt", "rt");

		while ((!feof(fp))) {
			fscanf(fp, "%16lX", &test.parts.sw);
			if (!feof(fp)) {
				a = test.value;
				mpfr_set_d(ma, a, MPFR_RNDD);
				run_fun(i, mpfr_result, ma, mc, mb);
				mpfr_myw(&mpfr_result, PRECISION, fwp_out_real);
				//fprintf(fwp_out_real,"%s\n","1");
			}
		}
		fclose(fp);
		fclose(fwp_out_real);


//	}
	return 0;
}

