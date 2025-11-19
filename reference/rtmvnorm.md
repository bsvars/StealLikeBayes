# Sample Random Draws From the Truncated Multivariate Normal Using the Algorithm Proposed by Yifang Li and Sujit K. Ghosh (2015)

Samples random numbers from a truncated multivariate normal distribution
with parameters mean vector, covariance matrix, and linear inequality
constraints of the form \\l \leq Bx \leq u\\, where \\B\\ is a
constraint matrix and \\l\\ and \\u\\ are lower and upper bounds. The
function uses a Gibbs sampling algorithm to generate draws from the
constrained distribution.

The truncated multivariate normal is important for research in Bayesian
statistics, econometrics, and any field requiring parameter estimation
subject to inequality constraints. Common applications include censored
regression models, portfolio optimization with constraints, and prior
distributions with bounded support.

## Usage

``` r
rtmvnorm(mean, sigma, blc, lower, upper, init, burn = 10)
```

## Arguments

- mean:

  an \\n\times p\\ matrix of means. n is the number of draws to be
  sampled. p is the dimension of the draws. **C++**: an `arma::mat`
  object.

- sigma:

  a \\p\times p\\ covariance matrix for the draws. **C++**: an
  `arma::mat` object.

- blc:

  an \\m\times p\\ matrix of coefficients for linear inequality
  constraints. **C++**: an `arma::mat` object.

- lower:

  an \\n\times m\\ matrix of lower truncation bounds. **C++**: an
  `arma::mat` object.

- upper:

  an \\n\times m\\ matrix of upper truncation bounds. **C++**: an
  `arma::mat` object.

- init:

  an \\n\times p\\ matrix of initial values for the algorithm. **C++**:
  an `arma::mat` object.

- burn:

  number of iterations used as burn-in. Defaults is 10. **C++**: an
  `arma::uword` object.

## Value

An \\n\times p\\ matrix of draws from the specified truncated
multivariate normal. **C++**: an `arma::mat` object.

## Details

This function is based on C++ code from the R package tmvtnsim by Lu
(2025) and is using objects and commands from the armadillo library by
Sanderson & Curtin (2025) thanks to the RcppArmadillo package by
Eddelbuettel, Francois, Bates, Ni, & Sanderson (2025).

## References

Eddelbuettel D., Francois R., Bates D., Ni B., Sanderson C. (2025).
RcppArmadillo: 'Rcpp' Integration for the 'Armadillo' Templated Linear
Algebra Library. R package version 15.0.2-2.
\<doi:10.32614/CRAN.package.RcppArmadillo\>

Sanderson C., Curtin R. (2025). Armadillo: An Efficient Framework for
Numerical Linear Algebra. International Conference on Computer and
Automation Engineering, 303-307,
\<doi:10.1109/ICCAE64891.2025.10980539\>

Li, Y., Ghosh, S.K. Efficient sampling methods for truncated
multivariate normal and student-t distributions subject to linear
inequality constraints. J Stat Theory Pract 9, 712–732 (2015).
\<doi:10.1080/15598608.2014.996690\>

Lu K. (2025). tmvtnsim: Truncated Multivariate Normal and t Distribution
Simulation. R package version 0.1.4,
\<doi:10.32614/CRAN.package.tmvtnsim\>

## Author

Filip Reierson <filip.reierson@gmail.com>

## Examples

``` r
rtmvnorm(mean = matrix(c(0, 0), nrow = 1), sigma = diag(2), 
         blc = diag(2), lower = matrix(c(-Inf, -Inf), nrow = 1), 
         upper = matrix(c(1, 1), nrow = 1), init = matrix(c(0, 0), 
         nrow = 1), burn = 10)
#>           [,1]       [,2]
#> [1,] -1.048713 0.03810289
```
