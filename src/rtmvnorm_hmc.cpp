#define _USE_MATH_DEFINES
#include "rtmvnorm_hmc.h"
#include <RcppEigen.h>
#include <cmath>
#include <cstddef>

// This script is adapted from the 'tnorm' R package by Kenyon Ng distributed
// under the MIT license and subsequently modified by Kenyon Ng.

// [[Rcpp::interfaces(cpp)]]
// [[Rcpp::export]]
void validate_dimensions(const Eigen::MatrixXd &cov,
                         const Eigen::VectorXd &mean,
                         const Eigen::VectorXd &initial,
                         const Eigen::MatrixXd &F, const Eigen::VectorXd &g) {
  const int dim = mean.size();

  if (cov.rows() != cov.cols()) {
    Rcpp::stop("Covariance must be a square matrix.");
  }
  if (cov.rows() != dim) {
    Rcpp::stop("Dimensions of mean and covariance do not match.");
  }
  if (initial.size() != dim) {
    Rcpp::stop("Dimensions of mean and initial value do not match.");
  }
  if (F.cols() != dim) {
    Rcpp::stop("Dimensions of mean and columns of F do not match.");
  }
  if (F.rows() != g.size()) {
    Rcpp::stop("Inconsistent dimensions of F and g.");
  }
}

// [[Rcpp::interfaces(cpp)]]
// [[Rcpp::export]]
Eigen::MatrixXd symmetrise(const Eigen::MatrixXd &cov) {
  return 0.5 * (cov + cov.transpose());
}

Eigen::LLT<Eigen::MatrixXd> safe_cholesky(const Eigen::MatrixXd &cov) {
  Eigen::LLT<Eigen::MatrixXd> cov_llt(cov);
  if (cov_llt.info() == Eigen::NumericalIssue) {
    Rcpp::stop("Covariance must be positive definite.");
  }
  return cov_llt;
}

// [[Rcpp::interfaces(cpp)]]
// [[Rcpp::export]]
Eigen::MatrixXd transform_constraint_matrix(const Eigen::MatrixXd &F,
                                            const Eigen::MatrixXd &L) {
  return F * L;
}

// [[Rcpp::interfaces(cpp)]]
// [[Rcpp::export]]
Eigen::VectorXd transform_constraint_offset(const Eigen::MatrixXd &F,
                                            const Eigen::VectorXd &mean,
                                            const Eigen::VectorXd &g) {
  return F * mean + g;
}

// [[Rcpp::interfaces(cpp)]]
// [[Rcpp::export]]
Eigen::VectorXd transform_initial_point(const Eigen::MatrixXd &L,
                                        const Eigen::VectorXd &mean,
                                        const Eigen::VectorXd &initial) {
  const Eigen::VectorXd diff = initial - mean;
  return L.triangularView<Eigen::Lower>().solve(diff);
}

// [[Rcpp::interfaces(cpp)]]
// [[Rcpp::export]]
Rcpp::List get_next_linear_hit_time(const Eigen::VectorXd &a,
                                    const Eigen::VectorXd &b,
                                    const Eigen::MatrixXd &F,
                                    const Eigen::VectorXd &g,
                                    int current_constraint) {
  double hit_time = -1;
  int cn = current_constraint;
  const double EPS = 0.00000001;
  constexpr double two_pi = 2.0 * M_PI;

  for (int i = 0; i < F.rows(); ++i) {
    const Eigen::VectorXd f = F.row(i);
    const double g_val = g(i);

    const double fa = f.dot(a);
    const double fb = f.dot(b);
    const double u = std::sqrt(fa * fa + fb * fb);

    if (!(u > g_val && u > -g_val)) {
      continue;
    }

    const double phi = std::atan2(-fa, fb);
    double t1 = std::acos(-g_val / u) - phi;
    double t2 = -t1 - 2 * phi;

    if (t1 < 0) {
      t1 += two_pi;
    }
    if (std::abs(t1) < EPS || std::abs(t1 - two_pi) < EPS) {
      t1 = 0;
    }

    if (t2 < 0) {
      t2 += two_pi;
    }
    if (std::abs(t2) < EPS || std::abs(t2 - two_pi) < EPS) {
      t2 = 0;
    }

    double t = -1;
    if (current_constraint == i) {
      t = std::max(t1, t2);
    } else if (t1 == 0 || t2 == 0) {
      const double midpoint = std::fabs(t2 - t1) / 2.0;
      if (u * std::cos(midpoint + phi) > -g_val) {
        t = std::max(t1, t2);
      } else {
        t = 0;
      }
    } else {
      t = std::min(t1, t2);
    }

    if (hit_time < 0 || t < hit_time) {
      hit_time = t;
      cn = i;
    }
  }
  return Rcpp::List::create(Rcpp::Named("hit_time") = hit_time,
                            Rcpp::Named("cn") = cn);
}

// [[Rcpp::interfaces(cpp)]]
// [[Rcpp::export]]
bool verify_constraints(const Eigen::VectorXd &x, const Eigen::MatrixXd &F,
                        const Eigen::VectorXd &g) {
  const double EPS = 0.00000001;
  for (int i = 0; i < F.rows(); ++i) {
    if (F.row(i).dot(x) + g(i) < -EPS) {
      return false;
    }
  }
  return true;
}

// [[Rcpp::interfaces(cpp)]]
// [[Rcpp::export]]
Eigen::VectorXd reflect_velocity(const Eigen::VectorXd &f,
                                 const Eigen::VectorXd &hit_velocity) {
  const double norm_sq = f.dot(f);
  const double alpha = f.dot(hit_velocity) / norm_sq;
  return hit_velocity - 2 * alpha * f;
}

// [[Rcpp::interfaces(cpp)]]
// [[Rcpp::export]]
Eigen::VectorXd sample_next(const Eigen::VectorXd &current_sample, int dim,
                            const Eigen::MatrixXd &F,
                            const Eigen::VectorXd &g) {
  constexpr double kTimeHorizon = M_PI / 2.0;
  constexpr int kInterruptInterval = 50;
  constexpr int kMaxOuterIterations = 500;
  const double EPS = 0.00000001;

  int interrupt_counter = 0;

  for (int iteration = 0;; ++iteration) {
    if (interrupt_counter++ % kInterruptInterval == 0) {
      Rcpp::checkUserInterrupt();
    }
    if (iteration > kMaxOuterIterations) {
      Rcpp::stop("Too many loops.");
    }

    Eigen::VectorXd position = current_sample;
    Eigen::VectorXd velocity(dim);
    for (int i = 0; i < dim; ++i)
      velocity(i) = R::norm_rand();

    double time_left = kTimeHorizon;
    int hit_constraint = -1;
    bool advance_success = true;

    // Advance until hit logic
    while (true) {
      if (interrupt_counter++ % kInterruptInterval == 0) {
        Rcpp::checkUserInterrupt();
      }

      double hit_time = -1;
      if (F.rows() > 0) {
        Rcpp::List res =
            get_next_linear_hit_time(velocity, position, F, g, hit_constraint);
        hit_time = res["hit_time"];
        hit_constraint = res["cn"];
      }

      if (hit_time < 0 || time_left < hit_time) {
        hit_constraint = -1;
        break;
      }

      if (hit_time < EPS) {
        advance_success = false;
        break;
      }

      time_left -= hit_time;
      const Eigen::VectorXd hit_velocity =
          std::cos(hit_time) * velocity - std::sin(hit_time) * position;
      position = std::sin(hit_time) * velocity + std::cos(hit_time) * position;

      const Eigen::VectorXd f = F.row(hit_constraint);

      // Reflect velocity
      velocity = reflect_velocity(f, hit_velocity);

      if (velocity.dot(f) < 0) {
        advance_success = false;
        break;
      }
    }

    if (!advance_success) {
      continue;
    }

    const Eigen::VectorXd candidate =
        std::sin(time_left) * velocity + std::cos(time_left) * position;
    if (verify_constraints(candidate, F, g)) {
      return candidate;
    }
  }
}

// [[Rcpp::interfaces(cpp)]]
// [[Rcpp::export]]
Eigen::MatrixXd rtmvnorm_hmc(int n, const Eigen::VectorXd &mean,
                             const Eigen::MatrixXd &cov,
                             const Eigen::VectorXd &initial,
                             const Eigen::MatrixXd &F, const Eigen::VectorXd &g,
                             int burn = 10) {
  validate_dimensions(cov, mean, initial, F, g);
  if (burn < 0) {
    Rcpp::stop("Burn-in must be non-negative.");
  }

  const int dim = mean.size();
  const Eigen::MatrixXd cov_sym = symmetrise(cov);
  const Eigen::LLT<Eigen::MatrixXd> cov_llt = safe_cholesky(cov_sym);
  const Eigen::MatrixXd L = cov_llt.matrixL();

  const Eigen::MatrixXd transformed_F = transform_constraint_matrix(F, L);
  const Eigen::VectorXd transformed_g = transform_constraint_offset(F, mean, g);
  Eigen::VectorXd current_sample = transform_initial_point(L, mean, initial);

  // Burn-in
  for (int i = 0; i < burn; ++i) {
    current_sample =
        sample_next(current_sample, dim, transformed_F, transformed_g);
  }

  // Sampling
  Eigen::MatrixXd draws = Eigen::MatrixXd::Zero(n, dim);
  for (int i = 0; i < n; ++i) {
    current_sample =
        sample_next(current_sample, dim, transformed_F, transformed_g);
    draws.row(i) = (L * current_sample + mean);
  }

  return draws;
}
