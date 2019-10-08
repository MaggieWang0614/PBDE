
// [[Rcpp::depends(RcppArmadillo)]]

#include <ctime>
#include <RcppArmadillo.h>
#include <chrono>
#include <iostream>
#include "density.h"

using namespace Rcpp;
using namespace std;
using namespace chrono;


void rcpp_to_std2(arma::mat y, std::vector<double> &y_std)
{
    // The goal of this function is to convert RCPP object to std objects

    // TODO: Refactor code so for loops are self contained functions
    // TODO: Why RCPP and not std?
    // TODO: inefficient Need Replacement?

    size_t N = y.n_rows;

    // Create y_std
    for (size_t i = 0; i < N; i++)
    {
        y_std[i] = y(i, 0);
    }
    return;
}

Rcpp::List p_n(double x, arma::mat x_vec, arma::mat x_prior, double tau){

    auto start = system_clock::now();
    size_t n = x_vec.n_rows;

    std::vector<double> x_vec_std(n);
    // std::vector<double> x_prior_std(x_prior.n_rows);
    std::vector<double> y(1);
    y.push_back(x);

    rcpp_to_std2(x_vec, x_vec_std);
    // rcpp_to_std2(x_prior, x_prior_std);

    ///////////////////////////////////////////////////////////////////

    double output = density_vec(y, x_vec_std, tau, true);

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

        return Rcpp::List::create(
        Rcpp::Named("value") = output
        );

}

Rcpp::List test(){
    double output = test_d();
    return Rcpp::List::create(
        Rcpp::Named("value") = output
    );
}


