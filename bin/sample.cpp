#include <stdio.h>
#include <math.h>
#include <bitset>
#include <fstream>
#include <map>
#include<stdlib.h>
#include<iostream>
#include<string>
#include<cstring>
using namespace std;
int s = 0x000;
int s1 = 0x7FF;
//int NUM =5;

FILE *fwp = fopen("../data/sampleResult1.txt", "w+");
void change_M(bitset<64>dou_number,int NUM)
{

	bitset<1>M;
	for (int j = 0; j<NUM;)
	{
		map<string, int> mediam;
		for (int i = 0; i<52; i++)
		{
			M = bitset<1>(rand() % 2);
			dou_number[i] = M[0];

		}

		map<string, int>::iterator ite = mediam.find(dou_number.to_string());
		if (ite == mediam.end())
		{
			j++;
			mediam.insert(map<string, int>::value_type(dou_number.to_string(), 1));
			fprintf(fwp, "%16lX\n", *(&dou_number));
		}
	}



}
bitset<64> change_E(bitset<64>dou_number, int s)
{
	bitset<11>E;
	E = bitset<11>(s);
	for (int i = 0; i<11; i++)
	{
		dou_number[i + 52] = E[i];

	}
	return dou_number;
}


int main(int argc, char** argv)
{
int NUM;
NUM=atoi(argv[1]);
	bitset<64>dou_number;
	dou_number.set(63, 0);
	for (s; s<=s1; s++)
	{
		dou_number = change_E(dou_number, s);

		change_M(dou_number,NUM);
	}
	dou_number.set(63, 1);
	s = 0x000;
	for (s; s<=s1; s++)//s1
	{
		dou_number = change_E(dou_number, s);

		change_M(dou_number,NUM);
	}
	fclose(fwp);
	return 0;


}



