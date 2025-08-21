#include "Vec3.h"
#include "Particle.h"
#include <vector>

constexpr float g = 9.806f;

void simulate(std::vector<Particle> &particleList){
  for (auto & p : particleList){
    gravity(p);

  }
}

void gravity(Particle &p){
  p.setAcc({0.0f, -g, 0.0f});
}

void timstep(Particle &p){
 
}