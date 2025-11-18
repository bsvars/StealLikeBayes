
set.seed(1)
run_no1 = rgennorm(1, diag(2), array(diag(2), c(2,2,2)), 3, list(diag(2), matrix(1,1,2)))

set.seed(1)
run_no2 = rgennorm(1, diag(2), array(diag(2), c(2,2,2)), 3, list(diag(2), matrix(1,1,2)))

expect_identical(
  run_no1[1],
  run_no2[1],
  info = "rgennorm: the first draws of two runs to be identical."
)

expect_error(
  rgennorm(a, diag(2), array(diag(2), c(2,2,2)), 3, list(diag(2), matrix(1,1,2))),
  info = "rgennorm: wrong first argument."
)

expect_error(
  rgennorm(1, matrix(c(NA,0,0,1),2,2), array(diag(2), c(2,2,2)), 3, list(diag(2), matrix(1,1,2))),
  info = "rgennorm: wrong second argument."
)

expect_error(
  rgennorm(1, diag(2), array(-diag(2), c(2,2,2)), 3, list(diag(2), matrix(1,1,2))),
  info = "rgennorm: wrong third argument."
)
