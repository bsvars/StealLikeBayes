n <- 3

set.seed(1)
A <- rhaar1(n)

set.seed(1)
B <- rhaar1(n)

expect_identical(
  A,
  B,
  info = "rhaar: two runs with the same seed produce identical matrices."
)

expect_true(
  all.equal(t(A) %*% A, diag(n), tolerance = 1e-8),
  info = "rhaar: sampled matrix is orthogonal."
)
