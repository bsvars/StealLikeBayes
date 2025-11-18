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
#>   [1,] -0.91917283
#>   [2,] -1.68823484
#>   [3,] -2.48221940
#>   [4,] -2.64199652
#>   [5,] -1.28832139
#>   [6,] -1.32182583
#>   [7,] -0.54234099
#>   [8,] -0.51424069
#>   [9,] -1.02608586
#>  [10,]  0.61392671
#>  [11,] -0.80637244
#>  [12,] -1.80650472
#>  [13,] -0.76371246
#>  [14,]  0.13243309
#>  [15,]  0.07773981
#>  [16,] -1.55971924
#>  [17,] -3.23578560
#>  [18,] -1.37758615
#>  [19,] -2.85555781
#>  [20,] -1.80805153
#>  [21,]  1.97004760
#>  [22,]  1.92864140
#>  [23,]  1.72278464
#>  [24,]  2.65696992
#>  [25,]  3.52801778
#>  [26,]  0.75501909
#>  [27,]  0.80271661
#>  [28,] -0.92521364
#>  [29,] -2.94546078
#>  [30,] -2.60623746
#>  [31,] -2.98275581
#>  [32,] -3.59303166
#>  [33,] -3.58430194
#>  [34,] -3.11041022
#>  [35,] -0.43027217
#>  [36,]  1.41896966
#>  [37,]  1.27778841
#>  [38,]  1.36212823
#>  [39,] -0.78750213
#>  [40,]  0.49690992
#>  [41,] -0.43147748
#>  [42,]  0.35617286
#>  [43,]  0.63222375
#>  [44,] -0.48659169
#>  [45,]  0.29052713
#>  [46,] -0.84104351
#>  [47,]  1.80912946
#>  [48,]  1.28508451
#>  [49,]  3.11416184
#>  [50,]  2.25226052
#>  [51,]  2.20952316
#>  [52,]  1.75002092
#>  [53,]  4.27914828
#>  [54,]  5.59717550
#>  [55,]  8.68315046
#>  [56,]  9.50964097
#>  [57,]  9.72763562
#>  [58,]  9.97730464
#>  [59,] 10.49409288
#>  [60,] 13.59106097
#>  [61,] 12.39622838
#>  [62,] 11.14523840
#>  [63,] 11.79404656
#>  [64,] 11.02763667
#>  [65,]  7.76268973
#>  [66,]  9.32240859
#>  [67,] 10.73070771
#>  [68,] 10.94706382
#>  [69,]  9.92358790
#>  [70,] 10.72575355
#>  [71,] 12.78079716
#>  [72,] 12.72036731
#>  [73,] 13.51483632
#>  [74,] 13.60768867
#>  [75,] 12.07047405
#>  [76,] 11.08449984
#>  [77,] 12.58951482
#>  [78,] 12.50523653
#>  [79,] 10.90229624
#>  [80,] 11.70905211
#>  [81,] 11.89878562
#>  [82,] 11.32505251
#>  [83,] 10.72285123
#>  [84,] 11.51419591
#>  [85,] 13.59143705
#>  [86,] 14.97745891
#>  [87,] 12.61553261
#>  [88,] 12.61605602
#>  [89,]  9.73108070
#>  [90,]  9.77738646
#>  [91,]  8.09238901
#>  [92,]  7.63702815
#>  [93,]  6.74454973
#>  [94,]  6.57356808
#>  [95,]  6.64340571
#>  [96,]  7.61373881
#>  [97,]  5.93800552
#>  [98,]  4.37345631
#>  [99,]  1.83977965
#> [100,]  0.28966459
```
