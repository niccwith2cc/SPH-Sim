#include "Vec3.h"
#include "Particle.h"
#include <vector>
#include <algorithm>
#include <math.h>

const Vec3 g(0.0f, -9.806f, 0.0f);

float Dt(std::vector<Particle> &particleList){
  // Velocity based adaptive dt
  float CFL = 0.4f;
  float eps = 1e-6f;
  float dt_min = 1e-4f;
  float dt_max = 0.01f;

  float particleSpacing = 1.0f;

  float maxVel = eps;
  for (auto& p: particleList){
    Vec3 vel = p.getVelocity();
    float velMag = std::sqrt(vel.getX() * vel.getX() +
                             vel.getY() * vel.getY() +
                             vel.getZ() * vel.getZ());
    if (velMag > maxVel) maxVel = velMag; 
  }

  if (maxVel < 1e-6f) return dt_max;

  float dt_cfl =  CFL * particleSpacing / maxVel;
  // std::cout << "dt_cfl " << dt_cfl << " vs dt_min " << dt_min << " vs dt_max " << dt_max << std::endl; 
  return std::clamp(dt_cfl, dt_min, dt_max);
}

void gravity(Particle &p){
  p.setAcc(g);
}

void timestep(Particle &p, float dt){
  Vec3 pos = p.getPosition();
  Vec3 vel = p.getVelocity();
  Vec3 acc = p.getAcc();

  pos += vel * dt + acc * (dt * dt * 0.5f);
  vel += acc * (0.5f * dt);

  gravity(p);
  Vec3 newacc = p.getAcc();

  vel += newacc * (0.5f * dt);

  p.setPosition(pos);
  p.setVelocity(vel);
  p.setAcc(newacc);

}

void simulate(std::vector<Particle> &particleList, float &finalTime, float &time, float &dt, int &timeSteps){
  while (time < finalTime){
    dt = 0.01f;
    std::cout << "The current time step dt: " << dt << ", with time: "  << time << std::endl; 

    timeSteps++;
    time += dt;

    for (auto & p : particleList){
      gravity(p);
    }

    for (auto & p : particleList){
      timestep(p, dt);
    }
  }
}