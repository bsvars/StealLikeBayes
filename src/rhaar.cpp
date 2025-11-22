
#include <RcppArmadillo.h>

using namespace arma;

/* This function was stolen by Xiaolei from package bsvarSIGNs by Xiaolei Wang
 * and Tomasz Woźniak on 18 November 2025 and then rewritten.
 */
// QR decomposition, where the diagonal elements of R are positive
// [[Rcpp::interfaces(cpp)]]
// [[Rcpp::export]]
arma::mat qr_sign_cpp(const arma::mat &A)
{
  int N = A.n_rows;

  arma::mat Q(N, N), R(N, N);
  arma::qr_econ(Q, R, A);

  // Check and modify the diagonal elements of R
  for (arma::uword i = 0; i < R.n_cols; ++i)
  {
    if (R(i, i) < 0)
    {
      Q.col(i) *= -1; // Change sign of the corresponding row in Q
    }
  }

  return Q;
}

/* This function was stolen by Xiaolei from package bsvarSIGNs by Xiaolei Wang
 * and Tomasz Woźniak on 18 November 2025 and then rewritten.
 */
// Sample uniformly from the space of nxn orthogonal matrices
// [[Rcpp::interfaces(cpp)]]
// [[Rcpp::export]]
arma::mat rhaar1(const int &n)
{
  return qr_sign_cpp(arma::mat(n, n, fill::randn));
}
