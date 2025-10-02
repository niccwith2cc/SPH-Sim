#include "Particle.h"

Particle::Particle() : position(0.0f, 0.0f, 0.0f),
                       velocity(0.0f, 0.0f, 0.0f),
                       acc(0.0f, 0.0f, 0.0f),
                       force(0.0f, 0.0f, 0.0f),
                       mass(1.0f),
                       pressure(0.0f) {}

Particle::Particle(const Vec3& pos, const Vec3& vel, const Vec3& a, const Vec3& f, float m, float p):
                   position(pos), velocity(vel), acc(a), force(f), mass(m), pressure(p) {}

const Vec3& Particle::getPosition() const{ return position; };
const Vec3& Particle::getVelocity() const{ return velocity; };
const Vec3& Particle::getAcc() const{ return acc; };
const Vec3& Particle::getForce() const{ return force; };
float Particle::getMass() const{ return mass; };
float Particle::getPressure() const{ return pressure; };

// Setters
void Particle::setPosition(const Vec3& pos) { position = pos ; };
void Particle::setVelocity(const Vec3& vel) { velocity = vel ; };
void Particle::setAcc(const Vec3& a) { acc = a ; }; 
void Particle::setForce(const Vec3& f) { force = f ; }; 
void Particle::setMass(float m) { mass = m ; }; 
void Particle::setPressure(float p) { pressure = p ; };

// Utilities
void Particle::zeroForce(){ force = Vec3(0.0f, 0.0f, 0.0f); }
void Particle::addForce(const Vec3& f){ force = force + f; }