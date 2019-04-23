#!/bin/bash

g++-8 bosonSampling_b_arma.cpp cxPermMinors.cpp cxPermMinorsNThreads.cpp randomUnitary.cpp -o a.out -std=c++11 -larmadillo -Ofast -march=native -fopenmp -pipe

#icpc bosonSampling_b_arma.cpp cxPermMinors.cpp cxPermMinorsNThreads.cpp randomUnitary.cpp -o a.out -std=c++11 -I ~/Downloads/armadillo-9.200.8/include -DARMA_DONT_USE_WRAPPER -lblas -llapack -Ofast -march=native -qopenmp


## BC4 compile

#g++ bosonSampling_b_arma.cpp cxPermMinors.cpp cxPermMinorsNThreads.cpp randomUnitary.cpp -o a.out -std=c++11 -I /mnt/storage/home/mv15872/arma/include -DARMA_DONT_USE_WRAPPER -lblas -llapack -Ofast -march=native -fopenmp -pipe

#icc bosonSampling_b_arma.cpp cxPermMinors.cpp cxPermMinorsNThreads.cpp randomUnitary.cpp -o a.out -std=c++11 -I /mnt/storage/home/mv15872/arma/include -DARMA_DONT_USE_WRAPPER -lblas -llapack -Ofast -march=native -qopenmp
