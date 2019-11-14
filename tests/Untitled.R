require(ggplot2)
require(tidyr)

n = 1:2000
N = length(n)+1000
rho = eta = nu1 = nu2 = nu = mu = sigma = rep(0, length(n))
rho[1] = (N-1)/N
eta[1] = 1/rho[1]
nu1[1] = (2-rho[1])/rho[1]^2
nu2[1] = 1/rho[1]^2
nu[1] = nu1[1]-nu2[1]
mu[1] = 2*log(eta[1]-1) - 0.5*log(nu[1]+(eta[1]-1)^2)
sigma[1] = sqrt(log(1+nu[1]/(eta[1]-1)^2))
for (i in 2:length(n)){
  rho[i] = (N-i)/(N-i+1)
  eta[i] = eta[i-1]/rho[i]
  nu1[i] = nu1[i-1]*(2-rho[i])/rho[i]^2
  nu2[i] = nu2[i-1]/rho[i]^2
  nu[i]=nu1[i]-nu2[i]
  mu[i] = 2*log(eta[i]-1) - 0.5*log(nu[i]+(eta[i]-1)^2)
  sigma[i] = sqrt(log(1+nu[i]/(eta[i]-1)^2))
}


cat("max nu value", max(nu))
cat("max eta value", max(eta))
param = data.frame(n, rho, mu, sigma)
param = gather(param, key = "n", value = "value")

p <- ggplot(data=param, aes(n)) + 
  geom_line( aes(x = rep(1:(length(n)/3), 3),y = value, group = n, colour=n)) +
  scale_color_brewer(palette="Dark2") + 
  labs(x = "n", y = "params", title = "Parameters")
p
# ggsave(filename = paste("Parameters.png", sep=""), width=5,height = 5)


plot(seq(0, 100, length.out=1000), dlnorm(seq(0, 100, length.out=1000), mu[2000], sigma[2000]), type='l')
var(rlnorm(10000, mu[2000], sigma[2000]))
