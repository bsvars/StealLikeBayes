
#ifndef SAMPLE_VARIANCES_NORMAL_GAMMA
#define SAMPLE_VARIANCES_NORMAL_GAMMA

#include <RcppArmadillo.h>

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
);

#endif 
