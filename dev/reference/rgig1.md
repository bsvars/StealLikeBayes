# Samples random draws from the generalized inverse Gaussian distribution

Samples random numbers from the generalized inverse Gaussian
distribution with density proportional to: \$\$f(x) = x^{\lambda - 1}
e^{-\frac{1}{2}(\chi/x + \psi x)},\$\$ with the parameters having to
satisfy the conditions: \$\$% \begin{array}{l} \lambda \> 0,\\ \psi \>
0, \chi \geq 0, \quad\mbox{or} \\ \lambda = 0,\\ \psi \> 0, \chi \> 0,
\quad\mbox{or} \\ \lambda \< 0,\\ \psi \geq 0, \chi \> 0. \end{array}
\$\$ The sampling algorithm proposed by Hörmann & Leydold (2013) is
implemented. If the arguments do not satisfy the restrictions a
std::logic_error exception is thrown in C++.

This method is useful for sampling variance coefficients that arise in
problems with their likelihood in the form of th inverse gamma
distribution and assuming a gamma prior.

## Usage

``` r
rgig1(lambda, chi, psi)
```

## Arguments

- lambda:

  a real scalar representing parameter \\\lambda\\. **C++**: a `double`
  object.

- chi:

  a real scalar representing parameter \\\chi\\. **C++**: a `double`
  object.

- psi:

  a real scalar representing parameter \\\psi\\. **C++**: a `double`
  object.

## Value

random draw from the GIG distribution. **C++**: a `double` object.

## Details

This function is based on C++ code from the R package shrinkTVP by
Knaus, Bitto-Nemling, Cadonna, Frühwirth-Schnatter (2021) and also uses
functionality of the GIGrvg package by Leydold & Hörmann (2023). It uses
random number generators from the armadillo library by Sanderson &
Curtin (2025) thanks to the RcppArmadillo package by Eddelbuettel,
Francois, Bates, Ni, & Sanderson (2025)

## References

Eddelbuettel D., Francois R., Bates D., Ni B., Sanderson C. (2025).
RcppArmadillo: 'Rcpp' Integration for the 'Armadillo' Templated Linear
Algebra Library. R package version 15.0.2-2.
\<doi:10.32614/CRAN.package.RcppArmadillo\>

Hörmann W., Leydold J. (2013). Generating generalized inverse Gaussian
random variates, Statistics and Computing 24, 547–557,
\<doi:10.1007/s11222-013-9387-3\>.

Leydold J., Hörmann W. (2023). GIGrvg: Random Variate Generator for the
GIG Distribution, R package version 0.8,
\<doi:10.32614/CRAN.package.GIGrvg\>.

Knaus, P., Bitto-Nemling, A., Cadonna, A., & Frühwirth-Schnatter, S.
(2021). Shrinkage in the Time-Varying Parameter Model Framework Using
the R Package shrinkTVP. Journal of Statistical Software, 100(13), 1–32.
\<doi:10.18637/jss.v100.i13\>.

Sanderson C., Curtin R. (2025). Armadillo: An Efficient Framework for
Numerical Linear Algebra. International Conference on Computer and
Automation Engineering, 303-307,
\<doi:10.1109/ICCAE64891.2025.10980539\>

## Author

Tomasz Woźniak <wozniak.tom@pm.me>

## Examples

``` r
rgig1(1, 1, 1)
#> [1] 0.2440235
```
