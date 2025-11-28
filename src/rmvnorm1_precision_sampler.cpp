
#include <RcppArmadillo.h>

using namespace Rcpp;
using namespace arma;


/* This function was stolen by Tomasz from package stochvol by Darjus Hosszejni 
 * and Gregor Kastner on 6 November 2025 and then rewritten.
 */
// [[Rcpp::interfaces(cpp)]]
// [[Rcpp::export]]
Rcpp::List cholesky_tridiagonal(
    const arma::vec&    omega_diag,
    const double&       omega_offdiag
) {
  const int T = omega_diag.n_elem - 1;
  vec chol_diag(T+1);
  vec chol_offdiag(T+1);
  chol_diag[0] = sqrt(omega_diag[0]);
  for (int j = 1; j < T+1; j++) {
    chol_offdiag[j-1] = omega_offdiag/chol_diag[j-1];
    chol_diag[j] = std::sqrt(omega_diag[j]-chol_offdiag[j-1]*chol_offdiag[j-1]);
  }
  return List::create(_["chol_diag"]=chol_diag, _["chol_offdiag"]=chol_offdiag);
} // END cholesky_tridiagonal



/* This function was stolen by Tomasz from package stochvol by Darjus Hosszejni 
 * and Gregor Kastner on 6 November 2025 and then rewritten.
 */
// [[Rcpp::interfaces(cpp)]]
// [[Rcpp::export]]
arma::vec forward_algorithm(
    const arma::vec& chol_diag,
    const arma::vec& chol_offdiag,
    const arma::vec& covector
) {
  const int T = chol_diag.n_elem - 1;
  vec htmp(T+1);
  htmp[0] = covector[0]/chol_diag[0];
  for (int j = 1; j < T+1; j++) {
    htmp[j] = (covector[j] - chol_offdiag[j-1]*htmp[j-1])/chol_diag[j];
  }
  return htmp;
} // END forward_algorithm



/* This function was stolen by Tomasz from package stochvol by Darjus Hosszejni 
 * and Gregor Kastner on 6 November 2025 and then rewritten.
 */
// [[Rcpp::interfaces(cpp)]]
// [[Rcpp::export]]
arma::vec backward_algorithm(
    const arma::vec& chol_diag,
    const arma::vec& chol_offdiag,
    const arma::vec& htmp
) {
  const int T = chol_diag.size() - 1;
  vec h(T+1);
  h[T] = htmp[T] / chol_diag[T];
  for (int j = T-1; j >= 0; j--) {
    h[j] = (htmp[j] - chol_offdiag[j] * h[j+1]) / chol_diag[j];
  }
  return h;
} // END backward_algorithm



/* This function was stolen by Tomasz from package stochvol by Darjus Hosszejni 
 * and Gregor Kastner on 6 November 2025 and then rewritten.
 */
// [[Rcpp::interfaces(cpp)]]
// [[Rcpp::export]]
arma::vec rmvnorm1_precision_sampler(
    const arma::vec&     location,
    const arma::vec&     precision_diag,
    const double&        precision_offdiag
) {
  int T               = location.n_rows;
  vec  epsilon(T, fill::randn);
  List precision_chol = cholesky_tridiagonal(precision_diag, precision_offdiag);    // Cholesky decomposition using a dedicated technique
  vec  aa             = forward_algorithm(precision_chol["chol_diag"],              // this forward substitution can be performed outside of the loop
                                          precision_chol["chol_offdiag"],
                                                        location);
  vec draw_ssar1      = backward_algorithm(precision_chol["chol_diag"],
                                           precision_chol["chol_offdiag"],
                                                         aa + epsilon);     // this has to be done in the loop as function backward_algorithm requires covector to be a vector (not a matrix)
  return draw_ssar1;
} // END rmvnorm1_precision_sampler
