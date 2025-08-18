#include "Vec3.h"
#include <cassert>
#include <iostream>

int main(){
  Vec3 a;
  std::cout << "Vector a: " << a << std::endl;
  std::cout << "Chechpoint 1 " << std::endl;

  a.set(5.f, 6.f, 8.f);
  std::cout << "Vector a: " << a << std::endl;
  assert( (void("check correct: "),  a.getX() == 5.f) );
  std::cout << "Checkpoint 2 " << std::endl; 

  float check1 = a.getX();
  assert( (void("Check X:"), check1 == 5.f) );
  std::cout << "Checkpoint 3" << std::endl;

  float check2 = a.getY();
  assert( (void("Check Y:"), check2 == 6.f) );
  std::cout << "Checkpoint 4" << std::endl;

  float check3 = a.getZ();
  assert( (void("Check Z:"), check3 == 8.f) );
  std::cout << "Checkpoint 5" << std::endl;

  Vec3 b(2.f, 9.f, 3.f);
  Vec3 c;
  std::cout << "Vector c: " << c << std::endl;
  std::cout << "Checkpoint 6" << std::endl;

  c = a + b;
  std::cout << "Vector c: " << c << std::endl;
  assert(c.getX() == 7.f);
  std::cout << "Checkpoint 7" << std::endl;

  Vec3 d = c.getVec();
  std::cout << "Vector d: " << d << std::endl;
  std::cout << "Checkpoint 8" << std::endl;

  c += Vec3(1.f, 1.f, 1.f);
  std::cout << "Vector c: " << c << std::endl;
  std::cout << "Checkpoint 9" << std::endl;

  d /= Vec3(2.f, 2.f, 2.f);
  std::cout << "Vector d: " << d << std::endl;
  std::cout << "Checkpoint 10" << std::endl;

  b.set(0.0f, 0.0f, 0.0f);


  
}