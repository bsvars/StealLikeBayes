
set.seed(1)
run_no1 = rgig1(1, 1, 1)

set.seed(1)
run_no2 = rgig1(1, 1, 1)

expect_identical(
  run_no1,
  run_no2,
  info = "rgig1: the first draws of two runs to be identical."
)

expect_error(
  rgig1(NA, 1, 1),
  info = "rgig1: wrong first argument."
)

expect_error(
  rgig1(1, NA, 1),
  info = "rgig1: wrong second argument."
)

expect_error(
  rgig1(1, 1, NA),
  info = "rgig1: wrong third argument."
)
