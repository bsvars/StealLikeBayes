
#ifndef _RGIG1_H_
#define _RGIG1_H_

#include <RcppArmadillo.h>

double univar_rgig_newapproach1 (
    double lambda, 
    double lambda_old, 
    double omega, 
    double alpha
);

double rgig1(
    double lambda,
    double chi,
    double psi
);

#endif