#' @title Samples random draws from a generalised normal distribution using the 
#' Gibbs sampler by Waggoner & Zha (2003a)
#' 
#' @description Samples random numbers from a generalised normal distribution
#' for a restricted \eqn{N\times N} full rank matrix \eqn{X}. The matrix is drawn
#' row-by-row from their full conditional distributions using the Gibbs sampler
#' by Waggoner & Zha (2003a). The density is proportional to
#' \deqn{det(X)^{\nu - N}\exp(-\frac{1}{2}\sum_{n=1}^{N}x_nV_nS_nV_n'x_n')}
#' specified by the \eqn{N\times N} scale matrices \eqn{S+n}, a positive 
#' scalar-valued shape parameter \eqn{\nu}, and \eqn{r_n\times N} selection 
#' matrices \eqn{V_n} defining the restrictions. Zero restrictions may be 
#' imposed on th \eqn{X} matrix row-by-row as
#' \deqn{X_{n.} = x_nV_n}
#' where \eqn{1\times r_n} vectors \eqn{x_n} collect the unrestricted elements 
#' of \eqn{X} and the matrices \eqn{V_n} place them in appropriate spots of the 
#' \eqn{1\times N} row \eqn{X_{n.}}. The output may be normalised using the 
#' method by Waggoner & Zha (2003b) ensuring positive diagonal elements of the 
#' output matrices.
#' 
#' This method is useful for sampling the structural matrix of the structural
#' vector autoregressive models identified by exclusion restrictions, sign and 
#' exclusion restrictions, heteroskedasticity, and instrumental variables.
#' 
#' @details This function is based on C++ code from the R package \pkg{bsvars}
#' by Woźniak (2024,2025) and is using 
#' objects and commands from the \pkg{armadillo} library by Sanderson & Curtin (2025)
#' thanks to the \pkg{RcppArmadillo} package by Eddelbuettel, Francois, Bates, 
#' Ni, & Sanderson (2025).
#' 
#' @param n a positive integer with the number of draws to be sampled. 
#' \strong{C++}: a \code{int} object.
#' @param X an \eqn{N\times N} structural matrix with the starting values to 
#' initiate the Gibbs sampler. \strong{C++}: an \code{arma::mat} matrix object.
#' @param S an \eqn{N\times N\times N} array with \eqn{N\times N} row-specific
#' precision matrices \eqn{S_n}. \strong{C++}: an \code{arma::cube} object.
#' @param nu a positive integer number with the shape parameter \eqn{nu}. 
#' \strong{C++}: an \code{arma::int} object.
#' @param V a list with \eqn{N} elements each including \eqn{r_n\times N} 
#' matrices \eqn{V_n}. \strong{C++}: an \code{arma::field<arma::mat>} object.
#' @param normalise a logical value of whether the output should be normalised
#' following the method by Waggoner & Zha (2003b) ensuring positive signs of the 
#' diagonal elements of the sampled matrices. \strong{C++}: an \code{bool} object.
#' @return  an \eqn{N\times N\times n}-array with random draws from the 
#' generalised normal distribution. \strong{C++}: an \code{arma::cube} object.
#' 
#' @author Tomasz Woźniak \email{wozniak.tom@pm.me}
#' 
#' @references 
#' 
#' Eddelbuettel D., Francois R., Bates D., Ni B., Sanderson C. (2025). 
#' RcppArmadillo: 'Rcpp' Integration for the 'Armadillo' Templated Linear 
#' Algebra Library. R package version 15.0.2-2. <doi:10.32614/CRAN.package.RcppArmadillo>
#' 
#' Sanderson C., Curtin R. (2025). Armadillo: An Efficient Framework for 
#' Numerical Linear Algebra. International Conference on Computer and Automation 
#' Engineering, 303-307, <doi:10.1109/ICCAE64891.2025.10980539>
#' 
#' Waggoner D.F., Zha T., (2003a). A Gibbs Sampler for Structural Vector 
#' Autoregressions. Journal of Economic Dynamics and Control, 28(2), 349-366,
#' <doi:10.1016/S0165-1889(02)00168-9>.
#' 
#' Waggoner, D.F., Zha, T. (2003b). Likelihood Preserving Normalization in 
#' Multiple Equation Models. Journal of Econometrics, 114(2), 329-347.
#' <doi:10.1016/S0304-4076(03)00087-3>
#' 
#' Woźniak T. (2024). bsvars: Bayesian Estimation of Structural Vector 
#' Autoregressive Models, R package version 3.2, 
#' <doi:10.32614/CRAN.package.bsvars>.
#' 
#' Woźniak T. (2025). Fast and Efficient Bayesian Analysis of Structural Vector 
#' Autoregressions Using the R Package bsvars. University of Melbourne Working 
#' Paper, 1–25. <doi:10.48550/arXiv.2410.15090>.
#' 
#' @examples 
#' rgennorm(1, diag(2), array(diag(2), c(2,2,2)), 3, list(diag(2), matrix(1,1,2)))
#' 
#' @export
rgennorm <- function(n, X, S, nu, V, normalise = TRUE) {
  
  stopifnot(
    "The argument n must be a positive integer." =
      (n %% 1 == 0) & (n > 0)
  )
  stopifnot(
    "The argument X must be a numeric vector with real numbers." =
      is.matrix(X) & all(!is.na(X)) & (length(dim(X)) == 2)
  )
  stopifnot(
    "The argument S must be an array with NxN matrices." =
      is.array(S) & all(!is.na(S)) & (length(dim(S)) == 3) & (length(unique(dim(S))) == 1)
  )
  stopifnot(
    "The argument nu must be an integer greater or equal than N." =
      (nu %% 1 == 0) & (nu >= nrow(X))
  )
  stopifnot(
    "The argument normalise must be a logical value." =
      is.logical(normalise) & length(normalise) == 1
  )
  stopifnot(
    "The argument nu must be an integer greater or equal than N." =
      (nu %% 1 == 0) & (nu >= nrow(X))
  )
  out = .Call(`_StealLikeBayes_rgennorm`, n, X, S, nu, V, normalise)
  
  return(out)
}