#!/bin/sh
PATH1="home/liangjinxiu/local"

function help()
{
echo -e "\e[1;31m   /main/analysis help:\e[0m"
echo -e "\e[1;31m	【--errorplot】 eg:source analysis.sh 5 sin 2.14 glibc\e[0m"
echo -e "\e[1;31m	【--Emaxmin】 eg:source analysis.sh --Emaxmin 5 sin 2.14 glibc\e[0m"
echo -e "\e[1;31m	【--Emaxminplot】 eg:source analysis.sh --Emaxminplot sin 2.14 glibc\e[0m"
echo -e "\e[1;31m	【--MAXMIN】 eg:source analysis.sh --MAXMIN sin 2.14 glibc\e[0m"
echo -e "\e[1;31m	【--searchhigh】 eg:source analysis.sh --searchhigh 5 1.0e-15 sin 2.14 glibc\e[0m"
echo -e "\e[1;31m	【--goodbad】 eg:source analysis.sh --goodbad 5 sin 2.19 2.14 glibc\e[0m"
echo -e "\e[1;31m	【--goodbadplot】 eg:source analysis.sh --goodbadplot sin 2.19 2.14\e[0m"
echo -e "\e[1;31m	【--help】\e[0m"
}

if [ $1="--help" ]
then
help
fi

case "$1" in
"--errorplot") 
cd ./bin
g++ hex2long.cpp -o hex2long
./hex2long
export PATH=/${PATH1}/python3/bin/:$PATH
echo -e "executing……\n"
python3 errorplot.py $2 $3 $4 $5
echo "$5$4$3 errorplot Completed!"
cd ..
;;

"--Emaxmin")
cd ./bin
export PATH=/${PATH1}/python3/bin/:$PATH
echo -e "executing……\n"
python3 Emaxmin.py $2 $3 $4 $5
echo "$5$4$3 Emaxmin Completed!"
cd ..
;;

"--Emaxminplot")
cd ./bin
export PATH=/${PATH1}/python3/bin/:$PATH
echo -e "executing……\n"
python3 Emaxminplot.py $2 $3 $4
echo "$4$3$2 Emaxminplot Completed!"
cd ..
;;

"--MAXMIN")
cd ./bin
echo -e "executing……\n"
python3 MAXMIN.py $2 $3 $4
echo "$4$3$2 MAXMIN Completed!"
cd ..
;;

"--searchhigh")
cd ./bin
echo -e "executing……\n"
python3 searchhigh.py $2 $3 $4 $5 $6
echo "$4$5$6_$3 searchhigh Completed!"
cd ..
;;

"--goodbad")
cd ./bin
g++ -std=c++11 -w pointcompare.cpp -o pointcompare -I/${PATH1}/gmp-6.1.2/include -L/${PATH1}/gmp-6.1.2/lib -lgmp -I/${PATH1}/mpfr-4.0.2/include -L/${PATH1}/mpfr-4.0.2/lib -lmpfr
export LD_LIBRARY_PATH=/${PATH1}/mpfr-4.0.2/lib:$LD_LIBRARY_PATH

echo -e "executing……\n"
./pointcompare $2 $3 $4 $5 $6
export PATH=/${PATH1}/python3/bin/:$PATH
python3 goodbad.py $2 $3 $4 $5 $6
echo "$3$4_$5 goodbad Completed!"
cd ..
;;

"--goodbadplot")
cd ./bin
echo -e "executing……\n"
export PATH=/${PATH1}/python3/bin/:$PATH
python3 goodbadplot.py $2 $3 $4
echo "$4$5$6_$3 searchhigh Completed!"
;;

*)
echo "please input right command!"
;;
esac




