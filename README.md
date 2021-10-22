
<!-- README.md is generated from README.Rmd. Please edit that file -->

# delone

<!-- badges: start -->

[![R-CMD-check](https://github.com/hypertidy/delone/workflows/R-CMD-check/badge.svg)](https://github.com/hypertidy/delone/actions)
<!-- badges: end -->

The goal of delone is to provide fast Delaunay triangulation of planar
coordinates (X,Y).

## Installation

You can install the development version from
[GitHub](https://github.com/) with:

``` r
# install.packages("devtools")
devtools::install_github("hypertidy/delone")
```

## Example

This is a basic example which shows usage.

`tri` is an integer vector of triangle triplets that index the input
vectors `x` and `y`.

``` r
x    <- runif(100)
y    <- runif(100)
library(delone)
tri <- xy_tri(x, y)
plot(x, y)
polygon(cbind(x, y)[rbind(matrix(tri, 3L), NA), ])
```

<img src="man/figures/README-example-1.png" width="100%" />

This suite hows speed comparisons.

``` r
library(delone)
n <- 10000
xy <- cbind(runif(n), runif(n))
## grid for akima
#grid <- expand.grid(x = seq(0, 1, length = as.integer(sqrt(n))), y = seq(0, 1, length = as.integer(sqrt(n))))

## these choice were
## 1) easy for me to try out
## 2)  pure Delaunay convex hull triangulation on bare points (akima is different, uses triangulation under the hood)
## 3) first published here: https://rpubs.com/cyclemumner/416456
rbenchmark::benchmark(
  ## akima doesn't really belong
  #akima = akima::interpp(xy[,1], xy[,2], z = rep(0, n), xo = grid$x, yo = grid$y),
  deldir = deldir::deldir(xy[,1], xy[,2], suppressMsge = TRUE),
  CGAL = delone::xy_tri(xy[,1], xy[,2]),
  geometry = geometry::delaunayn(xy, options = "Pp"),
  rgeos = rgeos::gDelaunayTriangulation(sp::SpatialPoints(xy)),
  RTriangle = RTriangle::triangulate(RTriangle::pslg(xy)),
  sf = sf::st_triangulate(sf::st_sfc(sf::st_multipoint(xy))),
  ## spatstat belongs but (was) the slowest (needs update to new spatstat.<family>)
  #spatstat = spatstat::delaunay(spatstat::ppp(xy[,1], xy[,2], window = spatstat::owin(range(xy[,1]), range(xy[,2])))),
  tripack = tripack::tri.mesh(xy[,1], xy[,2]),
  replications = 10,
  order = "relative",
  columns = c('test', 'elapsed', 'relative', 'user.self', 'sys.self')
)
#>        test elapsed relative user.self sys.self
#> 2      CGAL   0.137    1.000     0.137    0.000
#> 5 RTriangle   0.597    4.358     0.572    0.023
#> 7   tripack   0.702    5.124     0.703    0.000
#> 3  geometry   0.774    5.650     0.730    0.044
#> 6        sf   9.607   70.124     9.572    0.031
#> 4     rgeos  15.803  115.350    15.711    0.087
#> 1    deldir  39.887  291.146    39.798    0.080
```

## Code of Conduct

Please note that the delone project is released with a [Contributor Code
of
Conduct](https://contributor-covenant.org/version/2/0/CODE_OF_CONDUCT.html).
By contributing to this project, you agree to abide by its terms.
