\name{randomUnitary}
\alias{randomUnitary}
\title{Random unitary}
\usage{
randomUnitary(size)
}
\arguments{
\item{size}{dimension of matrix}
}
\description{
Generates a random unitary matrix (square)
}
\examples{
m <- 25 # size of matrix (m x m)
set.seed(7)
U <- randomUnitary(m)
#  
n <- 5 # First n columns
A <- U[,1:n]
}

