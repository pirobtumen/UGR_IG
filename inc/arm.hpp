// Informática Gráfica
//
// Alberto Sola - 2016
// -----------------------------------------------------------------------------

#ifndef __ARM_HPP
#define __ARM_HPP

#include "drawable.hpp"
#include "sphere.hpp"
#include "cylinder.hpp"

// -----------------------------------------------------------------------------

class Arm : public Drawable{
private:
  // TODO: static
  Sphere sphere;
  Cylinder cylinder;

  void draw_sphere(DrawMode mode) const;
  void draw_cylinder(DrawMode mode) const;

public:
  Arm();

  void draw(DrawMode mode) const;
};

#endif
