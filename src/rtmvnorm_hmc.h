#ifndef RTMVNORM_HMC_H
#define RTMVNORM_HMC_H

#include <RcppEigen.h>

// This script is adapted from the 'tnorm' R package by Kenyon Ng distributed
// under the MIT license and subsequently modified by Kenyon Ng.

void validate_dimensions(const Eigen::MatrixXd &cov,
                         const Eigen::VectorXd &mean,
                         const Eigen::VectorXd &initial,
                         const Eigen::MatrixXd &F, const Eigen::VectorXd &g);

Eigen::MatrixXd symmetrise(const Eigen::MatrixXd &cov);

Eigen::LLT<Eigen::MatrixXd> safe_cholesky(const Eigen::MatrixXd &cov);

Eigen::MatrixXd transform_constraint_matrix(const Eigen::MatrixXd &F,
                                            const Eigen::MatrixXd &L);

Eigen::VectorXd transform_constraint_offset(const Eigen::MatrixXd &F,
                                            const Eigen::VectorXd &mean,
                                            const Eigen::VectorXd &g);

Eigen::VectorXd transform_initial_point(const Eigen::MatrixXd &L,
                                        const Eigen::VectorXd &mean,
                                        const Eigen::VectorXd &initial);

Rcpp::List get_next_linear_hit_time(const Eigen::VectorXd &a,
                                    const Eigen::VectorXd &b,
                                    const Eigen::MatrixXd &F,
                                    const Eigen::VectorXd &g,
                                    int current_constraint);

bool verify_constraints(const Eigen::VectorXd &x, const Eigen::MatrixXd &F,
                        const Eigen::VectorXd &g);

Eigen::VectorXd reflect_velocity(const Eigen::VectorXd &f,
                                 const Eigen::VectorXd &hit_velocity);

Eigen::VectorXd sample_next(const Eigen::VectorXd &current_sample, int dim,
                            const Eigen::MatrixXd &F, const Eigen::VectorXd &g);

Eigen::MatrixXd rtmvnorm_hmc(int n, const Eigen::VectorXd &mean,
                             const Eigen::MatrixXd &cov,
                             const Eigen::VectorXd &initial,
                             const Eigen::MatrixXd &F, const Eigen::VectorXd &g,
                             int burn);

#endif // RTMVNORM_HMC_H
