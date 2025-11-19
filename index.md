# StealLikeBayes

A **C++** Compendium of Bayesian Statistical Routines for **R** Packages

This is a compendium of C++ routines useful for Bayesian statistics. We
steal other people’s C++ code, repurpose it, and export it so developers
of R packages can use it in their C++ code. We actually don’t steal
anything, or claim that Thomas Bayes did, but copy code that is
compatible with our GPL 3 licence, fully acknowledging the authorship of
the original code.

## How to contribute

You are welcome to contribute to **StealLikeBayes**! How does this work?

### Things to remember

- We only accept code from packages and repositories with compatible
  licences. If you are contributing code from a package distributed
  under **GPL 3** you’re good. Otherwise, you must argue the licence
  compatibility.
- Fully acknowledge the source of the contributed code in the file with
  your code and documentation.
- Provide one Bayesian statistical routine per submission.
- Your submission must consist of:
  - one **C++** file, `src/*.cpp`
  - the corresponding **C++** header file, `src/*.h`
  - one **R** file with a wrapper for your main **C++** function,
    `R/*.R` with full documentation and acknowledgement of the original
    code authorship,
  - one **R** file with tests of your function,
    `inst/tinytest/test_*.R`,
  - Updates on dependencies in `DESCRIPTION` and
    `R/StealLikeBayes-package.R`,
  - updates on your authorship in `DESCRIPTION`.

### To-do list

Open an issue by clicking *New issue* \>\> *A new submission template*.

Fork the repository
[bsvars/StealLikeBayes](https://github.com/bsvars/StealLikeBayes).

Follow the instructions from the issue.

Push your commits linking them all to your issue by including the hash
tag of your issue.

Run checks of the package locally. They all need to pass!

``` R
Rcpp::compileAttributes()
devtools::document()
devtools::check()
```

Submit your Pull Request.

Respond to all the comments from the maintainer.

### Instructions from the issue template

Fork the repository
[bsvars/StealLikeBayes](https://github.com/bsvars/StealLikeBayes).

Include your **C++** file, `src/[main_routine].cpp`, named after the
main routine/function you’re contributing called `[main_routine]`.

Acknowledge the authorship of the source code in this file in line with
its licence requirements.

Export all **C++** functions by including **Rcpp** directives
`// [[Rcpp::interfaces(cpp)]]` and `// [[Rcpp::export]]`.

Write and **R** wrapper only for the main function you contribute.

Include the corresponding **C++** header file, `src/[main_routine].h`
with all your **C++** functions.

Include one **R** file with a wrapper for your main **C++** function,
`R/[main_routine].R`.

This function must include argument type checks using
[`stopifnot()`](https://rdrr.io/r/base/stopifnot.html).

Include full documentation using **roxygen2** that must have all
necessary elements including:

the description of arguments and values, also described in terms of the
**C++** objects,

the acknowledgement of the original code authorship in `@details` with
explicit references to the **R** package where the original code comes
from listed in `@references`, and to the package defining the class of
**C++** inputs and outputs,

your authorship acknowledgement in section `@authors`,

an example of the **R** function use in `@examples`.

Include an **R** file with tests of your contributed **R** function,
`inst/tinytest/test_[main_routine].R`,

Update on dependencies in `DESCRIPTION` and
`R/StealLikeBayes-package.R`.

Update on your authorship in `DESCRIPTION`, using
[`person()`](https://rdrr.io/r/utils/person.html). In `comment` include
your `ORCID` and `contributions`, for instance
`contributions = "contributions: [main_routine]"`.

Update the `NEWS.md` by providing the `[main_routine]`, your GitHub
profile login, and a link to this issue.

Push your commits linking them all to your issue by including the hash
tag of your issue.

Run checks of the package locally. They all need to pass!

``` R
Rcpp::compileAttributes()
devtools::document()
devtools::check()
```

Submit your Pull Request.

Respond to all the comments from the maintainer.

## How to use the package **StealLikeBayes**

Please, feel free to use it whatever way you feel like, ofc! We create
it with two intended uses:

### Use our **C++** code in your **R** package

In order to use our **C++** code in your **R** package you need to
ensure you include all the dependencies to both: our package, and
packages on which our functions rely on such as **RcppArmadillo**. The
latter is on you!

To use **C++** code from **StealLikeBayes** follow the steps:

Include dependencies in your `DESCRIPTION` file, e.g.:
`LinkingTo: StealLikeBayes`.

Include our header in your `src/*.cpp` files, e.g.:
`#include "StealLikeBayes.h"`.

Use our functions in your **C++** code, e.g.:

``` R
arma::vec out = StealLikeBayes::rnorm1_precision_sampler(zeros<vec>(10), ones<vec>(10), -0.5);
```

### Use our **R** code in your **R** package

That’s simple!

Include dependencies in your `DESCRIPTION` file, e.g.:
`Depends: StealLikeBayes`.

Include dependencies in your `R/*-package.R` file,
e.g. `@importFrom StealLikeBayes rnorm1_precision_sampler`.

Use our functions in your **R** code, e.g.:

``` R
out = StealLikeBayes::rnorm1_precision_sampler(rep(0, 10), rep(1, 10), -0.5)
```

## Installation

You can install the **StealLikeBayes** package by running:

``` r
install_packages("StealLikeBayes")
```

You can install the development version of **StealLikeBayes** like so:

``` r
devtools::install_github("bsvars/StealLikeBayes")
```
