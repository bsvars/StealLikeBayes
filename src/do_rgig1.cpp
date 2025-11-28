#include <Rcpp.h>
#include <math.h>
#include <float.h>

using namespace Rcpp;

double univar_rgig_newapproach1 (double lambda, double lambda_old, double omega, double alpha){

  double A[3], Atot;
  double k0;
  double k1, k2;

  double xm;
  double x0;
  double a;

  double U, V, X;
  double hx;

  int count = 0;
  double res;

  if (lambda >= 1. || omega >1.)
    throw ("invalid parameters");




  xm = omega / (std::sqrt((1.-lambda)*(1.-lambda) + omega*omega)+(1.-lambda));


  x0 = omega/(1.-lambda);


  k0 = std::exp((lambda-1.)*std::log(xm) - 0.5*omega*(xm + 1./xm));
  A[0] = k0 * x0;


  if (x0 >= 2./omega) {
    k1 = 0.;
    A[1] = 0.;
    k2 = pow(x0, lambda-1.);
    A[2] = k2 * 2. * std::exp(-omega*x0/2.)/omega;
  }

  else {

    k1 = std::exp(-omega);
    A[1] = (lambda == 0.)
      ? k1 * std::log(2./(omega*omega))
        : k1 / lambda * ( std::pow(2./omega, lambda) - std::pow(x0, lambda) );


    k2 = std::pow(2/omega, lambda-1.);
    A[2] = k2 * 2 * std::exp(-1.)/omega;
  }


  Atot = A[0] + A[1] + A[2];

  do {
    ++count;


    V = Atot * R::runif(0, 1);

    do {


      if (V <= A[0]) {
        X = x0 * V / A[0];
        hx = k0;
        break;
      }


      V -= A[0];
      if (V <= A[1]) {
        if (lambda == 0.) {
          X = omega * std::exp(std::exp(omega)*V);
          hx = k1 / X;
        }
        else {
          X = std::pow(std::pow(x0, lambda) + (lambda / k1 * V), 1./lambda);
          hx = k1 * std::pow(X, lambda-1.);
        }
        break;
      }


      V -= A[1];
      a = (x0 > 2./omega) ? x0 : 2./omega;
      X = -2./omega * std::log(std::exp(-omega/2. * a) - omega/(2.*k2) * V);
      hx = k2 * std::exp(-omega/2. * X);
      break;

    } while(0);


    U = R::runif(0, 1) * hx;

    if (std::log(U) <= (lambda-1.) * std::log(X) - omega/2. * (X+1./X)) {

      res = (lambda_old < 0.) ? (alpha / X) : (alpha * X);
      break;
    }
  } while(1);

  return res;
}


double do_rgig1(double lambda,
                double chi,
                double psi) {

  if (chi == 0){
    chi = DBL_MIN;
  }

  if ( !(R_FINITE(lambda) && R_FINITE(chi) && R_FINITE(psi)) ||
       (chi <  0. || psi < 0)      ||
       (chi == 0. && lambda <= 0.) ||
       (psi == 0. && lambda >= 0.) ) {

    throw std::bad_function_call();
  }

  double res;

  // circumvent GIGrvg in these cases
  if ((chi < (11 * DBL_EPSILON)) & (lambda != 0)) {
    /* special cases which are basically Gamma and Inverse Gamma distribution */
    if (lambda > 0.0) {
      res = R::rgamma(lambda, 2.0/psi);
    }
    else {
      res = 1.0/R::rgamma(-lambda, 2.0/chi); // fixed
    }
  }

  else if ((psi < (11 * DBL_EPSILON)) & (lambda != 0)) {
    /* special cases which are basically Gamma and Inverse Gamma distribution */
    if (lambda > 0.0) {
      res = R::rgamma(lambda, 2.0/psi);  // fixed
    }
    else {
      res = 1.0/R::rgamma(-lambda, 2.0/chi); // fixed
    }

  } else if ((lambda == 0) && (sqrt(psi*chi) > 0) && (sqrt(psi*chi) < 1)) {
    res = univar_rgig_newapproach1(lambda, lambda, sqrt(psi*chi), sqrt(chi/psi));
  } else {
    SEXP (*fun)(int, double, double, double) = NULL;
    if (!fun) fun = (SEXP(*)(int, double, double, double)) R_GetCCallable("GIGrvg", "do_rgig");

    res = as<double>(fun(1, lambda, chi, psi));
  }

  return res;
}

