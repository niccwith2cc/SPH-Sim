#include "Particle.h"
#include "Vec3.h"
#include <vector>

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
      Vec3 pos(j * dx, i * dx, 0.0f);
      Particle p;
      p.setPosition(pos);
      particleList.push_back(p);
    }
  }
}