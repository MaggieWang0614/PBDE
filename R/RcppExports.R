p_n <- function(x, x_vec, tau, mu, sigma){

    if(class(x_vec) != "matrix"){
        cat("Input x_vec is not a matrix, try to convert type.\n")
        x_vec = as.matrix(x_vec)
    }

    obj = .Call(`_p_n`, x, x_vec, tau, mu, sigma)
    class(obj) = "density"
    return(obj)
}

test<- function(){
    obj = .Call(`_test`)
    class(obj) = "density"
    return(obj)
}

