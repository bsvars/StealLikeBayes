set.seed(1)
run_no1 <- rig2(10, 1, 10)

set.seed(1)
run_no2 <- rig2(10, 1, 10)

expect_identical(
  run_no1,
  run_no2,
  info = "rig2: draws are reproducible when the seed is fixed."
)

expect_equal(
  length(run_no1),
  10L,
  info = "rig2: returns the requested number of draws."
)

expect_true(
  all(is.finite(run_no1) & run_no1 > 0),
  info = "rig2: all draws are finite and positive."
)

set.seed(27)
draws <- rig2(100000, 3, 10)

expect_equal(
  mean(draws),
  3 / (10 - 2),
  tolerance = 0.01,
  info = "rig2: sample mean agrees with the theoretical mean."
)

expect_error(rig2(0, 1, 10), info = "rig2: n must be positive.")
expect_error(rig2(1.5, 1, 10), info = "rig2: n must be an integer.")
expect_error(rig2(1, 0, 10), info = "rig2: s must be positive.")
expect_error(rig2(1, 1, 0), info = "rig2: nu must be positive.")
expect_error(rig2(NA, 1, 10), info = "rig2: n must not be missing.")
expect_error(rig2(1, NA, 10), info = "rig2: s must not be missing.")
expect_error(rig2(1, 1, NA), info = "rig2: nu must not be missing.")
