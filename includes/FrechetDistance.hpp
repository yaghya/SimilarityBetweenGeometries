#include <algorithm> 
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
#include <limits>

#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/linestring.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/array.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <boost/geometry/geometries/register/linestring.hpp>
#include <boost/geometry/geometries/adapted/c_array.hpp>


namespace bnu = boost::numeric::ublas;
namespace bg = boost::geometry;

template <typename D>
D max(D a,D b)
{
	return (a>b)?a:b;
}
template <typename E>
E min(E a,E b)
{	
	return (a<b)?a:b;
}

//finding the Coupling Distance using the Pseudo code written in Readme file
template <typename Index,typename Matrix,typename LineString>
inline double coup(Index i,Index j, LineString ls1, LineString ls2, Matrix CoupMat)
{
	//double Inf=numeric_limits<double>::infinity();
	double Inf=10000000;
	if(CoupMat(i,j)>-1)
			return CoupMat(i,j);
	else if (i==1 && j==1)
		CoupMat(i,j)= bg::distance(ls1[i],ls2[j]);
	else if (i==1 &&  j>1 )
		CoupMat(i,j)= max(coup(i,j-1,ls1,ls2,CoupMat),bg::distance(ls1[i],ls2[j]));
	else if (i>1 && j==1)
		CoupMat(i,j)= max(coup(i-1,j,ls1,ls2,CoupMat),bg::distance(ls1[i],ls2[j]));
	else if (i>1 && j>1)
		CoupMat(i,j)= max(min(min(coup(i,j-1,ls1,ls2,CoupMat),coup(i,j-1,ls1,ls2,CoupMat)),coup(i,j-1,ls1,ls2,CoupMat)),bg::distance(ls1[i],ls2[j]));
	else
		return Inf;

}


template<typename LineString>
inline double FrechetDistance(LineString ls1,LineString ls2)
{
	double Dis=0;
	unsigned int  a = boost::size(ls1);
 	std::cout <<"size of linestring1 ="<< a << std::endl;
 	unsigned int  b = boost::size(ls2);
 	std::cout << "size of linestring2 ="<< b << std::endl;
 	bnu::matrix<double>  CoupMat(a,b,-1);
 	
 	//calling Recursion to get the coupling distance
 	Dis=coup(a-1,b-1,ls1,ls2,CoupMat);

	return Dis;
}
