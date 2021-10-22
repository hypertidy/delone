#include <vector>
#include <cpp11/list.hpp>
#include <R_ext/Rdynload.h>

#include "cpp11.hpp"
#include "cpp11/integers.hpp"
#include "cpp11/doubles.hpp"
using namespace cpp11;
namespace writable = cpp11::writable;


#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <vector>

 typedef CGAL::Exact_predicates_inexact_constructions_kernel            Kernel;
 typedef CGAL::Triangulation_vertex_base_with_info_2<unsigned int, Kernel> Vb;
 typedef CGAL::Triangulation_data_structure_2<Vb>                       Tds;
 typedef CGAL::Delaunay_triangulation_2<Kernel, Tds>                    Delaunay;
 typedef Kernel::Point_2                                                Point;

 typedef Tds::Vertex Vertex;
 typedef Tds::Vertex_iterator Vertex_iterator;
 typedef Tds::Face Face;
 typedef Tds::Face_iterator Face_iterator;
 typedef Face::Face_handle Face_handle;
 typedef Face::Vertex_handle Fvertex_handle;


[[cpp11::register]]
integers xy_tri_cpp(doubles x, doubles y) {
  // first implemented in hypertidy/laridae, this just basic planar triang
   std::vector< std::pair<Point,int> > points;
   for (int ip = 0; ip < x.size(); ip++){
     points.push_back( std::make_pair( Point(x[ip], y[ip]), ip) );
   }

   Delaunay triangulation;

   triangulation.insert(points.begin(),points.end());
   //printf("number of vertices: %i\n", triangulation.number_of_vertices());
   //printf("number of faces: %i\n", triangulation.number_of_faces());
   writable::integers vi(triangulation.number_of_faces() * 3);
   int cnt = 0;
   for(Delaunay::Finite_faces_iterator fit = triangulation.finite_faces_begin();
       fit != triangulation.finite_faces_end(); ++fit) {
     Delaunay::Face_handle face = fit;
     vi[cnt    ] = face->vertex(0)->info();
     vi[cnt + 1] = face->vertex(1)->info();
     vi[cnt + 2] = face->vertex(2)->info();
     cnt = cnt + 3;
   }


   return vi;
 }
