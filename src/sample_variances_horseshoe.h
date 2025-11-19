#ifndef Sample_Horseshoe_Variances_H
#define Sample_Horseshoe_Variances_H


#include <RcppArmadillo.h>

arma::vec sample_variances_horseshoe(
                        const arma::vec x,      // Input: current coefficient values
                        arma::vec& theta,       // Local variances lambda^2
                        double& zeta,           // Global variance tao^2
                        arma::vec& nu,          // Auxiliary for lambda^2
                        double& varpi          // Auxiliary for tao^2
                       );       

#endif
                        