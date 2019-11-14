library(PBDE)

### The density regression if I cut at the correct point
x_binom = rbinom(50, 1, 0.5)
x_prior = as.matrix(rnorm(50, 0, 1)*x_binom + rnorm(50, 2, 1)*(1-x_binom))
x_prior1 = x_prior[x_binom == 1]
x_prior0 = x_prior[x_binom == 0]
n = 100
x = seq(min(x_prior), max(x_prior), length.out=n)
density = density1 = density0 = density_cut = rep(n, 0)
tau = 1

for (tau in c(0.1)){#c(0.1, 1, 5, 10)){
  for (i in 1:length(x)){
    density[i] = exp(density(as.matrix(x[i]), as.matrix(x_prior), tau, TRUE)[[1]])
    density1[i] = exp(density(as.matrix(x[i]), as.matrix(x_prior1), tau, TRUE)[[1]])
    density0[i] = exp(density(as.matrix(x[i]), as.matrix(x_prior0), tau, TRUE)[[1]])
  }
  
  h <- hist(x_prior, plot=FALSE)
  h$counts=h$counts/sum(h$counts)
  plot(h, main = toString(tau))
  h <- hist(x_prior1, plot=FALSE)
  h$counts=h$counts/sum(h$counts)
  plot(h, main = toString(tau), col="grey",add=T)
  h <- hist(x_prior0, plot=FALSE)
  h$counts=h$counts/sum(h$counts)
  plot(h, main = toString(tau), col="white",add=T)
  lines(x, density, type = 'l')
  lines(x, density1, type = 'l', col = 'blue')
  lines(x, density0, type = 'l', col = 'green')
}

### Compare the density of split and no split
tau = 0.1
x_binom = rbinom(50, 1, 0.5)
x = as.matrix(rnorm(50, 0, 1)*x_binom + rnorm(50, 1, 1)*(1-x_binom))
x_prior = as.matrix(x[sample(50, 2)])
density_split = exp(density(x[x_binom==1], x_prior, tau, TRUE)[[1]] + density(x[x_binom==0], x_prior, tau, TRUE)[[1]])
density_no_split = exp(density(x, x_prior, tau, TRUE)[[1]])
cat("density of split ", density_split, "\n")
cat("density of no split ", density_no_split, "\n")

## More complicated case
set.seed(100)
n = 200 # size of training set
nt = 100 # size of testing set
d = 2 # number of TOTAL variables
dcat = 2 # number of categorical variables

  if (d != dcat) {
    x = matrix(runif((d - dcat) * n, -2, 2), n, d - dcat)
    if (dcat > 0) {
      x = cbind(x, matrix(as.numeric(sample(-2:2, dcat * n, replace = TRUE)), n, dcat))
    }
  } else {
    # x = matrix(as.numeric(sample(-2:2, dcat * n, replace = TRUE)), n, dcat)
    x = matrix(as.numeric(sample(0:1, dcat * n, replace = TRUE)), n, dcat)
  }
  xtest = unique(x)
  f = function(x) {
    sin(x[, 2] ^ 2) + sin(rowSums(x[, 1:2] ^ 2)) + (x[, 1] + x[, 2] ^ 2) / (3 + x[, 1])
  }
  ftrue = f(x)
  ftest = f(xtest)
  sigma = sd(ftrue)

  y = ftrue + sigma * rnorm(n)
  y_test = ftest + sigma * rnorm(nrow(xtest)) # nt
  # sample prior from y
  y_prior = as.matrix(y[sample(n, 10)])

  tau=0.1
  y = as.matrix(y)
  y_test = as.matrix(seq(min(y), max(y), length.out=n))
  density_x2_0_x1_0 = density_x2_0_x1_1 = density_x2_1 = rep(n, 0)
  for (i in 1:length(y_test)){
    density_x2_0_x1_0[i] = exp(density(as.matrix(y_test[i]), as.matrix(y[x[,1]==0&x[,2]==0]),tau,TRUE)[[1]])
    density_x2_0_x1_1[i] = exp(density(as.matrix(y_test[i]), as.matrix(y[x[,2]==0&x[,1]==1]),tau,TRUE)[[1]])
    density_x2_1[i] = exp(density(as.matrix(y_test[i]), as.matrix(y[x[,2]==1]), tau,TRUE)[[1]])
  }
  h <- hist(y, plot=FALSE)
  h$counts=h$counts/sum(h$counts)
  plot(h, main = toString(tau))
  h <- hist(y[x[,2]==1], plot=FALSE)
  h$counts=h$counts/sum(h$counts)
  plot(h, main = toString(tau), col = "grey", add=T)
  h <- hist(y[x[,1]==0&x[,2]==0], plot=FALSE)
  h$counts=h$counts/sum(h$counts)
  plot(h, main = toString(tau), col = "lightskyblue1", add=T)
  lines(y_test, density_x2_0_x1_0, type = 'l', col = "green")
  lines(y_test, density_x2_0_x1_1, type = 'l', col = 'blue')
  lines(y_test, density_x2_1, type = 'l', col = 'red')
  
  
  
  
  