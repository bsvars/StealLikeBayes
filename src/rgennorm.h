#ifndef _RGENNORM_
#define _RGENNORM_

#include <RcppArmadillo.h>

arma::mat orthogonal_complement_matrix_TW (const arma::mat& x);


arma::rowvec normalisation_wz2003_s (
    const arma::mat& B,                   // NxN
    const arma::mat& B_hat_inv,           // NxN
    const arma::mat& Sigma_inv,           // NxN
    const arma::mat& diag_signs           // KxN
);


arma::cube normalisation_wz2003 (
    arma::cube&       posterior_B,            // NxNxS
    const arma::mat&  B_hat              // NxN
);


arma::cube rgennorm (
    const int                     n,
    arma::mat&                    X,        // NxN
    const arma::cube&             S_inv,    // NxNxN
    const int&                    nu,       // positive scalar
    const arma::field<arma::mat>& V,        // restrictions
    const bool                    normalise = true
);

#endif