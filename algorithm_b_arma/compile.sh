#g++ bosonSampling_b_arma.cpp cxPermMinors.cpp randomUnitary.cpp -o a.out -std=c++11 -larmadillo -Ofast -march=native -pipe

g++-8 bosonSampling_b_arma.cpp cxPermMinorsNThreads.cpp randomUnitary.cpp -o a.out -std=c++11 -larmadillo -Ofast -march=native -fopenmp -pipe

#icpc bosonSampling_b_arma.cpp cxPermMinors.cpp randomUnitary.cpp -o a.out -std=c++11 -I ~/Downloads/armadillo-9.200.8/include -DARMA_DONT_USE_WRAPPER -lblas -llapack
