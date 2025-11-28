
#include <RcppArmadillo.h>
#include "rgig1.h"

using namespace arma;
using namespace Rcpp;

/* This function was stolen by Shelly Xie from bayesianVARs package by Luis Gruber and Gregor Kastner
 *  on 19 November 2025 and then rewritten.
 */
// QR decomposition, where the diagonal elements of R are positive
// [[Rcpp::interfaces(cpp)]]
// [[Rcpp::export]]
arma::vec sample_variances_normal_gamma(
    const arma::vec x, 
    arma::vec& theta_tilde,
    double& zeta, 
    double& a , 
    const arma::vec a_vec,
    const double varrho0, 
    const double varrho1, 
    const bool hyper, 
    const double tol = 1e-6
){
  const int N = x.n_elem;
  vec V_i(N);
  IntegerVector ii = seq_len(N) - 1;
  uvec ind = as<uvec>(ii);
  const int n = ind.size();
  int gridlength = a_vec.size();
  arma::vec logprobs(gridlength); logprobs.fill(0);
  
  arma::uvec::iterator it;
  for(it = ind.begin(); it != ind.end(); ++it){
    theta_tilde(*it) = rgig1(a-0.5, x(*it)*x(*it), a/zeta);
    if(hyper){
      for(int i=0; i<gridlength; ++i){
        logprobs(i) += R::dgamma(theta_tilde(*it),a_vec(i), 2*zeta/a_vec(i), true); // scale!!!
      }
    }
  }
  if(tol>0){
    double th_sum = accu(theta_tilde);
    arma::vec theta = theta_tilde/th_sum;
    arma::uvec th_uvec= find(theta<tol);
    theta(th_uvec) = vec(th_uvec.size(), fill::value(tol));
    theta_tilde = theta * th_sum;
  }
  
  zeta = 1./randg(distr_param(varrho0 + a*n, 1./(varrho1 + 0.5*a*arma::accu(theta_tilde(ind)))));
  
  if(hyper){
    arma::vec w_tmp = exp(logprobs - logprobs.max());
    arma::vec w = w_tmp/sum(w_tmp);
    
    if(!w.is_finite()){
      ::Rf_error("sample_V_i_NG (NG_a = 'hyperprior'): non-finite weights");
    }else if(sum(w)==0){
      ::Rf_error("sample_V_i_NG (NG_a = 'hyperprior'): zero weights");
    }
    
    int k = w.size();
    arma::ivec iv(k);
    R::rmultinom(1, w.begin(), k, iv.begin());
    arma::uvec i = arma::find(iv == 1,1); // reports only the first value that meets the condition (by construction there is only one 1)
    a = a_vec(i(0));
  }
  
  
  V_i(ind) = theta_tilde(ind);
  return V_i;
}
