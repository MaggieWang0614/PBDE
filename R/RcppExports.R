kernel_density_vec <- function(x_vec, x_prior, tau, take_log){

    if(class(x_vec) != "matrix"){
        cat("Input x_vec is not a matrix, try to convert type.\n")
        x_vec = as.matrix(x_vec)
    }

    obj = .Call(`_kernel_density_vec`,  x_vec, x_prior, tau, take_log)
    class(obj) = "density"
    return(obj)
}

kernel_density <- function(x_vec, x_prior, tau, mu, sigma, take_log){

    cat("mu", toString(mu), "\n")
    cat("sigma ", toString(sigma), "\n")

    obj = .Call(`_kernel_density`,  x_vec, x_prior, tau, mu, sigma, take_log)
    class(obj) = "density"
    return(obj)
}

test<- function(){
    obj = .Call(`_test`)
    class(obj) = "density"
    return(obj)
}

