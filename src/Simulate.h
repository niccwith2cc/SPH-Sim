#include "Vec3.h"
#include "Particle.h"
#include "Globals.h"
#include <vector>
#include <algorithm>
#include <math.h>

void spawnParticles(std::vector<Particle> &particleList, int nb){
  constexpr float massSun = 5.0f;
  constexpr float massPlanet = 2.0f;

  const Vec3 posSun = {0.0f, 0.0f, 0.0f};
  const Vec3 posPlanet = {2.0f, 5.0f, 0.0f};
  const Vec3 fill = {0.0f, 0.0f, 0.0f};

  Particle sun(posSun, fill, fill, fill, massSun, 0.0f);
  particleList.push_back(sun);
  Particle planet(posPlanet, fill, fill, fill, massPlanet, 0.0f);
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
  Particle& p1 = particleList[0];
  Particle& p2 = particleList[1];

  Vec3 r = p1.getPosition() - p2.getPosition();
  float dist = r.length();
  
  const float eps = 1e-8;
  
  Vec3 F = r * ( (-G * p1.getMass() * p2.getMass()) / (dist * dist * dist) );
  // Vec3 F = {0.0f, 0.0f, 0.0f};

  // if (invR.getX() < eps || invR.getY() < eps || invR.getZ() < eps){  
  //   F = invR * -G * p1.getMass() * p2.getMass();
  // } else {
  //   F = invR * -G * p1.getMass() * p2.getMass() * 1e-8f;
  // }

  p1.setForce(F);
  // if (DEBUG){
  //   std::cout << "Set force on Sun to be: " << F  << " N." << std::endl;
  // }
  p2.setForce(F*-1.0f);
  // if (DEBUG){
  //   std::cout << "Set force on Planet to be: " << F*-1  << " N." << std::endl;
  // }
  
  for (auto& p : particleList){
    Acc(p);
  }
}


void timestep(std::vector<Particle>& particleList, float dt){
  
  for (auto& p : particleList) {
    Vec3 pos = p.getPosition();
    Vec3 vel = p.getVelocity();
    Vec3 acc = p.getAcc();

    pos += vel * dt + acc * (0.5f * dt * dt);
    vel += acc * (0.5f * dt);

    p.setPosition(pos);
    p.setVelocity(vel);
  }

  Force(particleList);

  for (auto& p : particleList) {
    Vec3 vel = p.getVelocity();
    Vec3 acc = p.getAcc();

    vel += acc * (0.5f * dt);

    p.setVelocity(vel);
  }

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

void simulateStep(std::vector<Particle> &particleList, float &time, float &dt, int &timeSteps, bool &status){
  dt = Dt(particleList);

  timeSteps++;
  time += dt;

  Force(particleList);

  timestep(particleList, dt);

  for (auto& p : particleList){
    applyBoxConstraint(p, boundary);
  }

  if (status){
    std::cout << "The current time step dt: " << dt << ", with time: "  << time << std::endl; 
  }
}
