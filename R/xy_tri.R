#' Title
#'
#' @param x
#' @param y
#'
#' @return
#' @export
#'
#' @examples
xy_tri <- function(x, y = NULL) {
  xy <- xy.coords(x, y)
  y <- as.double(xy[["y"]])
  x <- as.double(xy[["x"]])
  xy_tri_cpp(x, y)
}
