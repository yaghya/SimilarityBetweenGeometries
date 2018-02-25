/*  
        Boost Competency Test (Gsoc '18)
        Author : Yaghyavardhan Sing Khangarot
        Institute: IIIT Hyderabad
*/

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
//typedef  bg:: strategy :: distance ::haversine HaverSineDistance;

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

bool isSubSequence(char str1[], char str2[], int m, int n)
{
    // Base Cases
    if (m == 0) return true;
    if (n == 0) return false;
 
    // If last characters of two strings are matching
    if (str1[m-1] == str2[n-1])
        return isSubSequence(str1, str2, m-1, n-1);
 
    // If last characters are not matching
    return isSubSequence(str1, str2, m, n-1);
}

template <typename Point>
double  Distance(Point const& P1,Point const& P2)
{
	//std::cout << typeid(Point).name() << std::endl;
	std::string Str2=typeid(Point).name(),Str1="geographic";
	bool flag=isSubSequence(&Str1[0],&Str2[0],(int)Str1.length(),(int)Str2.length());
	
	if(flag)
	{
		double Radius=6371; // in Kliometer
		typedef  bg:: strategy :: distance :: haversine<double> HaverSineDistance;
		return bg::distance(P1,P2,HaverSineDistance(Radius));
	}
	else
		return bg::distance(P1,P2);

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
		CoupMat(i,j)= Distance(ls1[i],ls2[j]);
	else if (i==1 &&  j>1 )
		CoupMat(i,j)= max(coup(i,j-1,ls1,ls2,CoupMat),Distance(ls1[i],ls2[j]));
	else if (i>1 && j==1)
		CoupMat(i,j)= max(coup(i-1,j,ls1,ls2,CoupMat),Distance(ls1[i],ls2[j]));
	else if (i>1 && j>1)
		CoupMat(i,j)= max(min(min(coup(i,j-1,ls1,ls2,CoupMat),coup(i,j-1,ls1,ls2,CoupMat)),coup(i,j-1,ls1,ls2,CoupMat)),Distance(ls1[i],ls2[j]));
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
