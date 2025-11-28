#' @title Samples random draws from the generalized inverse Gaussian distribution
#' 
#' @description Samples random numbers from the generalized inverse Gaussian 
#' distribution with density proportional to:
#' \deqn{f(x) = x^{\lambda - 1} e^{-\frac{1}{2}(\chi/x + \psi x)},}
#' with the parameters having to satisfy the conditions:
#' \deqn{%
#' \begin{array}{l}
#' \lambda > 0,\, \psi > 0, \chi \geq 0, \quad\mbox{or} \\
#' \lambda = 0,\, \psi > 0, \chi > 0,    \quad\mbox{or}  \\
#' \lambda < 0,\, \psi \geq 0, \chi > 0.
#' \end{array}
#' }
#' The sampling algorithm proposed by Hörmann & Leydold (2013) is implemented.
#' 
#' This method is useful for sampling variance coefficients that arise in problems
#' with their likelihood in the form of th inverse gamma distribution and assuming 
#' a gamma prior.
#' 
#' @details This function is based on C++ code from the R package \pkg{shrinkTVP}
#' by Knaus, Bitto-Nemling, Cadonna, Frühwirth-Schnatter (2021) and also uses
#' functionality of the \pkg{GIGrvg} package by Leydold & Hörmann (2023).
#' It uses random number generators from the \pkg{armadillo} library by Sanderson & Curtin (2025)
#' thanks to the \pkg{RcppArmadillo} package by Eddelbuettel, Francois, Bates, 
#' Ni, & Sanderson (2025)
#' 
#' @param lambda a real scalar representing parameter \eqn{\lambda}.
#' \strong{C++}: a \code{double} object.
#' @param chi a real scalar representing parameter \eqn{\chi}.
#' \strong{C++}: a \code{double} object.
#' @param psi a real scalar representing parameter \eqn{\psi}.
#' \strong{C++}: a \code{double} object.
#' @return  random draw from the GIG distribution. \strong{C++}: a \code{double} object.
#' 
#' @author Tomasz Woźniak \email{wozniak.tom@pm.me}
#' 
#' @references 
#' 
#' Eddelbuettel D., Francois R., Bates D., Ni B., Sanderson C. (2025). 
#' RcppArmadillo: 'Rcpp' Integration for the 'Armadillo' Templated Linear 
#' Algebra Library. R package version 15.0.2-2. <doi:10.32614/CRAN.package.RcppArmadillo>
#' 
#' Hörmann W., Leydold J. (2013). Generating generalized inverse Gaussian random variates,
#' Statistics and Computing 24, 547--557, <doi:10.1007/s11222-013-9387-3>.
#' 
#' Leydold J., Hörmann W. (2023). GIGrvg: Random Variate Generator for the GIG Distribution,
#' R package version 0.8, <doi:10.32614/CRAN.package.GIGrvg>.
#' 
#' Knaus, P., Bitto-Nemling, A., Cadonna, A., & Frühwirth-Schnatter, S. (2021). 
#' Shrinkage in the Time-Varying Parameter Model Framework Using the R Package shrinkTVP. 
#' Journal of Statistical Software, 100(13), 1–32. <doi:10.18637/jss.v100.i13>.
#' 
#' Sanderson C., Curtin R. (2025). Armadillo: An Efficient Framework for 
#' Numerical Linear Algebra. International Conference on Computer and Automation 
#' Engineering, 303-307, <doi:10.1109/ICCAE64891.2025.10980539>
#' 
#' @examples 
#' rgig1(1, 1, 1)
#' 
#' @export
rgig1 <- function(lambda, chi, psi) {
  
  stopifnot(
    "The argument lambda must be a real number." =
      is.numeric(lambda) & !is.na(lambda) & length(lambda) == 1,
    
    "The argument chi must be a real number." =
      is.numeric(chi) & !is.na(chi) & length(chi) == 1,
    
    "The argument psi must be a real number." =
      is.numeric(psi) & !is.na(psi) & length(psi) == 1,
    
    "Incorrect values for parameters lambda, chi, or psi." =  
      !(!(is.finite(lambda) && is.finite(chi) && is.finite(psi)) ||
          (chi <  0. || psi < 0)      ||
          (chi == 0. && lambda <= 0.) ||
          (psi == 0. && lambda >= 0.)) 
  )
  
  out = .Call(`_StealLikeBayes_rgig1`, lambda, chi, psi)
  
  return(out)
}
