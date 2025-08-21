#include "Simulate.h"

void simulate(Particle &p){
  Vec3 pos = p.getPosition();
  pos += Vec3(0.01f, 0.0f, 0.0f);
  p.setPosition(pos);
}