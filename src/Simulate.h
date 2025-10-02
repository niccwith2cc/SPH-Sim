#include "Vec3.h"
#include "Particle.h"
#include "Globals.h"
#include <vector>
#include <algorithm>
#include <math.h>

void spawnParticles(std::vector<Particle> &particleList, int nb){
  constexpr float massSun = M_Sun;
  constexpr float massPlanet = M_Planet;

  const Vec3 posSun = {0.0f, 0.0f, 0.0f};
  const Vec3 posPlanet = {50.0f, 0.0f, 0.0f};
  const Vec3 fill = {0.0f, 0.0f, 0.0f};

  Vec3 r = posSun - posPlanet;
  float dist = r.length();
  float vel = std::sqrt(G * M_Sun / dist);
  const Vec3 initial_vel = {0.0f, vel, 0.0f};

  Particle sun(posSun, fill, fill, fill, massSun, 0.0f);
  particleList.push_back(sun);

  Particle planet(posPlanet, fill, fill, fill, massPlanet, 0.0f);
  planet.setVelocity(initial_vel);
  particleList.push_back(planet);
}

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

void Acc(Particle &p){
  Vec3 F = p.getForce();
  float m = p.getMass();
  Vec3 Acc = F / m;
  std::cout << "Acc is " << Acc << std::endl;
  p.setAcc(Acc);
} 

void Force(std::vector<Particle>& particleList){
  Particle& sun = particleList[0];
  Particle& planet = particleList[1];

  Vec3 r = planet.getPosition() - sun.getPosition(); // planet to sun
  float dist2 = r.getX()*r.getX() + r.getY()*r.getY() + r.getZ()*r.getZ();
  const float softening = 1e-6f; // TODO: tune this variable
  float invDist = 1.0f / std::sqrt(dist2 + softening*softening);
  float invDist3 = invDist * invDist * invDist;
  
  Vec3 F = r * ( -G * sun.getMass() * planet.getMass() * invDist3 );

  sun.setForce(F* -1.0f);
  planet.setForce(F);
  
  Acc(sun);
  Acc(planet);
}


void applyBoxConstraint(Particle &p, const Box& boundary, float restitution = 1.0f){
  Vec3 pos = p.getPosition();
  Vec3 vel = p.getVelocity();

  // check x axis
  if (pos.getX() < boundary.xmin){
    pos.set(boundary.xmin, pos.getY(), pos.getZ());
    vel.set(-vel.getX() * restitution, vel.getY(), vel.getZ());
  } else if (pos.getX() > boundary.xmax){
    pos.set(boundary.xmax, pos.getY(), pos.getZ());
    vel.set(-vel.getX() * restitution, vel.getY(), vel.getZ());
  }

  // check y axis
  if (pos.getY() < boundary.ymin){
    pos.set(pos.getX(), boundary.ymin, pos.getZ());
    vel.set(vel.getX(), -vel.getY() * restitution, vel.getZ());
  } else if (pos.getY() > boundary.ymax){
    pos.set(pos.getX(), boundary.ymax, pos.getZ());
    vel.set(vel.getX(), -vel.getY() * restitution, vel.getZ());
  }

  // check z axis
  if (pos.getZ() < boundary.zmin){
    pos.set(pos.getX(), pos.getY(), boundary.zmin);
    vel.set(vel.getX(), vel.getY(), -vel.getZ() * restitution);
  } else if (pos.getZ() > boundary.zmax){
    pos.set(pos.getX(), pos.getY(), boundary.zmax);
    vel.set(vel.getX(), vel.getY(), -vel.getZ() * restitution);
  }

  p.setPosition(pos);
  p.setVelocity(vel);
}

void simulateStep(std::vector<Particle> &particleList, float &time, float &dt, int &timeSteps){
  dt = Dt(particleList);
  timeSteps++;
  time += dt;

  Force(particleList);

  for (auto& p : particleList) {
    Vec3 vel = p.getVelocity();
    Vec3 acc = p.getAcc();

    vel += acc * (0.5f * dt);
    p.setVelocity(vel);
  }

  for (auto& p : particleList){
    Vec3 pos = p.getPosition() ;
    Vec3 vel = p.getVelocity() ;
    
    pos += vel * dt;
    p.setPosition(pos);
  }

  Force(particleList);

  for (auto& p : particleList) {
    Vec3 vel = p.getVelocity();
    Vec3 acc = p.getAcc();
    
    vel += acc * (0.5f * dt);
    p.setVelocity(vel);
  }

  for (auto& p : particleList){
    applyBoxConstraint(p, boundary);
  }

  if (DEBUG){
    std::cout << "The current time step dt: " << dt << ", with time: "  << time << std::endl; 
  }
}
