// Informática Gráfica
//
// Alberto Sola - 2016
// -----------------------------------------------------------------------------

#ifndef __SPHERE_HPP
#define __SPHERE_HPP

#include "revolutionsurface.hpp"
#include <cmath>

// -----------------------------------------------------------------------------

class Sphere : public RevolutionSurface{

private:
  void generate_profile();

public:
  Sphere();
  Sphere(unsigned int profile_points);

};

// -----------------------------------------------------------------------------

#endif
