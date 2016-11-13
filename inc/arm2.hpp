// Informática Gráfica
//
// Alberto Sola - 2016
// -----------------------------------------------------------------------------

#ifndef __ARM2_HPP
#define __ARM2_HPP

#include "drawable.hpp"
#include "arm.hpp"
#include "cylinder.hpp"

// -----------------------------------------------------------------------------

class Arm2 : public Drawable{
private:
  // TODO: static
  Arm arm;
  Cylinder cylinder;

  void draw_arm(DrawMode mode) const;
  void draw_cylinder(DrawMode mode) const;

public:
  Arm2();

  void draw(DrawMode mode) const;
};

#endif
