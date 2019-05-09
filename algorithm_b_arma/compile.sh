#!/bin/bash

#g++-8 bosonSampling_b_arma.cpp cxPermMinors.cpp randomUnitary.cpp -o a.out -std=c++11 -larmadillo

g++-8 bosonSampling_b_arma.cpp cxPermMinors.cpp cxPermMinorsNThreads.cpp randomUnitary.cpp -o a.out -std=c++11 -larmadillo -fopenmp -Ofast -funroll-loops -pipe

#icpc bosonSampling_b_arma.cpp cxPermMinors.cpp cxPermMinorsNThreads.cpp randomUnitary.cpp -o a.out -std=c++11 -I ~/Downloads/armadillo-9.200.8/include -DARMA_DONT_USE_WRAPPER -lblas -llapack -qopenmp #-O3 -xHOST


## BC4 compile

#g++ bosonSampling_b_arma.cpp cxPermMinors.cpp randomUnitary.cpp -o a.out -std=c++11 -I /mnt/storage/home/mv15872/arma/include -DARMA_DONT_USE_WRAPPER -lblas -llapack

#g++ bosonSampling_b_arma.cpp cxPermMinors.cpp cxPermMinorsNThreads.cpp randomUnitary.cpp -o a.out -std=c++11 -I /mnt/storage/home/mv15872/arma/include -DARMA_DONT_USE_WRAPPER -lblas -llapack -Ofast -funroll-loops -march=native -mtune=native -fopenmp -pipe

#icc bosonSampling_b_arma.cpp cxPermMinors.cpp cxPermMinorsNThreads.cpp randomUnitary.cpp -o a.out -std=c++11 -I /mnt/storage/home/mv15872/arma/include -DARMA_DONT_USE_WRAPPER -lblas -llapack -O3 -xHOST -qopenmp
