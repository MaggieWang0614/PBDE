library(PBDE)
y = 1.84159
y_prior = c(0.103888, -0.0299007, -2.08149, -0.640775, 0, -0.656573, 1.72789, -7.45759, -8.52638, 0.120353)
mu = -4.78818
sigma  = 1.80856
tau = 0.0001
take_log = TRUE
temp = kernel_density(y, as.matrix(y_prior), tau, mu, sigma, take_log)
temp[[1]] 

