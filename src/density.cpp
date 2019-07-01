#include <cmath>
#include <vector>
#include <numeric> 
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "gsl/gsl_integration.h"

using namespace std;
using std::endl;

std::ostream &operator<<(std::ostream &out, const std::vector<double> &v);
std::ostream &operator<<(std::ostream &out, const std::vector<size_t> &v);
std::ostream &operator<<(std::ostream &out, const std::vector<std::vector<double>> &v);
std::ostream &operator<<(std::ostream &out, const std::vector<std::vector<size_t>> &v);

struct Params{
public:
    double n; // lenthg of x_vec
    double tau;
    double mu; // lognormal mean
    double sigma; // lognormal sd
    double x; // x value to be valualted
    std::vector<double>  x_vec; // vector of x_i's
    double iter;

    Params(double x, std::vector<double> x_vec, double tau, double mu, double sigma)
    {
        this->iter = 0;
        this->tau = tau;
        this->mu = mu;
        this->sigma = sigma;
        this->x = x;
        this->x_vec = x_vec;
        this->n = x_vec.size();
        return;
    }
};

double kernal(double x, void * params)
	{   
        Params p = * (Params *) params;
        double tau = p.tau;
        double mu = p.mu;
        double sigma = p.sigma;
        double y = p.x;
        std::vector<double> y_vec = p.x_vec;
        double n = y_vec.size();
        double iter = p.iter;
        
		return exp( - pow(y - y_vec[iter], 2) / 2 / tau / (x+1) - pow(log(x) - mu, 2) / 2 / pow(sigma, 2) ) / x / sqrt(x + 1);
        // return 0.0;
    }

double test_f(double x, void * params)
{
    return exp( - pow(x, 2) / 2) / sqrt( 2 * 3.1415926 ) ;
}


    double density(double x, std::vector<double> x_vec, double tau, double mu, double sigma){
        double output = 0.0;
        Params params(x, x_vec, tau, mu, sigma);
        std::vector<double> int_vec(params.n);
        std::vector<double> error(params.n);
        // std::vector<double> integral_vec(this->n);

        gsl_function F;
        F.function = &kernal;
        F.params = &params;

        for (size_t i = 0; i < params.n; i++){
            gsl_integration_workspace * w = gsl_integration_workspace_alloc (1000);
            gsl_integration_qagiu (&F, 0, 0, 1e-6, 1000, w, &int_vec[i], &error[i]);

            params.iter += 1;
            F.params = &params;
            gsl_integration_workspace_free (w);
        }
        output = std::accumulate(int_vec.begin(),int_vec.end(), 0.0) / params.n / 2 / 3.1415926 / sqrt(tau) / sigma;
        return output;

    }
    double test_d(){
        gsl_function F;
        F.function = &test_f;
        // F.params = &;

        double output, error;

        gsl_integration_workspace * w = gsl_integration_workspace_alloc (1000);
        gsl_integration_qagi (&F, 0, 1e-6, 1000, w, &output, &error);
        gsl_integration_workspace_free (w);
        return output;
    }

