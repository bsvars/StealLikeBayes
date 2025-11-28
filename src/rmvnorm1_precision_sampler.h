#ifndef _RNORM1_PRECISION_SAMPLER_
#define _RNORM1_PRECISION_SAMPLER_

#include <RcppArmadillo.h>

Rcpp::List cholesky_tridiagonal(
    const arma::vec&    omega_diag,
    const double&       omega_offdiag
);


arma::vec forward_algorithm(
    const arma::vec& chol_diag,
    const arma::vec& chol_offdiag,
    const arma::vec& covector
);


arma::vec backward_algorithm(
    const arma::vec& chol_diag,
    const arma::vec& chol_offdiag,
    const arma::vec& htmp
);


arma::vec rmvnorm1_precision_sampler(
    const arma::vec&     location,
    const arma::vec&     precision_diag,
    const double&        precision_offdiag
);

#endif