## **SimmilarityBetweenGeometries**
### (Implemented the following as the competency test for **Boost.Geometry** Gsoc '18)

## Pseudo code for finding Coupling Distance(frechet distance for curve formed by discrete points)
Function dF(P, Q): real;
input:polygonal curves P= (u1, . . . , up) and Q= (v1, . . . , vq).
return:δdF(P, Q)
ca:array[1..p,1..q] of real;
function c(i, j): real;
	begin
		if ca(i, j)>−1 then return ca(i, j)
		elsif i= 1 and j= 1 then ca(i, j) :=d(u1, v1)
		elsif i >1 and j= 1 then ca(i, j) := max{c(i−1,1), d(ui, v1)}
		elsif i= 1 and j >1 then ca(i, j) := max{c(1, j−1), d(u1, vj)}
		elsif i >1 and j >1 then ca(i, j) :=max{min(c(i−1, j), c(i−1, j−1), c(i, j−1)), d(ui, vj)}
		else ca(i, j)=∞
		return ca(i, j);
	end;
/* function c */
begin
	for i = 1 to p do for j= 1 to q do ca(i, j) :=−1.0;
	return c(p, q);
end.

### How to use this header: 
  1. Clone/Download this directory (or the file "FrechetDistance.hpp")
  1. Include the header in your code by specifying the absolute or relative path **( #include"/file_path/FrechetDistance.hpp")**