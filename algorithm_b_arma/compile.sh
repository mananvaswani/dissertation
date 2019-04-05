g++ bosonSampling_b_arma.cpp cxPermMinors.cpp randomUnitary.cpp -o a.out -std=c++11 -larmadillo -Ofast -march=native -pipe

#g++ bosonSampling_b_arma.cpp cxPermMinorsNThreads.cpp randomUnitary.cpp -o a.out -std=c++11 -larmadillo -O3 -march=native

#icpc bosonSampling_b_arma.cpp cxPermMinors.cpp randomUnitary.cpp -o a.out -std=c++11 -I ~/Downloads/armadillo-9.200.8/include -DARMA_DONT_USE_WRAPPER -lblas -llapack
