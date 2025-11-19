# Samples variances from the horseshoe prior using Gruber & Kastner (2024)

Performs one Gibbs sampling iteration for the horseshoe prior variance
parameters. The horseshoe prior Carvalho, Polson, Scott (2010) is a
continuous shrinkage prior for Bayesian variable selection with the
hierarchical structure: \$\$\beta_j \sim N(0, \lambda_j^2 \tau^2)\$\$
\$\$\lambda_j \sim C^+(0, 1)\$\$ \$\$\tau \sim C^+(0, 1)\$\$ where
\\C^+(0, 1)\\ denotes the half-Cauchy distribution, \\\lambda_j^2\\ are
the local shrinkage parameters (argument `theta`), and \\\tau^2\\ is the
global shrinkage parameter (argument `zeta`). The prior variance for
coefficient \\j\\ is \\V\_{i,j} = \lambda_j^2 \tau^2\\.

The half-Cauchy distributions are represented using auxiliary variables
\\\nu_j\\ and \\\varpi\\ to facilitate Gibbs sampling. This
implementation allows updating only a subset of coefficients specified
by the indices in argument `ind`.

## Usage

``` r
sample_variances_horseshoe(coefs, theta, zeta, nu, varpi)
```

## Arguments

- coefs:

  a \\p\\-vector with the current coefficient values \\\beta_j\\.
  **C++**: an `arma::vec` vector object.

- theta:

  a \\p\\-vector with the local variance parameters \\\lambda_j^2\\,
  updated by reference. **C++**: an `arma::vec` vector object.

- zeta:

  a numeric scalar with the global variance parameter \\\tau^2\\,
  updated by reference. **C++**: a `double` scalar.

- nu:

  a \\p\\-vector with auxiliary variables for the local shrinkage,
  updated by reference. **C++**: an `arma::vec` vector object.

- varpi:

  a numeric scalar with the auxiliary variable for the global shrinkage,
  updated by reference. **C++**: a `double` scalar.

## Value

a vector of variances' random draws. **C++**: an `arma::vec` vector
object.

## Details

This function is based on C++ code from the R package bayesianVARs by
Gruber & Kastner (2024) and is using objects and commands from the
armadillo library. Thanks to the RcppArmadillo package by Eddelbuettel,
Francois, Bates, Ni, & Sanderson (2025).

## References

Carvalho C.M., Polson N.G., Scott J.G. (2010). The horseshoe estimator
for sparse signals. Biometrika, 97(2), 465-480.
\<doi:10.1093/biomet/asq017\>

Eddelbuettel D., Francois R., Bates D., Ni B., Sanderson C. (2025).
RcppArmadillo: 'Rcpp' Integration for the 'Armadillo' Templated Linear
Algebra Library. R package version 15.0.2-2.
\<doi:10.32614/CRAN.package.RcppArmadillo\>

Gruber L.,Kastner G. (2024). bayesianVARs: MCMC Estimation of Bayesian
Vector Autoregressions. R package version 0.1.5,
\<doi:10.32614/CRAN.package.bayesianVARs\>

Makalic E., Schmidt D.F. (2016). A Simple Sampler for the Horseshoe
Estimator. IEEE Signal Processing Letters, 23(1), 179-182.
\<doi:10.1109/LSP.2015.2503725\>

Sanderson C., Curtin R. (2025). Armadillo: An Efficient Framework for
Numerical Linear Algebra. International Conference on Computer and
Automation Engineering, 303-307,
\<doi:10.1109/ICCAE64891.2025.10980539\>

## Author

Longcan Li <longcando@outlook.com>

## Examples

``` r
sample_variances_horseshoe( rep(0, 2), rep(0, 2), 1, rep(1, 2), 1)
#>           [,1]
#> [1,] 0.2170079
#> [2,] 0.3932400
```
