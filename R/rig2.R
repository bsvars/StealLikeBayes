#' @title Sample from the inverted gamma-2 distribution
#'
#' @description Samples independent random numbers from the inverted gamma-2
#' distribution, denoted by \eqn{IG2(s, \nu)}, with density
#' \deqn{f(x) = \frac{(s/2)^{\nu/2}}{\Gamma(\nu/2)}
#' x^{-(\nu+2)/2}\exp\left(-\frac{s}{2x}\right), \quad x > 0.}
#' The draws are generated as \eqn{s/Z}, where \eqn{Z} follows a chi-squared
#' distribution with \eqn{\nu} degrees of freedom.
#'
#' This distribution is commonly used for variance parameters in Bayesian
#' models.
#'
#' @details This function is based on C++ code from the GPL-3 R package
#' \pkg{bsvars} by Woźniak (2024, 2025). It uses random-number generators from
#' the \pkg{armadillo} library by Sanderson & Curtin (2025), made available to R
#' through the \pkg{RcppArmadillo} package by Eddelbuettel et al. (2025).
#'
#' @param n a positive integer giving the number of draws.
#' \strong{C++}: an \code{int} object.
#' @param s a positive real scalar giving the scale parameter.
#' \strong{C++}: a \code{double} object.
#' @param nu a positive real scalar giving the degrees-of-freedom parameter.
#' \strong{C++}: a \code{double} object.
#'
#' @return A numeric vector of length \code{n} containing independent draws
#' from the inverted gamma-2 distribution. \strong{C++}: an
#' \code{arma::vec} object.
#'
#' @author Tomasz Woźniak \email{wozniak.tom@pm.me}
#'
#' @references
#'
#' Bauwens L., Lubrano M., Richard J.-F. (1999). \emph{Bayesian Inference in
#' Dynamic Econometric Models}. Oxford University Press.
#'
#' Eddelbuettel D., François R., Bates D., Ni B., Sanderson C. (2025).
#' RcppArmadillo: 'Rcpp' Integration for the 'Armadillo' Templated Linear
#' Algebra Library. R package version 15.0.2-2.
#' \doi{10.32614/CRAN.package.RcppArmadillo}
#'
#' Sanderson C., Curtin R. (2025). Armadillo: An Efficient Framework for
#' Numerical Linear Algebra. International Conference on Computer and
#' Automation Engineering, 303--307. \doi{10.1109/ICCAE64891.2025.10980539}
#'
#' Woźniak T. (2026). bsvars: Bayesian Estimation of Structural Vector
#' Autoregressive Models, R package version 4.0.
#' \doi{10.32614/CRAN.package.bsvars}
#'
#' Woźniak T. (2026). Fast and Efficient Bayesian Analysis of Structural
#' Vector Autoregressions Using the R Package bsvars. University of Melbourne
#' Working Paper, 1--25. \doi{10.48550/arXiv.2410.15090}
#'
#' @examples
#' rig2(5, 1, 10)
#'
#' @export
rig2 <- function(n, s, nu) {
  stopifnot(
    "The argument n must be a positive integer." =
      is.numeric(n) && length(n) == 1 && !is.na(n) && is.finite(n) &&
        n > 0 && n %% 1 == 0,
    "The argument s must be a positive real number." =
      is.numeric(s) && length(s) == 1 && !is.na(s) && is.finite(s) && s > 0,
    "The argument nu must be a positive real number." =
      is.numeric(nu) && length(nu) == 1 && !is.na(nu) && is.finite(nu) && nu > 0
  )

  out <- .Call(`_StealLikeBayes_rig2`, n, s, nu)

  return(out)
}
