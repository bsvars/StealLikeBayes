
set.seed(1)
run_no1 = rmvnorm1_precision_sampler(rep(0, 100), rep(1, 100), -0.5)

set.seed(1)
run_no2 = rmvnorm1_precision_sampler(rep(0, 100), rep(1, 100), -0.5)

expect_identical(
  run_no1[1],
  run_no2[1],
  info = "rmvnorm1_precision_sampler: the first draws of two runs to be identical."
)

expect_error(
  rmvnorm1_precision_sampler(c(NA,rep(0, 99)), rep(1, 100), -0.5),
  info = "rmvnorm1_precision_sampler: wrong first argument."
)

expect_error(
  rmvnorm1_precision_sampler(rep(1, 100), c(NA,rep(0, 99)), -0.5),
  info = "rmvnorm1_precision_sampler: wrong second argument."
)

expect_error(
  rmvnorm1_precision_sampler(rep(0, 100), rep(1, 100), NA),
  info = "rmvnorm1_precision_sampler: wrong third argument."
)

expect_true(
  any(is.na(rmvnorm1_precision_sampler(rep(0, 100), rep(-1, 100), -0.5))),
  info = "rmvnorm1_precision_sampler: not positive definite returns NA."
)
