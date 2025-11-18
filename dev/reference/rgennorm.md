# Samples random draws from a generalised normal distribution using the Gibbs sampler by Waggoner & Zha (2003a)

Samples random numbers from a generalised normal distribution for a
restricted \\N\times N\\ full rank matrix \\X\\. The matrix is drawn
row-by-row from their full conditional distributions using the Gibbs
sampler by Waggoner & Zha (2003a). The density is proportional to
\$\$det(X)^{\nu -
N}\exp(-\frac{1}{2}\sum\_{n=1}^{N}x_nV_nS_nV_n'x_n')\$\$ specified by
the \\N\times N\\ scale matrices \\S_n\\, a positive scalar-valued shape
parameter \\\nu\\, and \\r_n\times N\\ selection matrices \\V_n\\
defining the restrictions. Zero restrictions may be imposed on th \\X\\
matrix row-by-row as \$\$X\_{n.} = x_nV_n\$\$ where \\1\times r_n\\
vectors \\x_n\\ collect the unrestricted elements of \\X\_{n.}\\ and the
matrices \\V_n\\ place them in appropriate spots of the \\1\times N\\
row \\X\_{n.}\\. The output may be normalised using the method by
Waggoner & Zha (2003b) ensuring positive diagonal elements of the output
matrices.

This method is useful for sampling the structural matrix of the
structural vector autoregressive models identified by exclusion
restrictions, sign and exclusion restrictions, heteroskedasticity, and
instrumental variables.

## Usage

``` r
rgennorm(n, X, S, nu, V, normalise = TRUE)
```

## Arguments

- n:

  a positive integer with the number of draws to be sampled. **C++**: a
  `int` object.

- X:

  an \\N\times N\\ structural matrix with the starting values to
  initiate the Gibbs sampler. **C++**: an `arma::mat` matrix object.

- S:

  an \\N\times N\times N\\ array with \\N\times N\\ row-specific
  precision matrices \\S_n\\. **C++**: an `arma::cube` object.

- nu:

  a positive integer number with the shape parameter \\nu\\. **C++**: an
  `arma::int` object.

- V:

  a list with \\N\\ elements each including \\r_n\times N\\ matrices
  \\V_n\\. **C++**: an `arma::field<arma::mat>` object.

- normalise:

  a logical value of whether the output should be normalised following
  the method by Waggoner & Zha (2003b) ensuring positive signs of the
  diagonal elements of the sampled matrices. **C++**: an `bool` object.

## Value

an \\N\times N\times n\\-array with random draws from the generalised
normal distribution. **C++**: an `arma::cube` object.

## Details

This function is based on C++ code from the R package bsvars by Woźniak
(2024,2025) and is using objects and commands from the armadillo library
by Sanderson & Curtin (2025) thanks to the RcppArmadillo package by
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

Waggoner D.F., Zha T., (2003a). A Gibbs Sampler for Structural Vector
Autoregressions. Journal of Economic Dynamics and Control, 28(2),
349-366, \<doi:10.1016/S0165-1889(02)00168-9\>.

Waggoner, D.F., Zha, T. (2003b). Likelihood Preserving Normalization in
Multiple Equation Models. Journal of Econometrics, 114(2), 329-347.
\<doi:10.1016/S0304-4076(03)00087-3\>

Woźniak T. (2024). bsvars: Bayesian Estimation of Structural Vector
Autoregressive Models, R package version 3.2,
\<doi:10.32614/CRAN.package.bsvars\>.

Woźniak T. (2025). Fast and Efficient Bayesian Analysis of Structural
Vector Autoregressions Using the R Package bsvars. University of
Melbourne Working Paper, 1–25. \<doi:10.48550/arXiv.2410.15090\>.

## Author

Tomasz Woźniak <wozniak.tom@pm.me>

## Examples

``` r
rgennorm(1, diag(2), array(diag(2), c(2,2,2)), 3, list(diag(2), matrix(1,1,2)))
#> , , 1
#> 
#>           [,1]       [,2]
#> [1,] 1.1593962 -3.2777784
#> [2,] 0.9654515  0.9654515
#> 
```
