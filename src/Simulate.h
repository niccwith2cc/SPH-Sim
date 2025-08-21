#include "Vec3.h"
#include "Particle.h"
#include <vector>
#include <algorithm>
#include <math.h>

const Vec3 g(0.0f, -9.806f, 0.0f);

float Dt(std::vector<Particle> &particleList){
  float CFL = 0.5f;
  float eps = 1e-6f;
  float dx = 1.0f;

  float maxVel = eps;
  for (auto& p: particleList){
    Vec3 vel = p.getVelocity();
    float velMag = std::sqrt(vel.getX() * vel.getX() +
                             vel.getY() * vel.getY() +
                             vel.getZ() * vel.getZ());
    if (velMag > maxVel) maxVel = velMag; 
  }

  return CFL*dx / std::max(maxVel, eps);
}

void gravity(Particle &p){
  p.setAcc(g);
}

void timestep(Particle &p, float dt){
  Vec3 pos = p.getPosition();
  Vec3 vel = p.getVelocity();

  pos += vel * dt + g * dt * dt * 0.5f;
  p.setPosition(pos);

  vel += g * dt;
  p.setVelocity(vel);
}

void simulate(std::vector<Particle> &particleList, float finalTime){
  float time = 0.0f;
  float dt;
  int timeSteps = 0;
  
  while (time < finalTime){
    if (timeSteps < 2){
      dt = 0.01f;
      std::cout << "The current time step dt: " << dt << ", with time: "  << timeSteps << std::endl;
    } else {
      dt = Dt(particleList);
    } 

    timeSteps++;
    time += dt;

    for (auto & p : particleList){
        gravity(p);
        timestep(p, dt);
      }
  }
}