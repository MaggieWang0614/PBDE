#include <cmath>
#include <vector>
#include <numeric> 
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "gsl/gsl_integration.h"
#include "density.h"


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
        
        if (iter <=2){p.print();}
		double output =  exp( - pow(y - y_vec[iter], 2) / 2 / tau / (x+1) - pow(log(x) - mu, 2) / 2 / pow(sigma, 2) ) / x / sqrt(x + 1);
        return output;
        // return 0.0;
    }

double test_f(double x, void * params)
{
    return exp( - pow(x, 2) / 2) / sqrt( 2 * 3.1415926 ) ;
}


    double density_single(double x, std::vector<double> x_vec, double tau, double mu, double sigma)
    {
        // std::cout << "x " << x << endl;
        // std::cout << "tau " << tau << endl;
        // std::cout << "mu " << mu << endl;
        // std::cout << "simga " << sigma << endl;
        // std::cout << "x_vec";
        // for (size_t i = 0; i < x_vec.size(); i++){std::cout << " " << x_vec[i];}
        // std::cout << endl;

        double output = 0.0;
        Params params(x, x_vec, tau, mu, sigma);
        std::vector<double> int_vec(params.n);
        std::vector<double> error(params.n);
        // std::vector<double> integral_vec(this->n);

        gsl_function F;
        F.function = &kernal;
        F.params = &params;
        gsl_integration_workspace *w = gsl_integration_workspace_alloc(3000);
       
        for (size_t i = 0; i < params.n; i++){
            // std::cout << "density_single loop i " << i << endl;
            
            gsl_integration_qagiu(&F, 0, 0, 1e-6, 1000, w, &int_vec[i], &error[i]);
            // std::cout << i << ": " << int_vec[i] << endl;
            params.iter += 1;
            F.params = &params;
        }
        
        output = std::accumulate(int_vec.begin(),int_vec.end(), 0.0) / params.n / 2 / 3.1415926 / sqrt(tau) / sigma;
        
        gsl_integration_workspace_free(w);
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

double density_vec(std::vector<double> x_vec, std::vector<double> x_prior, double tau, bool take_log)
{

    size_t h;
    size_t n = x_prior.size();
    size_t N = x_vec.size() + n + 1;
    std::vector<double> x_density(x_vec.size());
    double eta_n, rho_h, nu_n1, nu_n2, nu_n, mu_n, sigma_n, temp, output, x;
    eta_n = nu_n1 = nu_n2 = 1;

    for (size_t h = 1; h <= n; h++)
    {
        rho_h = double (N-h) / double(N-h+1);
        eta_n = eta_n / rho_h;
        nu_n1 = nu_n1 * (2-rho_h) / pow(rho_h, 2);
        nu_n2 = nu_n2 * pow(rho_h, -2);
    }
    nu_n = nu_n1 - nu_n2;
    mu_n = 2*log(eta_n - 1) - 0.5*log(nu_n + pow(eta_n - 1, 2));
    sigma_n = sqrt(log( 1 + nu_n / pow(eta_n - 1, 2)));
    h = n;

    for (size_t i = 0; i < x_vec.size(); i++)
    {
        x = x_vec[i];
        temp = density_single(x, x_prior, tau, mu_n, sigma_n);
        x_density[i] = temp;

        h++;
        rho_h = double (N-h) / double(N-h+1);
        eta_n *= 1 / rho_h;
        nu_n1 *= (2-rho_h) / pow(rho_h, 2);
        nu_n2 *= pow(rho_h, -2);
        nu_n = nu_n1 - nu_n2;
        mu_n = 2*log(eta_n - 1) - 0.5*log(nu_n + pow(eta_n - 1, 2));
        sigma_n = sqrt(log( 1 + nu_n / pow(eta_n - 1, 2)));
        x_prior.push_back(x);
    }
    if (take_log)
    {
        output = 0;
        for (size_t i = 0; i < x_density.size(); i++) { output += log(x_density[i]);}
        return output;
    }
    else
    {
        output = 0;
        for (size_t i = 0; i < x_density.size(); i++) { output *= x_density[i];}
        return output;
    }
    
}
