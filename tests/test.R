library(PBDE)

x = 1
x_vec = as.matrix(rnorm(10, 0, 1))
x_prior = as.matrix(rnorm(10, 0, 1))
tau = 1
mu = 0
sigma = 1

output = p_n(x_vec, x_prior, tau, take_log = TRUE)
output = p_n(x_vec, x_prior, tau, take_log = TRUE)
print(output$value)
