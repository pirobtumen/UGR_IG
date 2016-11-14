// Informática Gráfica
//
// Alberto Sola - 2016
// -----------------------------------------------------------------------------

#ifndef __ARM2_HPP
#define __ARM2_HPP

#include "drawable.hpp"
#include "arm.hpp"
#include "cylinder.hpp"
#include "rotatevar.hpp"

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

  double get_beta() const;
  double get_cyl_length() const;

  void draw(DrawMode mode) const;
};

#endif
