#pragma once
#include "Particle.h"
#include "Vec3.h"
#include "Boundary.h"
#include <vector>

#define DEBUG 1
#define INFO 1

const Vec3 g(0.0f, -9.806f, 0.0f);

const float G = 1.0f;
constexpr float M_Sun = 1000.0f;
constexpr float M_Planet = 1.0f;

const Box boundary(160.0f, 160.0f, 20.0f);