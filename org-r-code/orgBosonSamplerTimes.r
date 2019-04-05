library (BosonSampling)

run_one_sample <- function(n, m) {
    ptm <- proc.time()
    A <- randomUnitary(m)[,1:n]
    valueList <- bosonSampler(A, sampleSize = 1)$values
    print (valueList)
    apply(valueList,2, sort)
    time <- c (n , (proc.time() - ptm)[3]*1000)
    return (time)
}

get_many_samples <- function(num) {
    timedata <- matrix(ncol=2)
    for (i in 2:num) {
        n <- i
        m <- i*i
        r = run_one_sample(n, m)
        timedata <- rbind(timedata, r)
    }
    write.csv(timedata, file = "data_r_org.csv", row.names= FALSE)
}
