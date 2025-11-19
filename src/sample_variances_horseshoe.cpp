#include <RcppArmadillo.h>

using namespace Rcpp;
using namespace arma;

// [[Rcpp:interface(cpp)]]
// [[Rcpp::export]]
arma::vec sample_variances_horseshoe(
    const arma::vec x,      // Input: current coefficient values
    arma::vec& theta,       // Local variances lambda^2
    double& zeta,           // Global variance tau^2
    arma::vec& nu,          // Auxiliary for lambda^2
    double& varpi           // Auxiliary for tau^2
  ) {
  
  int n = x.n_elem;
  IntegerVector ii = seq_len(n) - 1;
  uvec ind = as<uvec>(ii);
  
  // initialize V_i 
  vec V_i_new(n);
  
  uvec::iterator it;
  for(it = ind.begin(); it != ind.end(); ++it){
    // Sample local variances: theta_j ~ Inverse-Gamma(1, rate)
    double rate_theta = 1.0/nu(*it) + (x(*it)*x(*it))/(2.0*zeta);
    theta(*it) = 1.0 / randg(distr_param(1.0, 1.0/rate_theta));
    
    // Sample auxiliary variables: nu_j ~ Inverse-Gamma(1, 1 + 1/theta_j)
    double rate_nu = 1.0 + 1.0/theta(*it);
    nu(*it) = 1.0 / randg(distr_param(1.0, 1.0/rate_nu));
  }
  
  // Sample global variance: zeta ~ Inverse-Gamma((n+1)/2, rate)
  double shape_zeta = (n + 1.0) / 2.0;
  double rate_zeta = 1.0/varpi + 0.5 * accu(square(x(ind))/theta(ind));
  zeta = 1.0 / randg(distr_param(shape_zeta, 1.0/rate_zeta));
  
  // Sample auxiliary variable: varpi ~ Inverse-Gamma(1, 1 + 1/zeta)
  double rate_varpi = 1.0 + 1.0/zeta;
  varpi = 1.0 / randg(distr_param(1.0, 1.0/rate_varpi));
  
  // Compute and return variances
  V_i_new(ind) = theta(ind) * zeta;
  
  return V_i_new;
}






