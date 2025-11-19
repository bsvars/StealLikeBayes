
set.seed(1)
run_no1 = sample_variances_normal_gamma(rep(1,2), rep(0,2), 1, 1, rep(1,2), 1, 1, TRUE, 1e-6)

set.seed(1)
run_no2 = sample_variances_normal_gamma(rep(1,2), rep(0,2), 1, 1, rep(1,2), 1, 1, TRUE, 1e-6)

expect_identical(
  run_no1,
  run_no2,
  info = "sample_variances_normal_gamma: the output vectors of two runs to be identical."
)

expect_error(
  sample_variances_normal_gamma(-1, rep(0,2), 1, 1, rep(1,2), 1, 1, TRUE, 1e-6),
  info = "sample_variances_normal_gamma: wrong first argument."
)

expect_error(
  sample_variances_normal_gamma(rep(1,2), -1, 1, 1, 1, TRUE, 1e-6),
  info = "sample_variances_normal_gamma: wrong second argument."
)

expect_error(
  sample_variances_normal_gamma(rep(1,2), rep(0,2), -1, rep(1,2), 1, 1, TRUE, 1e-6),
  info = "sample_variances_normal_gamma: wrong third argument."
)

