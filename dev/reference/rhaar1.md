# Sample random matrices from Haar distribution

This function samples random orthogonal matrices from the Haar
distribution, that is, the uniform distribution over the space of
orthogonal matrices.

## Usage

``` r
rhaar1(n)
```

## Arguments

- n:

  a positive integer scalar specifying the dimension of the orthogonal
  matrix. **C++**: an `int` scalar.

## Value

An \\n\times n\\ matrix with a random draw of the orthogonal matrix from
the Haar distribution. **C++**: an `arma::mat` object.

## Details

This function is based on C++ code from the R package bsvarSIGNs by Wang
X., Woźniak T. (2025a,2025b) and is using objects and commands from the
armadillo library by Sanderson & Curtin (2025) thanks to the
RcppArmadillo package by Eddelbuettel, Francois, Bates, Ni, & Sanderson
(2025)

## References

Eddelbuettel D., Francois R., Bates D., Ni B., Sanderson C. (2025).
RcppArmadillo: 'Rcpp' Integration for the 'Armadillo' Templated Linear
Algebra Library. R package version 15.0.2-2.
\<doi:10.32614/CRAN.package.RcppArmadillo\>

Sanderson C., Curtin R. (2025). Armadillo: An Efficient Framework for
Numerical Linear Algebra. International Conference on Computer and
Automation Engineering, 303-307,
\<doi:10.1109/ICCAE64891.2025.10980539\>

Stewart, G. W. (1980). The efficient generation of random orthogonal
matrices with an application to condition estimators. SIAM Journal on
Numerical Analysis, 17(3), 403-409. \<doi:10.1137/0717034\>

Wang X., Woźniak T. (2025a). bsvarSIGNs: Bayesian SVARs with Sign, Zero,
and Narrative Restrictions. R package version 2.0,
\<doi:0.32614/CRAN.package.bsvarSIGNs\>.

Wang X., Woźniak T. (2025b). Bayesian Analyses of Structural Vector
Autoregressions with Sign, Zero, and Narrative Restrictions Using the R
Package bsvarSIGNs, \<doi:10.48550/arXiv.2501.16711\>.

## Author

Xiaolei Wang <adamwang15@gmail.com>

## Examples

``` r
rhaar1(3)
#>             [,1]        [,2]        [,3]
#> [1,] -0.18012866 -0.97997952 -0.08481633
#> [2,] -0.06946447 -0.07333823  0.99488501
#> [3,] -0.98118722  0.18509903 -0.05486344
```
