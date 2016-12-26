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
  static Sphere sphere;
  static Cylinder cylinder;

  void draw_sphere(DrawMode mode) const;
  void draw_cylinder(DrawMode mode) const;

public:
  Arm();

  double get_alpha() const;
  void draw(DrawMode mode) const;
};

#endif
