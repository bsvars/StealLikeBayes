# Sample from the inverted gamma-2 distribution

Samples independent random numbers from the inverted gamma-2
distribution, denoted by \\IG2(s, \nu)\\, with density \$\$f(x) =
\frac{(s/2)^{\nu/2}}{\Gamma(\nu/2)}
x^{-(\nu+2)/2}\exp\left(-\frac{s}{2x}\right), \quad x \> 0.\$\$ The
draws are generated as \\s/Z\\, where \\Z\\ follows a chi-squared
distribution with \\\nu\\ degrees of freedom.

This distribution is commonly used for variance parameters in Bayesian
models.

## Usage

``` r
rig2(n, s, nu)
```

## Arguments

- n:

  a positive integer giving the number of draws. **C++**: an `int`
  object.

- s:

  a positive real scalar giving the scale parameter. **C++**: a `double`
  object.

- nu:

  a positive real scalar giving the degrees-of-freedom parameter.
  **C++**: a `double` object.

## Value

A numeric vector of length `n` containing independent draws from the
inverted gamma-2 distribution. **C++**: an `arma::vec` object.

## Details

This function is based on C++ code from the GPL-3 R package bsvars by
Woźniak (2024, 2025). It uses random-number generators from the
armadillo library by Sanderson & Curtin (2025), made available to R
through the RcppArmadillo package by Eddelbuettel et al. (2025).

## References

Bauwens L., Lubrano M., Richard J.-F. (1999). *Bayesian Inference in
Dynamic Econometric Models*. Oxford University Press.

Eddelbuettel D., François R., Bates D., Ni B., Sanderson C. (2025).
RcppArmadillo: 'Rcpp' Integration for the 'Armadillo' Templated Linear
Algebra Library. R package version 15.0.2-2.
[doi:10.32614/CRAN.package.RcppArmadillo](https://doi.org/10.32614/CRAN.package.RcppArmadillo)

Sanderson C., Curtin R. (2025). Armadillo: An Efficient Framework for
Numerical Linear Algebra. International Conference on Computer and
Automation Engineering, 303–307.
[doi:10.1109/ICCAE64891.2025.10980539](https://doi.org/10.1109/ICCAE64891.2025.10980539)

Woźniak T. (2024). bsvars: Bayesian Estimation of Structural Vector
Autoregressive Models, R package version 3.2.
[doi:10.32614/CRAN.package.bsvars](https://doi.org/10.32614/CRAN.package.bsvars)

Woźniak T. (2025). Fast and Efficient Bayesian Analysis of Structural
Vector Autoregressions Using the R Package bsvars. University of
Melbourne Working Paper, 1–25.
[doi:10.48550/arXiv.2410.15090](https://doi.org/10.48550/arXiv.2410.15090)

## Author

Tomasz Woźniak <wozniak.tom@pm.me>

## Examples

``` r
rig2(5, 1, 10)
#>            [,1]
#> [1,] 0.06306287
#> [2,] 0.14042387
#> [3,] 0.06977329
#> [4,] 0.09247198
#> [5,] 0.12065217
```
