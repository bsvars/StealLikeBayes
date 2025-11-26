#' @title Generate Truncated Multivariate Normal Samples via Hamiltonian Monte Carlo
#'
#' @description
#' Generate \eqn{p}-dimensional truncated multivariate normal samples that satisfy
#' an inequality constraint \deqn{F \times x + g \ge 0,} where \eqn{x} is a column
#' vector of the generated sample. The sampler is an exact Hamiltonian Monte Carlo
#' (HMC) sampler as described in Pakman and Paninski (2014).
#'
#' @details
#' The function generates samples from a truncated multivariate normal distribution
#' with mean \code{mean} and covariance \code{cov}, subject to linear constraints
#' defined by \code{Fmat} and \code{g}.
#'
#' The user should supply an initial value that strictly satisfies the inequality
#' constraints, although the generated samples only satisfy them weakly.
#'
#' No check for symmetry is performed on the covariance matrix.
#'
#' It is advisable to use a small burn-in period (e.g., 10) to allow the Markov
#' chain to reach stationarity.
#'
#' This function is a wrapper around a C++ implementation adapted from the 'tnorm'
#' R package by Kenyon Ng.
#'
#' @param n a positive integer with the number of samples.
#' \strong{C++}: an \code{int} object.
#' @param mean a \eqn{p}-dimensional mean vector.
#' \strong{C++}: an \code{Eigen::VectorXd} object.
#' @param cov a \eqn{p \times p} covariance matrix of the normal distribution.
#' \strong{C++}: an \code{Eigen::MatrixXd} object.
#' @param initial a \eqn{p}-dimensional initial value vector for the Markov chain.
#' \strong{C++}: an \code{Eigen::VectorXd} object.
#' @param Fmat an \eqn{m \times p} constraint matrix \eqn{F} defining linear
#' inequalities, where \eqn{m} is the number of constraints.
#' \strong{C++}: an \code{Eigen::MatrixXd} object.
#' @param g an \eqn{m}-dimensional constraint vector defining linear inequalities.
#' \strong{C++}: an \code{Eigen::VectorXd} object.
#' @param burn a non-negative integer with the number of burn-in iterations
#' before collecting samples.
#' \strong{C++}: an \code{int} object.
#'
#' @return An \eqn{n \times p} matrix with each row corresponding to a sample.
#' \strong{C++}: an \code{Eigen::MatrixXd} object.
#'
#' @references
#' Pakman, A. and Paninski, L. (2014). Exact Hamiltonian Monte Carlo for
#' Truncated Multivariate Gaussians. Journal of Computational and Graphical
#' Statistics, 23(2), 518–542. <doi:10.1080/10618600.2013.788448>
#'
#' Ng, K. (2024). tnorm: Generate Multivariate Truncated Normal Samples. R
#' package version 0.0.1. <https://github.com/weiyaw/tnorm>
#'
#' Bates, D. and Eddelbuettel, D. (2013). Fast and Elegant Numerical Linear
#' Algebra Using the RcppEigen Package. Journal of Statistical Software, 52(5),
#' 1–24. <doi:10.18637/jss.v052.i05>
#'
#' @examples
#' rtmvnorm_hmc(1, c(0, 0), diag(2), c(0, 2), diag(2), c(1, -1), 1)
#'
#' @export
rtmvnorm_hmc <- function(n, mean, cov, initial, Fmat, g, burn) {
  stopifnot(
    "Mean must be a vector." =
      is.vector(mean) || (is.matrix(mean) && min(dim(mean)) == 1)
  )
  stopifnot(
    "Covariance must be a square matrix." =
      is.matrix(cov) && ncol(cov) == nrow(cov)
  )
  stopifnot(
    "Inconsistent dimensions of the mean and covariance." =
      ncol(cov) == length(mean)
  )
  stopifnot(
    "Inconsistent dimensions of the mean and the initial value." =
      length(initial) == length(mean)
  )
  stopifnot(
    "Initial value violates constraints." =
      all(Fmat %*% initial + g >= 0)
  )

  .Call(`_StealLikeBayes_rtmvnorm_hmc`, n, mean, cov, initial, Fmat, g, burn)
}
