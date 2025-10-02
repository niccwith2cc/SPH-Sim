#ifndef PARTICLE_H
#define PARTICLE_H
#include "Vec3.h"

class Particle
{
private:
  Vec3 position, velocity, acc, force;
  float mass;
  float pressure;

public:
  Particle();
  Particle(const Vec3& pos, const Vec3& vel, const Vec3& a, const Vec3& f, float m, float p);

  // Getters
  const Vec3& getPosition() const;
  const Vec3& getVelocity() const;
  const Vec3& getAcc() const;
  const Vec3& getForce() const;
  float getMass() const;
  float getPressure() const;

  // Setters
  void setPosition(const Vec3& pos);
  void setVelocity(const Vec3& vel);
  void setAcc(const Vec3& a); 
  void setForce(const Vec3& f); 
  void setMass(float m); 
  void setPressure(float p); 
  // Utility: zero and accumulate forces
  void zeroForce();
  void addForce(const Vec3& f);
};
#endif //PARTICLE_H