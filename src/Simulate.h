#include "Vec3.h"
#include "Particle.h"
#include "Globals.h"
#include <vector>
#include <algorithm>
#include <math.h>

void spawnGrid(std::vector<Particle> &particleList, int nb){
  // to use this to create a nb * nb grid
  /*
    |
    |
    |
  i |  nb |
    |  0  |  1  |  2  | ... | nb - 1 | j
  */
  float dx = 1.0f;
  for (int i = 0; i < nb; i++){
    for (int j = 0; j < nb; j++){
      Particle p;
      Vec3 pos(j * dx, i * dx, 0.00f);
      p.setPosition(pos);
      particleList.push_back(p);
    }
  }
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
  } else if (pos.getX() > boundary.ymax){
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

  for (auto & p : particleList){
    gravity(p);
  }

  for (auto & p : particleList){
    timestep(p, dt);
    applyBoxConstraint(p, boundary);
  }

  if (status){
    std::cout << "The current time step dt: " << dt << ", with time: "  << time << std::endl; 
  }
}
