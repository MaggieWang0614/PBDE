// [[Rcpp::depends(RcppArmadillo)]]
#include <RcppArmadillo.h>
#include <Rcpp.h>
#include "density.h"

using namespace Rcpp;

// [[Rcpp::plugins(cpp11)]]
// [[Rcpp::export]]
Rcpp::List kernel_density_vec(arma::mat x_vec, arma::mat x_prior, double tau, bool take_log);
RcppExport SEXP _kernel_density_vec(SEXP x_vecSEXP, SEXP x_priorSEXP, SEXP tauSEXP, SEXP take_logSEXP)
{
    BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter<arma::mat>::type x_vec(x_vecSEXP);
    Rcpp::traits::input_parameter<arma::mat>::type x_prior(x_priorSEXP);
    Rcpp::traits::input_parameter<double>::type tau(tauSEXP);
    Rcpp::traits::input_parameter<bool>::type take_log(take_logSEXP);
    rcpp_result_gen = Rcpp::wrap(kernel_density_vec(x_vec, x_prior, tau, take_log));
    return rcpp_result_gen;
    END_RCPP
}

Rcpp::List kernel_density(double x_vec, arma::mat x_prior, double tau, double mu, double sigma, bool take_log);
RcppExport SEXP _kernel_density(SEXP x_vecSEXP, SEXP x_priorSEXP, SEXP tauSEXP,  SEXP muSEXP,  SEXP sigmaSEXP,SEXP take_logSEXP)
{
    BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter<double>::type x_vec(x_vecSEXP);
    Rcpp::traits::input_parameter<arma::mat>::type x_prior(x_priorSEXP);
    Rcpp::traits::input_parameter<double>::type tau(tauSEXP);
    Rcpp::traits::input_parameter<double>::type mu(muSEXP);
    Rcpp::traits::input_parameter<double>::type sigma(sigmaSEXP);
    Rcpp::traits::input_parameter<bool>::type take_log(take_logSEXP);
    rcpp_result_gen = Rcpp::wrap(kernel_density(x_vec, x_prior, tau, mu, sigma, take_log));
    return rcpp_result_gen;
    END_RCPP
}

Rcpp::List test();
RcppExport SEXP _test(){
    BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(test());
    return rcpp_result_gen;
    END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    // {"_XBART_sample_int_ccrank", (DL_FUNC)&_XBART_sample_int_ccrank, 3},
    // {"_XBART_train_forest_root_std_all", (DL_FUNC)&_XBART_train_forest_root_std_all, 21},
    {"_kernel_density_vec", (DL_FUNC)&_kernel_density_vec, 4},
    {"_kernel_density", (DL_FUNC)&_kernel_density, 6},
    {"_test", (DL_FUNC)&_test, 0},

    {NULL, NULL, 0}};

RcppExport void R_init_PBDE(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}