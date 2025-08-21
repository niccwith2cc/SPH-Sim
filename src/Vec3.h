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

  // Vec on Vec
  Vec3 operator+(const Vec3& other) const;
  Vec3 operator-(const Vec3& other) const;
  Vec3 operator*(const Vec3& other) const;
  Vec3 operator/(const Vec3& other) const;

  // Vec on self
  Vec3& operator+=(const Vec3& other);
  Vec3& operator-=(const Vec3& other);
  Vec3& operator*=(const Vec3& other);
  Vec3& operator/=(const Vec3& other);

  // Vec on scalar
  Vec3 operator+(const float other) const;
  Vec3 operator-(const float other) const;
  Vec3 operator*(const float other) const;
  Vec3 operator/(const float other) const;

  void Print() const;
  friend std::ostream& operator<<(std::ostream& os, const Vec3& v);

};

#endif // VEC3_H
