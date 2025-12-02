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
rmvnorm1_precision_sampler(location, precision_diag, precision_offdiag)
```

## Arguments

- location:

  an \\N\\-vector with the location parameter \\L\\. **C++**: an
  `arma::vec` vector object.

- precision_diag:

  an \\N\\-vector with the diagonal elements of the precision matrix
  \\P\\. **C++**: an `arma::vec` vector object.

- precision_offdiag:

  a numeric scalar with the off-diagonal element of the precision matrix
  \\P\\. **C++**: a `double` scalar.

## Value

an \\N\\-vector with random draws from the multivariate normal
distribution. **C++**: an `arma::vec` vector object.

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
rmvnorm1_precision_sampler(rep(0, 100), rep(1, 100), -0.5)
#>              [,1]
#>   [1,] -1.7487767
#>   [2,] -0.6821048
#>   [3,] -2.6937834
#>   [4,] -2.2436332
#>   [5,]  1.4163399
#>   [6,]  1.5548896
#>   [7,]  1.5039664
#>   [8,]  2.6180880
#>   [9,]  3.7355183
#>  [10,]  1.1384757
#>  [11,]  1.2715265
#>  [12,] -0.4156162
#>  [13,] -2.4826242
#>  [14,] -2.2238534
#>  [15,] -2.6776345
#>  [16,] -3.3786988
#>  [17,] -3.4670357
#>  [18,] -3.0804647
#>  [19,] -0.4450064
#>  [20,]  1.4147540
#>  [21,]  1.3029527
#>  [22,]  1.4152998
#>  [23,] -0.7261275
#>  [24,]  0.5582017
#>  [25,] -0.3669681
#>  [26,]  0.4225857
#>  [27,]  0.7083174
#>  [28,] -0.4065745
#>  [29,]  0.3720712
#>  [30,] -0.7599300
#>  [31,]  1.8982930
#>  [32,]  1.3939749
#>  [33,]  3.2490135
#>  [34,]  2.4175366
#>  [35,]  2.4004539
#>  [36,]  1.9640067
#>  [37,]  4.5244769
#>  [38,]  5.8889929
#>  [39,]  9.0376838
#>  [40,]  9.9404790
#>  [41,] 10.2373393
#>  [42,] 10.5663046
#>  [43,] 11.1637603
#>  [44,] 14.3515223
#>  [45,] 13.2521127
#>  [46,] 12.0882335
#>  [47,] 12.8213604
#>  [48,] 12.1380055
#>  [49,]  8.9448247
#>  [50,] 10.5712234
#>  [51,] 12.0527206
#>  [52,] 12.3453742
#>  [53,] 11.3956851
#>  [54,] 12.2704617
#>  [55,] 14.4034752
#>  [56,] 14.4244302
#>  [57,] 15.3010144
#>  [58,] 15.4769960
#>  [59,] 14.0195761
#>  [60,] 13.1082378
#>  [61,] 14.6882262
#>  [62,] 14.6808221
#>  [63,] 13.1514681
#>  [64,] 14.0300343
#>  [65,] 14.2926908
#>  [66,] 13.7908659
#>  [67,] 13.2584263
#>  [68,] 14.1194076
#>  [69,] 16.2698968
#>  [70,] 17.7334669
#>  [71,] 15.4473901
#>  [72,] 15.5202913
#>  [73,] 12.7037330
#>  [74,] 12.8146478
#>  [75,] 11.1920541
#>  [76,] 10.7963626
#>  [77,]  9.9618269
#>  [78,]  9.8474286
#>  [79,]  9.9735836
#>  [80,] 11.0011833
#>  [81,]  9.3818466
#>  [82,]  7.8702685
#>  [83,]  5.3854040
#>  [84,]  3.8800785
#>  [85,]  3.6334329
#>  [86,]  3.9178242
#>  [87,]  3.5536894
#>  [88,]  2.7945568
#>  [89,]  3.3738858
#>  [90,]  4.1308699
#>  [91,]  2.1805281
#>  [92,]  2.5523271
#>  [93,]  2.8591397
#>  [94,]  4.2738569
#>  [95,]  3.6459778
#>  [96,]  1.6127594
#>  [97,] -1.4183169
#>  [98,] -2.5699581
#>  [99,] -1.0477762
#> [100,] -1.6158873
```
