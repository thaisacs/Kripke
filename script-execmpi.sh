DATASET=exp-results
rm -rf $DATASET
mkdir $DATASET

app=./build/bin/kripke.exe --niter 100

perf stat -o $DATASET/perf-asc-kripke.out $app
/usr/bin/time -o $DATASET/time-asc-kripke.out -v $app

#ltrace -o $DATASET/mpi-asc-kripke.out ./build/bin/kripke.exe --niter 100
#cd $DATASET
#cat mpi-asc-kripke.out | grep "MPI" > mpi2-asc-kripke.out
#rm mpi-asc-kripke.out
#mv mpi2-asc-kripke.out mpi-asc-kripke.out
