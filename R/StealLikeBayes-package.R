#  #####################################################################################
#  R package StealLikeBayes by Tomasz Woźniak Copyright (C) 2025
#
#  This file is part of the R package StealLikeBayes: A C++ compendium of 
#  Bayesian statistical routines for R packages
#
#  The R package StealLikeBayes is free software: you can redistribute it
#  and/or modify it under the terms of the GNU General Public License
#  as published by the Free Software Foundation, either version 3 or
#  any later version of the License.
#
#  The R package StealLikeBayes is distributed in the hope that it will be
#  useful, but WITHOUT ANY WARRANTY; without even the implied warranty
#  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
#  General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with the R package StealLikeBayes If that is not the case, please
#  refer to <http://www.gnu.org/licenses/>.
#  #####################################################################################
#' @title A C++ compendium of Bayesian statistical routines for R packages
#'
#' @description This is a compendium of C++ routines useful for Bayesian 
#' statistics. We steal other people's C++ code, repurpose it, and export it so 
#' developers of R packages can use it in their C++ code. We actually don't 
#' steal anything, or claim that Thomas Bayes did, but copy code that is 
#' compatible with our GPL 3 licence, fully acknowledging the authorship of the 
#' original code.
#' 
#' @note This is a collaborative project. You are welcome to contribute. Please,
#' read the documentation at \url{https://bsvars.org/StealLikeBayes/dev/} and 
#' StealLikeBayes!
#' 
#' @name StealLikeBayes-package
#' @aliases StealLikeBayes-package StealLikeBayes
#' @docType package
#' @importFrom Rcpp sourceCpp
#' @useDynLib StealLikeBayes, .registration = TRUE
#' @keywords internal Bayesian
'_PACKAGE'