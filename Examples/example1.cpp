

#include <algorithm> // for reverse, unique
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
#include <limits>
#include "FrechetDistance.hpp"

#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/array.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

// Optional includes and defines to handle c-arrays as points, std::vectors as linestrings
#include <boost/geometry/geometries/register/linestring.hpp>
#include <boost/geometry/geometries/adapted/c_array.hpp>

BOOST_GEOMETRY_REGISTER_C_ARRAY_CS(cs::cartesian)
namespace bnu = boost::numeric::ublas;
namespace bg = boost::geometry;
BOOST_GEOMETRY_REGISTER_LINESTRING_TEMPLATED(std::vector)
BOOST_GEOMETRY_REGISTER_LINESTRING_TEMPLATED(std::deque)




int main(void)
{
    using namespace boost::geometry;

    // Define a linestring, which is a vector of points, and add some points
    // (we add them deliberately in different ways)
    typedef model::d2::point_xy<double> point_2d;
    typedef model::linestring<point_2d> linestring_2d;
    linestring_2d ls1,ls2;

    // points can be created using "make" and added to a linestring using the std:: "push_back"
    ls1.push_back(make<point_2d>(1.1, 1.1));

    // points can also be assigned using "assign_values" and added to a linestring using "append"
    point_2d lp;
    assign_values(lp, 2.5, 2.1);
    append(ls1, lp);
    append(ls1,make<point_2d>(4.5,7.0));
    // Lines can be streamed using DSV (delimiter separated values)
    std::cout << dsv(ls1) << std::endl;
/*
    // The bounding box of linestrings can be calculated
    typedef model::box<point_2d> box_2d;
    box_2d b;
    envelope(ls, b);
    std::cout << dsv(b) << std::endl;
*/
    // The length of the line can be calulated
    std::cout << "length: " << length(ls1) << std::endl;
    std:: cout << "size" << ls1.size() << std::endl;
    std::cout << "number of points 2: " << typeid(boost::size(ls1)).name() << std::endl;
 	int  a = boost::size(ls1);
 	std::cout << a << std::endl;
 	const double c[][2] = { {3.1, 3.1}, {4.9, 1.1}, {3.1, 1.9} };
 	append(ls2, c);
 	double FrechDis;
 	FrechDis=FrechetDistance(ls1,ls2);
 	std::cout <<"FrechetDistance=" << FrechDis << std::endl;
    return 0;

 }