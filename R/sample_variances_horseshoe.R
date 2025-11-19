#' @title Samples variances from the horseshoe prior using Gruber & Kastner (2024)
#' 
#' @description Performs one Gibbs sampling iteration for the horseshoe prior
#' variance parameters. The horseshoe prior Carvalho, Polson, Scott (2010) is a 
#' continuous shrinkage prior for Bayesian variable selection with the 
#' hierarchical structure:
#' \deqn{\beta_j \sim N(0, \lambda_j^2 \tau^2)}
#' \deqn{\lambda_j \sim C^+(0, 1)}
#' \deqn{\tau \sim C^+(0, 1)}
#' where \eqn{C^+(0, 1)} denotes the half-Cauchy distribution, \eqn{\lambda_j^2} 
#' are the local shrinkage parameters (argument \code{theta}), and \eqn{\tau^2} 
#' is the global shrinkage parameter (argument \code{zeta}). The prior variance 
#' for coefficient \eqn{j} is \eqn{V_{i,j} = \lambda_j^2 \tau^2}.
#' 
#' The half-Cauchy distributions are represented using auxiliary variables 
#' \eqn{\nu_j} and \eqn{\varpi} to facilitate Gibbs sampling. This implementation
#' allows updating only a subset of coefficients specified by the indices in 
#' argument \code{ind}.
#'
#' @details This function is based on C++ code from the R package \pkg{bayesianVARs}
#' by Gruber & Kastner (2024) and is using objects and commands from the \pkg{armadillo} library.
#' Thanks to the \pkg{RcppArmadillo} package by Eddelbuettel, Francois, Bates, Ni, & Sanderson (2025).
#' 
#' @param coefs a \eqn{p}-vector with the current coefficient values \eqn{\beta_j}. 
#' \strong{C++}: an \code{arma::vec} vector object.
#' @param theta a \eqn{p}-vector with the local variance parameters \eqn{\lambda_j^2}, 
#' updated by reference. \strong{C++}: an \code{arma::vec} vector object.
#' @param zeta a numeric scalar with the global variance parameter \eqn{\tau^2}, 
#' updated by reference. \strong{C++}: a \code{double} scalar.
#' @param nu a \eqn{p}-vector with auxiliary variables for the local shrinkage, 
#' updated by reference. \strong{C++}: an \code{arma::vec} vector object.
#' @param varpi a numeric scalar with the auxiliary variable for the global 
#' shrinkage, updated by reference. \strong{C++}: a \code{double} scalar.
#' @return  a vector of variances' random draws. \strong{C++}: an \code{arma::vec} vector object.
#' 
#' @author Longcan Li \email{longcando@outlook.com}
#' 
#' @references 
#' 
#' Carvalho C.M., Polson N.G., Scott J.G. (2010). The horseshoe estimator for 
#' sparse signals. Biometrika, 97(2), 465-480. <doi:10.1093/biomet/asq017>
#' 
#' Eddelbuettel D., Francois R., Bates D., Ni B., Sanderson C. (2025). 
#' RcppArmadillo: 'Rcpp' Integration for the 'Armadillo' Templated Linear 
#' Algebra Library. R package version 15.0.2-2. <doi:10.32614/CRAN.package.RcppArmadillo>
#' 
#' Gruber L.,Kastner G. (2024). bayesianVARs: MCMC Estimation of Bayesian Vector Autoregressions.
#' R package version 0.1.5, <doi:10.32614/CRAN.package.bayesianVARs>
#' 
#' Makalic E., Schmidt D.F. (2016). A Simple Sampler for the Horseshoe Estimator. 
#' IEEE Signal Processing Letters, 23(1), 179-182. <doi:10.1109/LSP.2015.2503725>
#' 
#' Sanderson C., Curtin R. (2025). Armadillo: An Efficient Framework for 
#' Numerical Linear Algebra. International Conference on Computer and Automation 
#' Engineering, 303-307, <doi:10.1109/ICCAE64891.2025.10980539>
#' 
#' @examples 
#' sample_variances_horseshoe( rep(0, 2), rep(0, 2), 1, rep(1, 2), 1)
#' 
#' @export
sample_variances_horseshoe <- function(coefs, theta, zeta, nu, varpi) {
  
  p <- length(coefs)
  
  stopifnot(
    "The argument coefs must be a numeric vector with real numbers." =
      is.numeric(coefs) & all(!is.na(coefs))
  )
  stopifnot(
    "The argument theta must be a numeric vector with real numbers." =
      is.numeric(theta) & all(!is.na(theta)) & length(theta) == p
  )
  stopifnot(
    "The argument zeta must be a positive real number." =
      is.numeric(zeta) & length(zeta) == 1 & !is.na(zeta) & zeta > 0
  )
  stopifnot(
    "The argument nu must be a numeric vector with real numbers." =
      is.numeric(nu) & all(!is.na(nu)) & length(nu) == p
  )
  stopifnot(
    "The argument varpi must be a positive real number." =
      is.numeric(varpi) & length(varpi) == 1 & !is.na(varpi) & varpi > 0
  )
  
  # Call C++ function
  out <- .Call(`_StealLikeBayes_sample_variances_horseshoe`, 
                coefs, theta, zeta, nu, varpi)
  
  return(out)
}