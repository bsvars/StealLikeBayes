---
name: A new submission template
about: Use this template as a guide to your submission to StealLikeBayes
title: "[SUBMISSION] [main_routine]"
labels: ''
assignees: ''

---

Thank you for your submission to **StealLikeBayes**! Enjoy working on it and spread the news! 

Cheers, Tomasz

## Things to remember

- We only accept code from packages and repositories with compatible licences. If you are contributiong code from a package distributed under **GPL 3** you're good. Otherwise, you must argue the licence compatibility.
- Fully acknowledge the source of the contributed code in the file with your code and documentation.
- Provide one Bayesian statistical routine per submission.
- Your submission must consist of:
  - one **C++** file, `src/*.cpp`
  - the corresponding **C++** header file, `src/*.h`
  - one **R** file with a wrapper for your main **C++** function, `R/*.R` with full documentation and acknowledgement of the original code authorship,
  - one **R** file with tests of your function, `inst/tinytest/*.R`,
  - Updates on dependencies in `DESCRIPTION` and `R/StealLikeBayes-package.R`,
  - updates on your authorship in `DESCRIPTION`.

## To-do list

- [ ] Fork the repository [bsvars/StealLikeBayes](https://github.com/bsvars/StealLikeBayes).
- [ ] Include your **C++** file, `src/[main_routine].cpp`, named after the main routine/function you're contributing called `[main_routine]`.
  - [ ] Acknowledge the authorship of the source code in this file in line with its licence requirements.
  - [ ] Export all **C++** functions by including **Rcpp** directives `// [[Rcpp::interfaces(cpp)]]` and `// [[Rcpp::export]]`.
  - [ ] Write and **R** wrapper only for the main function you contribute.
- [ ] Include the corresponding **C++** header file, `src/[main_routine].h` with all your **C++** functions.
- [ ] Include one **R** file with a wrapper for your main **C++** function, `R/[main_routine].R`.
  - [ ] This function must include argument type checks using `stopifnot()`.
  - [ ] Include full documentation using **roxygen2** that must have all necessary elements including:
  - [ ] the description of arguments and values, also described in terms of the **C++** objects,
  - [ ] the acknowledgement of the original code authorship in `@details` with explicit references to the **R** package where the original code comes from listed in `@references`, and to the package defining the class of **C++** inputs and outputs,
  - [ ] your authorship acknowledgement in section `@authors`,
  - [ ] an example of the **R** function use in `@examples`.
- [ ] Include an **R** file with tests of your contributed **R** function, `inst/tinytest/[main_routine].R`,
- [ ] Update on dependencies in `DESCRIPTION` and `R/StealLikeBayes-package.R`.
- [ ] Update on your authorship in `DESCRIPTION`, using `person()`. In `comment` include your `ORCID` and `contributions`, for instance `contributions = "contributions: [main_routine]"`.
- [ ] Update the `NEWS.md` by providing the `[main_routine]`, your GitHub profile login, and a link to this issue.
- [ ] Push your commits linking them all to your issue by including the hash tag of your issue.
- [ ] Run checks of the package locally. They all need to pass!
```
Rcpp::compileAttributes()
devtools::document()
devtools::check()
```
- [ ] Submit your Pull Request.
- [ ] Respond to all the comments from the maintainer.