#' Title
#'
#' @param x
#' @param y
#'
#' @return
#' @export
#'
#' @examples
#' x    <- c(2.3,3.0,7.0,1.0,3.0,8.0)
#' y    <- c(2.3,3.0,2.0,5.0,8.0,9.0)
#'
#' tri <- xy_tri(x, y)
#' plot(x, y)
#' polygon(cbind(x, y)[rbind(matrix(tri, 3L), NA), ])
xy_tri <- function(x, y = NULL) {
  xy <- xy.coords(x, y)
  y <- as.double(xy[["y"]])
  x <- as.double(xy[["x"]])
  xy_tri_cpp(x, y) + 1L ## 0-based in C++, 1-based in R
}
