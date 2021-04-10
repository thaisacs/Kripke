DATASET=exp-results
rm -rf $DATASET
mkdir $DATASET

sudo perf stat -o $DATASET/perf-asc-kripke.out ./build/bin/kripke.exe --niter 100
/usr/bin/time -o $DATASET/time-asc-kripke.out -v ./build/bin/kripke.exe --niter 100
ltrace -o $DATASET/mpi-asc-kripke.out ./build/bin/kripke.exe --niter 100

cd $DATASET
cat mpi-asc-kripke.out | grep "MPI" > mpi2-asc-kripke.out
rm mpi-asc-kripke.out
mv mpi2-asc-kripke.out mpi-asc-kripke.out

#mpirun -n 2 ./lmp -var t 300 -echo screen -in lj/in.lj
