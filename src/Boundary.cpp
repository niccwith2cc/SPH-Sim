// Boundary.cpp
#include "Boundary.h"

// Construct Boundary from total sizes in x, y and z.
Boundary::Boundary(float _x, float _y, float _z){
	xmin = -_x;
	xmax =  _x;
  
	ymin = -_y;
	ymax =  _y;

	zmin = -_z;
	zmax =  _z;

}
