p_n <- function(x_vec, x_prior, tau, take_log){

    if(class(x_vec) != "matrix"){
        cat("Input x_vec is not a matrix, try to convert type.\n")
        x_vec = as.matrix(x_vec)
    }

    obj = .Call(`_p_n`,  x_vec, x_prior, tau, take_log)
    class(obj) = "density"
    return(obj)
}

test<- function(){
    obj = .Call(`_test`)
    class(obj) = "density"
    return(obj)
}

