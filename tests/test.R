library(PBDE)

tau = 0.1;
x_prior = rnorm(10, 0, 1);
x_vec = rnorm(50, 2, 1);

output = p_n(x_vec, x_prior, tau, mu, sigma)
print(output$value)
