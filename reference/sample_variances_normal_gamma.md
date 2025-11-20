# Samples variances of the Normal-Gamma prior distribution by Brown & Griffin (2010).

This function samples variances from a Normal-Gamma prior distribution.
The prior distribution has a hierarchical structure where each element
\\x_i\\ of a \\k\\-vector \\X\\ follows: \$\$x_i \sim N(0,\vartheta_i
\zeta_j), \vartheta_i \sim G(a_j, a_j / 2) \text{, and } \zeta_j^{-1}
\sim G(b,c)\$\$ for \\i=j=1,\dots,k\\. The hyperparameter \\a_j\\
follows an i.i.d. discrete hyperprior with \\Pr(a_j = \tilde{a}\_r) =
p_r\\, where \\\tilde{a} = (\tilde{a}\_1, \dots, \tilde{a}\_R)'\\ is the
vector of strictly positive support points. See Brown & Griffin (2010)
and Gruber & Kastner (2025) for further details.

## Usage

``` r
sample_variances_normal_gamma(
  x,
  theta_tilde,
  zeta,
  a,
  a_vec,
  varrho0,
  varrho1,
  hyper,
  tol = 1e-06
)
```

## Arguments

- x:

  A starting values vector of the variances. **C++**: an `arma::vec`
  vector object.

- theta_tilde:

  A starting values vector of \\\vartheta_i\\. **C++**:an `arma::vec`
  vector object.

- zeta:

  A starting value of \\\zeta_j\\. **C++**: an `double` object.

- a:

  Prior shape parameter of the Gamma distribution for \\\vartheta_i\\.
  **C++**: an `double` object.

- a_vec:

  Multinomial grid for updating shape parameter of the Gamma
  distribution.**C++**: an `arma::vec` vector object.

- varrho0:

  Prior shape parameter of the Gamma distribution for \\\zeta_j\\.
  **C++**: an `double` object.

- varrho1:

  Prior scale parameter of the Gamma distribution for \\\zeta_j\\.
  **C++**: an `double` object.

- hyper:

  A logical value. TRUE or FALSE. **C++**: an `bool` object

- tol:

  The numerical tolerance, default is '1e-06'. **C++**: an `double`
  object.

## Value

A vector of variances of the Normal-Gamma prior distribution. **C++**:
an `arma::vec` object.

## Details

This function is based on C++ code from the R package bayesianVARs by
Gruber (2025) and is using objects and commands from the armadillo
library by Sanderson & Curtin (2025) thanks to the RcppArmadillo package
by Eddelbuettel, Francois, Bates, Ni, & Sanderson (2025).

## References

Gruber, L. (2025). bayesianVARs: MCMC Estimation of Bayesian
Vectorautoregressions. R package version 0.1.5.9000, \<doi:
10.32614/CRAN.package.bayesianVARs\>.

Gruber, L., & Kastner, G. (2025). Forecasting macroeconomic data with
Bayesian VARs: Sparse or dense? It depends!. International Journal of
Forecasting, 41(4), 1589-1619,
\<doi:org/10.1016/j.ijforecast.2025.02.001\>.

Philip J. Brown., Jim E. Griffin (2010). Inference with normal-gamma
prior distributions in regression problems. Bayesian Analysis, 5(1),
171-188, \<doi:org/10.1214/10-BA507\>.

Eddelbuettel D., Francois R., Bates D., Ni B., Sanderson C. (2025).
RcppArmadillo: 'Rcpp' Integration for the 'Armadillo' Templated Linear
Algebra Library. R package version 15.0.2-2.
\<doi:10.32614/CRAN.package.RcppArmadillo\>

Sanderson C., Curtin R. (2025). Armadillo: An Efficient Framework for
Numerical Linear Algebra. International Conference on Computer and
Automation Engineering, 303-307,
\<doi:10.1109/ICCAE64891.2025.10980539\>

## Author

Jianying Shelly Xie <shellyyinggxie@gmail.com>

## Examples

``` r
sample_variances_normal_gamma(rep(0,2), rep(1,2), 1, 1, rep(1,2), 1, 1, TRUE, 1e-6)
#>          [,1]
#> [1,] 2.129573
#> [2,] 4.068682
```
