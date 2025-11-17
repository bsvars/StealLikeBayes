# Samples random draws from a multivariate normal distribution using the precision sampler by Chan & Jeliazkov (2009)

Samples random numbers from an \\N\\-variate normal distribution
specified by the \\N\times N\\ precision matrix \\P\\ and \\N\times 1\\
location vector \\L\\ as per: \$\$N(P^{-1}L, P^{-1})\$\$ where the
precision matrix \\P\\ is bi-diagonal with the diagonal elements given
in the vector argument `precision_diag` and the off-diagonal element is
given in the scalar argument `precision_offdiag`, and the location
vector \\L\\ is provided in the vector argument `location`.

This method is useful for the simulation smoother of the linear Gaussian
state-space models with the state variable specified by the
autoregressive dynamics with one lag, AR(1). See Woźniak (2021) for more
details.

## Usage

``` r
rnorm1_precision_sampler(location, precision_diag, precision_offdiag)
```

## Arguments

- location:

  an \\N\\-vector with the location parameter \\L\\. **C++**: an
  `arma:vec` vector object.

- precision_diag:

  an \\N\\-vector with the diagonal elements of the precision matrix
  \\P\\. **C++**: an `arma:vec` vector object.

- precision_offdiag:

  a numeric scalar with the off-diagonal element of the precision matrix
  \\P\\. **C++**: a `double` scalar.

## Value

an \\N\\-vector with random draws from the multivariate normal
distribution. **C++**: an `arma:vec` vector object.

## Details

This function is based on C++ code from the R package stochvol by
Hosszejni & Kastner (2025) and Kastner G. (2016) and is using objects
and commands from the armadillo library by Sanderson & Curtin (2025)
thanks to the RcppArmadillo package by Eddelbuettel, Francois, Bates,
Ni, & Sanderson (2025)

## References

Chan J.C.C., Jeliazkov I. (2009). Efficient simulation and integrated
likelihood estimation in state space models. International Journal of
Mathematical Modelling and Numerical Optimisation, 1(1/2),
\<doi:10.1504/IJMMNO.2009.030090\>.

Eddelbuettel D., Francois R., Bates D., Ni B., Sanderson C. (2025).
RcppArmadillo: 'Rcpp' Integration for the 'Armadillo' Templated Linear
Algebra Library. R package version 15.0.2-2.
\<doi:10.32614/CRAN.package.RcppArmadillo\>

Hosszejni D., Kastner G. (2025). stochvol: Efficient Bayesian Inference
for Stochastic Volatility (SV) Models. R package version 3.2.8,
\<doi:10.32614/CRAN.package.stochvol\>

Kastner G. (2016). Dealing with Stochastic Volatility in Time Series
Using the R Package stochvol. Journal of Statistical Software, 69(5),
1–30. \<doi:10.18637/jss.v069.i05\>.

Sanderson C., Curtin R. (2025). Armadillo: An Efficient Framework for
Numerical Linear Algebra. International Conference on Computer and
Automation Engineering, 303-307,
\<doi:10.1109/ICCAE64891.2025.10980539\>

Woźniak T. (2021). Simulation Smoother using RcppArmadillo, RcppGallery
<https://gallery.rcpp.org/articles/simulation-smoother-using-rcpparmadillo/>

## Author

Tomasz Woźniak <wozniak.tom@pm.me>

## Examples

``` r
rnorm1_precision_sampler(rep(0, 100), rep(1, 100), -0.5)
#>              [,1]
#>   [1,] -0.8980005
#>   [2,] -2.4499267
#>   [3,] -1.7482649
#>   [4,] -1.9654423
#>   [5,] -2.4326542
#>   [6,] -2.8886978
#>   [7,] -0.5267503
#>   [8,] -1.7351475
#>   [9,] -3.2676642
#>  [10,] -3.8332336
#>  [11,] -4.0417223
#>  [12,] -4.2982875
#>  [13,] -4.6138733
#>  [14,] -4.3687768
#>  [15,] -2.8160693
#>  [16,] -2.7924673
#>  [17,] -2.0128842
#>  [18,] -2.0296672
#>  [19,] -2.5759578
#>  [20,] -1.0042948
#>  [21,] -2.5021349
#>  [22,] -3.5295344
#>  [23,] -2.5176816
#>  [24,] -1.6871978
#>  [25,] -1.8207532
#>  [26,] -3.5155620
#>  [27,] -5.2114004
#>  [28,] -3.3770605
#>  [29,] -4.8858750
#>  [30,] -3.8669254
#>  [31,] -0.1581464
#>  [32,] -0.2974709
#>  [33,] -0.5982883
#>  [34,]  0.2374214
#>  [35,]  1.0002593
#>  [36,] -1.8692254
#>  [37,] -1.9025862
#>  [38,] -3.7031645
#>  [39,] -5.7787831
#>  [40,] -5.4880538
#>  [41,] -5.9137287
#>  [42,] -6.5700611
#>  [43,] -6.6059165
#>  [44,] -6.1790311
#>  [45,] -3.5568563
#>  [46,] -1.7801166
#>  [47,] -1.9988806
#>  [48,] -1.9917446
#>  [49,] -4.2128700
#>  [50,] -2.9975748
#>  [51,] -3.9960390
#>  [52,] -3.2780839
#>  [53,] -3.0741524
#>  [54,] -4.2632406
#>  [55,] -3.5556352
#>  [56,] -4.7560586
#>  [57,] -2.1776058
#>  [58,] -2.7773175
#>  [59,] -1.0260712
#>  [60,] -1.9673480
#>  [61,] -2.0877761
#>  [62,] -2.6240350
#>  [63,] -0.1746850
#>  [64,]  1.0580110
#>  [65,]  4.0526267
#>  [66,]  4.7826708
#>  [67,]  4.9032510
#>  [68,]  5.0553409
#>  [69,]  5.4740200
#>  [70,]  8.4689281
#>  [71,]  7.1702278
#>  [72,]  5.8186628
#>  [73,]  6.3680065
#>  [74,]  5.5026436
#>  [75,]  2.1433248
#>  [76,]  3.6107397
#>  [77,]  4.9240552
#>  [78,]  5.0441466
#>  [79,]  3.9254539
#>  [80,]  4.6328932
#>  [81,]  6.5909480
#>  [82,]  6.4320829
#>  [83,]  7.1278039
#>  [84,]  7.1214738
#>  [85,]  5.4865175
#>  [86,]  4.4050389
#>  [87,]  5.8144000
#>  [88,]  5.6336363
#>  [89,]  3.9356597
#>  [90,]  4.6481629
#>  [91,]  4.7431498
#>  [92,]  4.0751236
#>  [93,]  3.3795917
#>  [94,]  4.0776611
#>  [95,]  6.0599934
#>  [96,]  7.3491548
#>  [97,]  4.8911444
#>  [98,]  4.7971705
#>  [99,]  1.8195182
#> [100,]  1.7749003
```
