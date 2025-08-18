#include "Vec3.h"
#include <iostream>

Vec3::Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
Vec3::Vec3(float _x, float _y, float _z): x(_x), y(_y), z(_z) {}

float Vec3::getX() const {return x;};
float Vec3::getY() const {return y;};
float Vec3::getZ() const {return z;};
Vec3  Vec3::getVec() const {return *this;};

void Vec3::set(float _x, float _y, float _z)
{
  this-> x = _x;
  this-> y = _y;
  this-> z = _z;
};

Vec3 Vec3::operator+(const Vec3& other) const { return Vec3(x + other.x, y + other.y, z + other.z); };
Vec3 Vec3::operator-(const Vec3& other) const { return Vec3(x - other.x, y - other.y, z - other.z); };
Vec3 Vec3::operator*(const Vec3& other) const { return Vec3(x * other.x, y * other.y, z * other.z); };
Vec3 Vec3::operator/(const Vec3& other) const { 
  if (other.x == 0.0f || other.y == 0.0f || other.z == 0.0f) {
    throw std::runtime_error("Division by zero in operator/");
  }
  return Vec3(x / other.x, y / other.y, z / other.z); 
};

Vec3& Vec3::operator+=(const Vec3& other) { x += other.x, y += other.y, z += other.z; return *this; };
Vec3& Vec3::operator-=(const Vec3& other) { x -= other.x, y -= other.y, z -= other.z; return *this; };
Vec3& Vec3::operator*=(const Vec3& other) { x *= other.x, y *= other.y, z *= other.z; return *this; };
Vec3& Vec3::operator/=(const Vec3& other) {
  if (other.x == 0.0f || other.y == 0.0f || other.z == 0.0f) {
    throw std::runtime_error("Division by zero in operator/=");
  } 
  x /= other.x, y /= other.y, z /= other.z; 
  return *this; 
};

void Vec3::Print() const {
  std::cout << "Vector " << " " << x << " " << y << " " << z << std::endl;
};

std::ostream& operator<<(std::ostream& os, const Vec3& v){
  os << "Vec3( " << v.x << ", " << v.y << ", " << v.z << " )";
  return os;
}
