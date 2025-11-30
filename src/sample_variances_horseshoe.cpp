// [[Rcpp::depends(RcppArmadillo)]]
#include <RcppArmadillo.h>

using namespace Rcpp;
using namespace arma;

// [[Rcpp::interfaces(cpp)]]
// [[Rcpp::export]]
Rcpp::List sample_variances_horseshoe(
    const arma::vec x,      // Input: current coefficient values
    arma::vec& theta,       // Local variances lambda^2
    double& zeta,           // Global variance tao^2
    arma::vec& nu,          // Auxiliary for lambda^2
    double& varpi          // Auxiliary for tao^2
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
  
  // return all results as a list
  return List::create(
    _["V_i"] = V_i_new,
    _["theta"] = theta,
    _["zeta"] = zeta,
    _["nu"] = nu,
    _["varpi"] = varpi
  );
}






