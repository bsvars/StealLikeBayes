
#include <RcppArmadillo.h>

using namespace Rcpp;
using namespace arma;


/* This function was stolen by Tomasz from package bsvars by Tomasz Woźniak
 * on 18 November 2025 and then rewritten.
 */
// [[Rcpp::interfaces(cpp)]]
// [[Rcpp::export]]
arma::mat orthogonal_complement_matrix_TW (const arma::mat& x) {
  // # x is a mxn matrix and m>n
  // # the function returns a mx(m-n) matrix, out, that is an orthogonal complement of x, i.e.:
  // # t(x)%*%out = 0 and det(cbind(x,out))!=0
  int n_nrow     = x.n_rows;
  int n_ncol     = x.n_cols;
  mat Q;
  mat R;
  qr(Q, R, x);
  mat ocm = Q.tail_cols(n_nrow-n_ncol);
  return ocm;
} // END orthogonal_complement_matrix_TW




/* This function was stolen by Tomasz from package bsvars by Tomasz Woźniak
 * on 18 November 2025 and then rewritten.
 */
// [[Rcpp::interfaces(cpp)]]
// [[Rcpp::export]]
arma::rowvec normalisation_wz2003_s (
    const arma::mat& B,                   // NxN
    const arma::mat& B_hat_inv,           // NxN
    const arma::mat& Sigma_inv,           // NxN
    const arma::mat& diag_signs           // KxN
) {
  // returns a rowvec of signs
  const int N         = B.n_rows;
  const int K         = pow(2,N);
  vec       distance(K);
  
  for (int k=0; k<K; k++) {
    mat   B_tmp_inv   = inv(diagmat(diag_signs.row(k)) * B);
    mat   dist_tmp    = trans(B_tmp_inv - B_hat_inv);
    for (int n=0; n<N; n++) {
      distance(k)     += as_scalar(dist_tmp.row(n) * Sigma_inv * trans(dist_tmp.row(n)));
    } // END n loop
  } // END k loop
  
  rowvec out = diag_signs.row(distance.index_min());
  return out;
} // END normalisation_wz2003_s


/* This function was stolen by Tomasz from package bsvars by Tomasz Woźniak
 * on 18 November 2025 and then rewritten.
 */
// [[Rcpp::interfaces(cpp)]]
// [[Rcpp::export]]
arma::cube normalisation_wz2003 (
    arma::cube&       posterior_B,            // NxNxS
    const arma::mat&  B_hat              // NxN
) {
  // changes posterior_B by reference filling it with normalised values
  const int   N       = posterior_B.n_rows;
  const int   K       = pow(2, N);
  const int   S       = posterior_B.n_slices;
  
  mat B_hat_inv       = inv(B_hat);
  mat Sigma_inv       = B_hat.t() * B_hat;
  
  // create matrix diag_signs whose rows contain all sign combinations
  mat diag_signs(K, N);
  vec omo             = as<vec>(NumericVector::create(-1,1));
  for (int n=0; n<N; n++) {
    vec os(pow(2, n), fill::ones);
    vec oos(pow(2, N-1-n), fill::ones);
    diag_signs.col(n) = kron(os, kron(omo, oos));
  }
  
  // normalisation
  for (int s=0; s<S; s++) {
    rowvec sss            = normalisation_wz2003_s(posterior_B.slice(s), B_hat_inv, Sigma_inv, diag_signs);
    mat B_norm            = diagmat(sss) * posterior_B.slice(s);
    posterior_B.slice(s)   = B_norm;
  }
  
  return posterior_B;
} // END normalisation_wz2003



/* This function was stolen by Tomasz from package bsvars by Tomasz Woźniak
 * on 18 November 2025 and then rewritten.
 */
// [[Rcpp::interfaces(cpp)]]
// [[Rcpp::export]]
arma::cube rgennorm (
    const int                     n,
    arma::mat&                    X,        // NxN
    const arma::cube&             S_inv,    // NxNxN
    const int&                    nu,       // positive scalar
    const arma::field<arma::mat>& V,        // restrictions
    const bool                    normalise = true
) {
  
  const int N               = S_inv.n_rows;
  double    post_nu         = nu - N;
  mat       post_S_inv(N, N);
  field<mat> Un(N);
  cube      out(N, N, n);
  
  
  for (int j=0; j<n; j++) {
    for (int i=0; i<N; i++) {
      if (j == 0) {
        post_S_inv              = V(i) * S_inv.slice(i) * V(i).t();
        post_S_inv              = 0.5 * ( post_S_inv + post_S_inv.t() );
        Un(i)                   = chol(post_nu * inv_sympd(post_S_inv));
      }
      
      mat B_tmp               = X;
      B_tmp.shed_row(i);
      rowvec w                = trans(orthogonal_complement_matrix_TW(B_tmp.t()));
      vec w1_tmp              = trans(w * V(i).t() * Un(i).t());
      double w1w1_tmp         = as_scalar(sum(pow(w1_tmp, 2)));
      mat w1                  = w1_tmp.t() / sqrt(w1w1_tmp);
      mat Wn;
      const int rn            = V(i).n_rows;
      if (rn == 1) {
        Wn                    = w1;
      } else {
        Wn                    = join_rows(w1.t(), orthogonal_complement_matrix_TW(w1.t()));
      }
      
      vec   alpha(rn);
      vec   u(post_nu + 1, fill::randn);
      u                      *= pow(post_nu, -0.5);
      alpha(0)                = pow(as_scalar(sum(u % u)), 0.5);
      if (R::runif(0, 1) < 0.5) {
        alpha(0)       *= -1;
      }
      if (rn>1){
        vec nn(rn - 1, fill::randn);
        nn                   *= pow(post_nu, -0.5);
        alpha.rows(1,rn-1)    = nn;
      }
      rowvec b0n              = alpha.t() * Wn * Un(i);
      X.row(i)                = b0n * V(i);
      
    } // END i loop
    
    out.slice(j)              = X;
    
  } // END j loop
  
  if (normalise) {
    mat B_hat   = diagmat(diagvec(sign(X))) * X;
    out         = normalisation_wz2003 (out, B_hat);
  }
  
  return out;
} // END rgennorm

