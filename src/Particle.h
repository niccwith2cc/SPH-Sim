struct vec3
{
  float x, y, z;
};

class Particle
{
private:
  vec3 position, velocity, acc, force;
  float mass;
  float pressure;

public:
  Particle(const vec3& pos = {0, 0, 0}, const vec3& vel = {0,0,0}, const vec3& a = {0,0,0}, const vec3& f = {0,0,0}, float m = 1.0f, float p = 0.0f)
    : position(pos), velocity(vel), acc(a), force(f), mass(m), pressure(p) {}

  // Getters
  const vec3& getPosition() const { return position; }
  const vec3& getVelocity() const { return velocity; }
  const vec3& getAcc() const { return acc; }
  const vec3& getForce() const { return force; }
  float getMass() const { return mass; }
  float getPressure() const { return pressure; }

  // Setters
  void setPosition(const vec3& pos) { position = pos; }
  void setVelocity(const vec3& vel) { velocity = vel; }
  void setAcc(const vec3& a) { acc = a; }
  void setForce(const vec3& f) { force = f; }
  void setMass(float m) { mass = m; }
  void setPressure(float p) { pressure = p; }
};