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
#>   [1,]  1.4608853
#>   [2,]  2.3349694
#>   [3,]  0.2086251
#>   [4,]  1.9253446
#>   [5,]  3.5641378
#>   [6,]  0.8029575
#>   [7,]  1.4632877
#>   [8,]  2.5339769
#>   [9,]  0.2489033
#>  [10,]  1.8649541
#>  [11,]  1.0456731
#>  [12,]  1.1677633
#>  [13,] -2.0406779
#>  [14,] -2.6029099
#>  [15,] -1.7700439
#>  [16,] -2.9695457
#>  [17,] -4.2510859
#>  [18,] -1.1948321
#>  [19,] -0.1049684
#>  [20,]  0.6612540
#>  [21,]  2.0515166
#>  [22,] -2.5504467
#>  [23,] -1.7202383
#>  [24,] -2.6956830
#>  [25,] -1.8549323
#>  [26,] -2.1559116
#>  [27,] -1.7771188
#>  [28,] -1.1572903
#>  [29,] -2.7270197
#>  [30,] -0.4452003
#>  [31,] -1.1953964
#>  [32,]  1.2022129
#>  [33,] -0.1870302
#>  [34,] -3.0578951
#>  [35,] -6.1549189
#>  [36,] -3.8575262
#>  [37,] -3.3695333
#>  [38,] -3.3489014
#>  [39,] -3.0268974
#>  [40,] -2.0787420
#>  [41,]  1.1847181
#>  [42,]  1.4786665
#>  [43,]  1.5817986
#>  [44,]  1.3496192
#>  [45,] -0.2223411
#>  [46,]  3.1071914
#>  [47,]  2.3668010
#>  [48,]  1.5162699
#>  [49,]  3.6835550
#>  [50,]  6.4014721
#>  [51,]  6.7802551
#>  [52,]  5.8469884
#>  [53,]  6.2114125
#>  [54,]  7.8825454
#>  [55,]  7.0981016
#>  [56,]  8.9193424
#>  [57,]  8.9891594
#>  [58,]  8.0664665
#>  [59,]  7.5243262
#>  [60,]  9.9016478
#>  [61,]  9.6575961
#>  [62,] 10.0142459
#>  [63,]  8.1958283
#>  [64,]  6.5585978
#>  [65,]  7.2017505
#>  [66,]  9.3126415
#>  [67,] 10.0335865
#>  [68,]  7.2190461
#>  [69,]  7.1909328
#>  [70,]  4.2689336
#>  [71,]  4.1074216
#>  [72,]  2.9924009
#>  [73,]  2.3042701
#>  [74,]  2.3314854
#>  [75,]  5.5663826
#>  [76,]  3.6166151
#>  [77,]  3.0423258
#>  [78,]  2.5671991
#>  [79,]  1.2224970
#>  [80,]  0.6290351
#>  [81,]  2.8851808
#>  [82,]  5.0074181
#>  [83,]  5.8743128
#>  [84,]  5.5109248
#>  [85,]  6.1891985
#>  [86,]  6.8598586
#>  [87,]  7.5964180
#>  [88,]  7.1001796
#>  [89,]  5.9059936
#>  [90,]  4.8738788
#>  [91,]  4.7931546
#>  [92,]  3.8182000
#>  [93,]  1.3603421
#>  [94,]  2.0451010
#>  [95,]  1.9313262
#>  [96,]  2.2302862
#>  [97,]  1.8231346
#>  [98,]  0.5577038
#>  [99,] -0.2413544
#> [100,]  1.0138549
```
