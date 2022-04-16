#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <string.h>
#include<mpfr.h>
#include <malloc.h>
#include <cmath>

#define PRECISION 200


using namespace std;
char str[50];
FILE *fp;
FILE *fp1;
FILE *fwp_out;


typedef union DoubleUnio {
double value;
struct {
unsigned long int sw;
} parts;
} dbu;


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
/*
void Rerror(double double_experiment_result, mpfr_t mpfr_result, mpfr_t &result)
{
	mpfr_t sub_result, abs_result,a,aaa, bb,experiment_result;
    mpfr_inits2(PRECISION, sub_result, abs_result, a,aaa, bb,experiment_result, (mpfr_ptr)0);
    double b = 3.1e-61;
    dbu search0;
	search0.parts.sw=0x0;
	mpfr_set_zero(aaa,1);
    mpfr_set_zero(a,-1);
	mpfr_set_d(bb, b, MPFR_RNDD);
    if (mpfr_cmp(mpfr_result,aaa)==0||mpfr_cmp(mpfr_result,a)==0)
    {
		if(double_experiment_result==search0.value)
			mpfr_set_zero(result,1);
		else
		{
			mpfr_set(mpfr_result, bb, MPFR_RNDD);
			mpfr_set_d(experiment_result, double_experiment_result, MPFR_RNDD);
			mpfr_sub(sub_result, experiment_result, mpfr_result, MPFR_RNDD);
    		mpfr_abs(abs_result, mpfr_result, MPFR_RNDD);
    		mpfr_div(result, sub_result, abs_result, MPFR_RNDD);
		}
        
    }   
	else
	{
		mpfr_set_d(experiment_result, double_experiment_result, MPFR_RNDD);
		mpfr_sub(sub_result, experiment_result, mpfr_result, MPFR_RNDD);
    	mpfr_abs(abs_result, mpfr_result, MPFR_RNDD);
   		mpfr_div(result, sub_result, abs_result, MPFR_RNDD);
	}    
}
*/
int main(int argc, char** argv) {
//	mpfr_t ma, mc, mb, mpfr_result, experiment_result,result;
//	mpfr_inits2(PRECISION, mc, ma, mb, mpfr_result, experiment_result,result,
//		(mpfr_ptr)0);
mpfr_t ma, mc, mb, mpfr_result1, mpfr_result, experiment_result,result,abs_result,abs_result1,sub_result;
        mpfr_inits2(PRECISION, mc, ma, mb, mpfr_result1, mpfr_result, experiment_result,result,abs_result,abs_result1,sub_result,
                (mpfr_ptr)0);
	dbu test, test1;
	double a,aa;
	static int size = 1000;
	char *outfilename= (char *)malloc(size);
	char *outfilename1= (char *)malloc(size);
	char *outfilename2= (char *)malloc(size);
	char *fm1 = (char *)malloc(size);
	char *fm = (char *)malloc(size);
	
	fm1 = get_file_name("../data/analysis/pointcompare/",argv[2] , argv[3]);
	outfilename = get_file_name(fm1, "_", argv[4]);
outfilename=get_file_name(outfilename,".","txt");
	fwp_out = fopen(outfilename, "wb+");

	
	fm= get_file_name("../data/error/",argv[2] , argv[3]);
	outfilename2= get_file_name(fm, "_mpfr", ".txt");
	outfilename1 = get_file_name("../data/error/", argv[2], argv[4]);
outfilename1=get_file_name(outfilename1,"_mpfr",".txt");
	fp = fopen(outfilename2, "rb");
//fp=fopen("../data/glibc2.14/sin.txt","rt");
	fp1 = fopen(outfilename1, "rb");
//fp1=fopen("../data/oracle/sin.txt","rb");
printf("%s %s %s\n",outfilename2,outfilename1,outfilename);
	int flag;dbu double_error;
//fscanf(fp, "%16lX", &test.parts.sw);
//printf("%16lX",test.parts.sw);
int num;
num=4096*atoi(argv[1]);	
//printf("%d\n",num);
//while ((!feof(fp))) {
for(int i=0;i<num;i++){
//printf("1");
mpfr_myr(&mpfr_result, PRECISION, fp);
                        mpfr_myr(&mpfr_result1, PRECISION, fp1);
    
                    if (!feof(fp)) {
                mpfr_abs(abs_result, mpfr_result, MPFR_RNDD);
                mpfr_abs(abs_result1, mpfr_result1, MPFR_RNDD);
                                mpfr_sub(sub_result, abs_result, abs_result1, MPFR_RNDD);
    
                           //     mpfr_myw(&sub_result, PRECISION, fwp_out);
                double_error.value=mpfr_get_d(sub_result,MPFR_RNDD);
                                fprintf(fwp_out,"%16lX\n",double_error.parts.sw);
                        }  
		
}
fclose(fp);
fclose(fp1);
fclose(fwp_out);

	return 0;
}

