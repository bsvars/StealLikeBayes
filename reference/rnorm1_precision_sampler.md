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
#>               [,1]
#>   [1,] -0.35736735
#>   [2,]  0.58656465
#>   [3,]  0.80394037
#>   [4,] -0.76460876
#>   [5,] -2.66797560
#>   [6,] -1.02073359
#>   [7,] -2.66420975
#>   [8,] -1.79673337
#>   [9,]  1.98295465
#>  [10,]  2.06402771
#>  [11,]  1.96934845
#>  [12,]  3.02697384
#>  [13,]  4.05462015
#>  [14,]  1.40111584
#>  [15,]  1.52014773
#>  [16,] -0.16110219
#>  [17,] -2.18390744
#>  [18,] -1.86642603
#>  [19,] -2.26285802
#>  [20,] -2.90106188
#>  [21,] -2.92400786
#>  [22,] -2.47586479
#>  [23,]  0.20473016
#>  [24,]  2.08860766
#>  [25,]  1.99381975
#>  [26,]  2.12369110
#>  [27,]  0.00700192
#>  [28,]  1.31909344
#>  [29,]  0.42048943
#>  [30,]  1.23708550
#>  [31,]  1.54713390
#>  [32,]  0.45854790
#>  [33,]  1.26433250
#>  [34,]  0.16012953
#>  [35,]  2.84329625
#>  [36,]  2.35999073
#>  [37,]  4.23397066
#>  [38,]  3.41995003
#>  [39,]  3.42189479
#>  [40,]  3.00532401
#>  [41,]  5.58298291
#>  [42,]  6.95979035
#>  [43,] 10.11555947
#>  [44,] 11.02108400
#>  [45,] 11.31985794
#>  [46,] 11.65060051
#>  [47,] 12.24940152
#>  [48,] 15.43533346
#>  [49,] 14.33264301
#>  [50,] 13.16806989
#>  [51,] 13.90137010
#>  [52,] 13.21857764
#>  [53,] 10.02943108
#>  [54,] 11.66142686
#>  [55,] 13.14652922
#>  [56,] 13.44184340
#>  [57,] 12.49557636
#>  [58,] 13.37413178
#>  [59,] 15.50930779
#>  [60,] 15.53139697
#>  [61,] 16.40889654
#>  [62,] 16.58548988
#>  [63,] 15.12967613
#>  [64,] 14.22147952
#>  [65,] 15.80451026
#>  [66,] 15.79958502
#>  [67,] 14.27368094
#>  [68,] 15.15622126
#>  [69,] 15.42252444
#>  [70,] 14.92464381
#>  [71,] 14.39677720
#>  [72,] 15.26236823
#>  [73,] 17.41641413
#>  [74,] 18.88228902
#>  [75,] 16.59900985
#>  [76,] 16.67571598
#>  [77,] 13.86410861
#>  [78,] 13.98107518
#>  [79,] 12.36516913
#>  [80,] 11.97695290
#>  [81,] 11.15038884
#>  [82,] 11.04435246
#>  [83,] 11.17894567
#>  [84,] 12.21471204
#>  [85,] 10.60379031
#>  [86,]  9.10160442
#>  [87,]  6.62731692
#>  [88,]  5.13371280
#>  [89,]  4.89929178
#>  [90,]  5.19592191
#>  [91,]  4.84406808
#>  [92,]  4.09751983
#>  [93,]  4.68949696
#>  [94,]  5.45882518
#>  [95,]  3.52112418
#>  [96,]  3.90594623
#>  [97,]  4.22564054
#>  [98,]  5.65287395
#>  [99,]  5.03735536
#> [100,]  3.01707662
```
