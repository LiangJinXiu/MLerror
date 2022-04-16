#!/bin/sh
PATH1="home/liangjinxiu/local"

function help()
{
echo -e "\e[1;36m   /main help:\e[0m"
echo -e "\e[1;36m	【--sampling】 eg:source main.sh --sampling 5\e[0m"
echo -e "\e[1;36m	【--Oracle】 eg:source main.sh --Oracle sin\e[0m"
echo -e "\e[1;36m	【--glibc】 eg:source main.sh --glibc sin 2.14\e[0m"
echo -e "\e[1;36m	【--gsl】 eg:source main.sh --gsl sin 2.6\e[0m"
echo -e "\e[1;36m	【--mkl】 eg:source main.sh --mkl sin 2020\e[0m"
echo -e "\e[1;36m	【--error】 eg:source main.sh --error 5 sin 2.14 glibc\e[0m"
echo -e "\e[1;36m	【--analysis】\e[0m"
echo -e "\e[1;36m	【--help】\e[0m"
}

if [ $1="--help" ]
then
help
fi

case "$1" in
"--sampling") 
cd ./bin
g++ sample.cpp -o sample
echo -e "executing……\n"
./sample $2
echo "sampling Completed!"
cd ..
;;

"--Oracle")
cd ./bin
g++ -std=c++11 -w oracle.cpp -o oracle -I/${PATH1}/gmp-6.1.2/include -L/${PATH1}/gmp-6.1.2/lib -lgmp -I/${PATH1}/mpfr-4.0.2/include -L/${PATH1}/mpfr-4.0.2/lib -lmpfr
export LD_LIBRARY_PATH=/${PATH1}/mpfr-4.0.2/lib:$LD_LIBRARY_PATH
echo -e "executing……\n"
./oracle $2
echo "$2 Oracle Completed!"
cd ..
;;

"--glibc")
cd ./data
mkdir glibc$3
cd ..
cd ./bin
g++ -std=c++11 -w glibc.cpp -o glibc -Wl,--rpath=/${PATH1}/glibc-$3/lib -Wl,--dynamic-linker=/${PATH1}/glibc-$3/lib/ld-linux-x86-64.so.2 -lm
#export LD_LIBRARY_PATH=/${PATH1}/glibc-$3/lib:$LD_LIBRARY_PATH
echo -e "executing……\n"
./glibc $2 $3
echo "$2 test Completed!"
cd ..
;;

"--gsl")
cd ./data
mkdir gsl$3
cd ..
cd ./bin
g++ -std=c++11 -w gsl.cpp -o gsl I/${PATH1}/gsl-$3/include -L/${PATH1}/gsl-$3/lib -lgsl -lgslcblas
echo -e "executing……\n"
./gsl $2 $3
echo "$2 test Completed!"
cd ..
;;

"--mkl")
cd ./data
mkdir mkl$3
cd ..
cd ./bin
g++ -std=c++11 -w mkl.cpp -o mkl -I/${PATH1}/mkl-$3/mkl/include -lmkl_rt -L/${PATH1}/mkl-$3/mkl/lib/intel64 -L/${PATH1}/mkl-$3/lib/intel64
echo -e "executing……\n"
./mkl $2 $3
echo "$2 test Completed!"
cd ..
;;

"--error")
cd ./bin
g++ -std=c++11 -w error.cpp -o error -I/${PATH1}/gmp-6.1.2/include -L/${PATH1}/gmp-6.1.2/lib -lgmp -I/${PATH1}/mpfr-4.0.2/include -L/${PATH1}/mpfr-4.0.2/lib -lmpfr
export LD_LIBRARY_PATH=/${PATH1}/mpfr-4.0.2/lib:$LD_LIBRARY_PATH
echo -e "executing……\n"
./error $2 $3 $4 $5
echo "$3 error Completed!"
cd ..
;;

"--analysis")
source analysis.sh --help
;;

*)
echo "please input right command!"
;;
esac




