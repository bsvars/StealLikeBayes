set.seed(1)
run_no1 = sample_variances_horseshoe( rep(0, 2), rep(0, 2), 1, rep(1, 2), 1)

set.seed(1)
run_no2 = sample_variances_horseshoe( rep(0, 2), rep(0, 2), 1, rep(1, 2), 1)

expect_identical(
  run_no1[1],
  run_no2[1],
  info = "rgennorm: the first draws of two runs to be identical."
)

expect_error(
  sample_variances_horseshoe( c(NA, 2), rep(0, 2), 1, rep(1, 2), 1),
  info = "rgennorm: wrong first argument."
)

expect_error(
  sample_variances_horseshoe( rep(0, 2),  c(NA, 2), 1, rep(1, 2), 1),
  info = "rgennorm: wrong second argument."
)


