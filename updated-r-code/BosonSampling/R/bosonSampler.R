bosonSampler = function(A, sampleSize, perm = FALSE){
#
# A complex matrix
#
# out:  samples = list of boson sample mode sequences
#       perms   = list of associated permanents
#       pmfs    = list of associated pmfs
#
# transpose A -- benefit since both R and Armadillo store matrices in column order
#
	A = t(A)
	m = ncol(A); n = nrow(A)
	if(perm){
		permList <- matrix(0,ncol=sampleSize)
		pmfList <- matrix(0,ncol=sampleSize)
	}
	sampMatrix <- matrix(0,nrow=n,ncol=sampleSize)
	for(k in 1:sampleSize){
#
# permute rows of A
#
		reorder <- sample.int(n,useHash=FALSE)
#
# start with row 1 and sample the first mode c_1
# i.e. the first mode in an individual sample sequence
#
		permVector <- A[reorder[1],]
		probVector <- Mod(permVector)^2
		sampMatrix[1,k] <- sample.int(m,
					      size = 1,
					      prob = probVector,
					      useHash=FALSE)
#
# now sample remaining modes c_2,c_3,...,c_n in an individual sequence
#
		modeLimit <- 2
		while(modeLimit <= n){
			Asub_in <- A[reorder[1:modeLimit],]
			Asub_samp <- Asub_in[,sampMatrix[,k],drop=FALSE]
			subPerm <- cxPermMinors(Asub_samp)
#
# permanents of submatrices using Laplace-type expansion
#
			permVector <- t(subPerm) %*% Asub_in
			probVector <- Mod(permVector)^2
#
# next mode in an individual sequence 
#
			sampMatrix[modeLimit,k] <- 
				sample.int(m, 
					   size = 1,
					   prob = probVector,
					   useHash=FALSE)
			modeLimit <- modeLimit + 1
		}
#
# build list of sample sequences and associated permanents/pmfs
#
		if(perm){
			permList[k] = permVector[n]
			pmfdenom <- prod(factorial(tabulate(sampMatrix[,k])))
			pmfList[k] = probVector[n]/pmfdenom
		}
	}

	if(perm){
		list(sampMatrix, perms = permList, pmfs = pmfList)
	} else {
		list(sampMatrix, perms = NULL, pmfs = NULL)
	}
}

