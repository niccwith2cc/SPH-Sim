#ifndef VEC3_H
#define VEC3_H

#include <iostream>

class Vec3 {
private:
  float x, y, z;

public:
  Vec3();
  Vec3(float _x, float _y, float _z);

  float getX() const;
  float getY() const;
  float getZ() const;
  Vec3 getVec() const ;

  void set(float _x, float _y, float _z);

  Vec3 operator+(const Vec3& other) const;
  Vec3 operator-(const Vec3& other) const;
  Vec3 operator*(const Vec3& other) const;
  Vec3 operator/(const Vec3& other) const;

  Vec3& operator+=(const Vec3& other);
  Vec3& operator-=(const Vec3& other);
  Vec3& operator*=(const Vec3& other);
  Vec3& operator/=(const Vec3& other);

  void Print() const;
  friend std::ostream& operator<<(std::ostream& os, const Vec3& v);

};

#endif // VEC3_H
