#ifndef BOUNDARY_H
#define BOUNDARY_H

class Boundary{
  public:
    float xmin, xmax;
    float ymin, ymax;
    float zmin, zmax;

    Boundary(float _x, float _y, float _z);
};

// Use public inheritance so Box is-a Boundary.
class Box : public Boundary{
  public:
    // Forward the three size components to the base Boundary constructor.
    Box(float _x, float _y, float _z) : Boundary(_x, _y, _z) {}
};
#endif 
