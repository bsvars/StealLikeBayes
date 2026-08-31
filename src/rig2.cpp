#include <RcppArmadillo.h>

using namespace arma;

/* This function was contributed by Tomasz Woźniak based on code from the
 * GPL-3 package bsvars by Tomasz Woźniak and rewritten for StealLikeBayes.
 */

// [[Rcpp::interfaces(cpp)]]
// [[Rcpp::export]]
arma::vec rig2 (
    const int n,
    const double s,
    const double nu
) {
  vec rig2 = s / chi2rnd(nu, n);
  return rig2;
}
