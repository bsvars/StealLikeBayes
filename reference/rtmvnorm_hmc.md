# Generate Truncated Multivariate Normal Samples via Hamiltonian Monte Carlo

Generate \\p\\-dimensional truncated multivariate normal samples that
satisfy an inequality constraint \$\$F \times x + g \ge 0,\$\$ where
\\x\\ is a column vector of the generated sample. The sampler is an
exact Hamiltonian Monte Carlo (HMC) sampler as described in Pakman and
Paninski (2014).

## Usage

``` r
rtmvnorm_hmc(n, mean, cov, initial, Fmat, g, burn)
```

## Arguments

- n:

  a positive integer with the number of samples. **C++**: an `int`
  object.

- mean:

  a \\p\\-dimensional mean vector. **C++**: an `Eigen::VectorXd` object.

- cov:

  a \\p \times p\\ covariance matrix of the normal distribution.
  **C++**: an `Eigen::MatrixXd` object.

- initial:

  a \\p\\-dimensional initial value vector for the Markov chain.
  **C++**: an `Eigen::VectorXd` object.

- Fmat:

  an \\m \times p\\ constraint matrix \\F\\ defining linear
  inequalities, where \\m\\ is the number of constraints. **C++**: an
  `Eigen::MatrixXd` object.

- g:

  an \\m\\-dimensional constraint vector defining linear inequalities.
  **C++**: an `Eigen::VectorXd` object.

- burn:

  a non-negative integer with the number of burn-in iterations before
  collecting samples. **C++**: an `int` object.

## Value

An \\n \times p\\ matrix with each row corresponding to a sample.
**C++**: an `Eigen::MatrixXd` object.

## Details

The function generates samples from a truncated multivariate normal
distribution with mean `mean` and covariance `cov`, subject to linear
constraints defined by `Fmat` and `g`.

The user should supply an initial value that strictly satisfies the
inequality constraints, although the generated samples only satisfy them
weakly.

No check for symmetry is performed on the covariance matrix.

It is advisable to use a small burn-in period (e.g., 10) to allow the
Markov chain to reach stationarity.

This function is a wrapper around a C++ implementation adapted from the
'tnorm' R package by Kenyon Ng.

## References

Pakman, A. and Paninski, L. (2014). Exact Hamiltonian Monte Carlo for
Truncated Multivariate Gaussians. Journal of Computational and Graphical
Statistics, 23(2), 518–542. \<doi:10.1080/10618600.2013.788448\>

Ng, K. (2024). tnorm: Generate Multivariate Truncated Normal Samples. R
package version 0.0.1. \<https://github.com/weiyaw/tnorm\>

Bates, D. and Eddelbuettel, D. (2013). Fast and Elegant Numerical Linear
Algebra Using the RcppEigen Package. Journal of Statistical Software,
52(5), 1–24. \<doi:10.18637/jss.v052.i05\>

## Examples

``` r
rtmvnorm_hmc(1, c(0, 0), diag(2), c(0, 2), diag(2), c(1, -1), 1)
#>           [,1]     [,2]
#> [1,] 0.9463479 1.316826
```
