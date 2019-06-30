library(PBDE)

x = 1
x_vec = c(1)
tau = 1
mu = 0
sigma = 1

output = p_n(x, x_vec, tau, mu, sigma)
print(output$value)
