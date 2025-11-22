# 1D half-line truncation
set.seed(101)
mu <- 0
sigma <- 1
lower <- 1
samples <- rtmvnorm_hmc(n = 8000, mean = mu, cov = matrix(sigma^2), initial = 2, Fmat = matrix(1), g = -lower, burn = 800)

# Analytical moments
alpha <- (lower - mu) / sigma
Z <- 1 - pnorm(alpha)
expected_mean <- mu + dnorm(alpha) / Z * sigma
expected_var <- sigma^2 * (1 + alpha * dnorm(alpha) / Z - (dnorm(alpha) / Z)^2)

expect_equal(mean(samples), expected_mean, tolerance = 0.08, info = "1D half-line: mean")
expect_equal(var(samples)[1, 1], expected_var, tolerance = 0.08, info = "1D half-line: var")

# 1D bounded interval
set.seed(123)
mu <- 1.2
sigma <- 0.8
lower <- 0.25
upper <- 2
samples <- rtmvnorm_hmc(n = 5000, mean = mu, cov = matrix(sigma^2), initial = 0.5, Fmat = rbind(1, -1), g = c(-lower, upper), burn = 500)

# Analytical moments
alpha <- (lower - mu) / sigma
beta <- (upper - mu) / sigma
Z <- pnorm(beta) - pnorm(alpha)
term1 <- (dnorm(alpha) - dnorm(beta)) / Z
term2 <- (alpha * dnorm(alpha) - beta * dnorm(beta)) / Z
expected_mean <- mu + term1 * sigma
expected_var <- sigma^2 * (1 + term2 - term1^2)

expect_equal(mean(samples), expected_mean, tolerance = 0.05, info = "1D bounded: mean")
expect_equal(var(samples)[1, 1], expected_var, tolerance = 0.06, info = "1D bounded: var")

# Positive quadrant (2D)
set.seed(234)
samples <- rtmvnorm_hmc(n = 9000, mean = c(0, 0), cov = diag(2), initial = c(1, 1), Fmat = diag(2), g = c(0, 0), burn = 900)

# Analytical moments (same for both dimensions, lower=0)
alpha <- 0
Z <- 1 - pnorm(0)
expected_mean <- dnorm(0) / Z
expected_var <- 1 + 0 - (dnorm(0) / Z)^2

expect_equal(mean(samples[, 1]), expected_mean, tolerance = 0.05, info = "Positive quadrant: dim1 mean")
expect_equal(mean(samples[, 2]), expected_mean, tolerance = 0.05, info = "Positive quadrant: dim2 mean")
expect_equal(var(samples)[1, 1], expected_var, tolerance = 0.05, info = "Positive quadrant: dim1 var")
expect_equal(var(samples)[2, 2], expected_var, tolerance = 0.05, info = "Positive quadrant: dim2 var")
expect_equal(var(samples)[1, 2], 0, tolerance = 0.05, info = "Positive quadrant: cov")

# Rectangular constraints (2D independent)
set.seed(456)
mean_vec <- c(-0.2, 0.5)
cov_mat <- diag(c(1.6, 0.4))
lower <- c(0, -1)
upper <- c(Inf, 1)
samples <- rtmvnorm_hmc(n = 6000, mean = mean_vec, cov = cov_mat, initial = c(0.2, 0), Fmat = rbind(c(1, 0), c(0, 1), c(0, -1)), g = c(0, 1, 1), burn = 800)

# Dim 1
sigma1 <- sqrt(cov_mat[1, 1])
alpha1 <- (lower[1] - mean_vec[1]) / sigma1
Z1 <- 1 - pnorm(alpha1)
expected_mean1 <- mean_vec[1] + dnorm(alpha1) / Z1 * sigma1
expected_var1 <- sigma1^2 * (1 + alpha1 * dnorm(alpha1) / Z1 - (dnorm(alpha1) / Z1)^2)

# Dim 2
sigma2 <- sqrt(cov_mat[2, 2])
alpha2 <- (lower[2] - mean_vec[2]) / sigma2
beta2 <- (upper[2] - mean_vec[2]) / sigma2
Z2 <- pnorm(beta2) - pnorm(alpha2)
term1_2 <- (dnorm(alpha2) - dnorm(beta2)) / Z2
term2_2 <- (alpha2 * dnorm(alpha2) - beta2 * dnorm(beta2)) / Z2
expected_mean2 <- mean_vec[2] + term1_2 * sigma2
expected_var2 <- sigma2^2 * (1 + term2_2 - term1_2^2)

expect_equal(mean(samples[, 1]), expected_mean1, tolerance = 0.05, info = "Rectangular: dim1 mean")
expect_equal(var(samples)[1, 1], expected_var1, tolerance = 0.06, info = "Rectangular: dim1 var")
expect_equal(mean(samples[, 2]), expected_mean2, tolerance = 0.05, info = "Rectangular: dim2 mean")
expect_equal(var(samples)[2, 2], expected_var2, tolerance = 0.06, info = "Rectangular: dim2 var")
expect_equal(var(samples)[1, 2], 0, tolerance = 0.04, info = "Rectangular: cov")
