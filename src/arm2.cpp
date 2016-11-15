// Informática Gráfica
//
// Alberto Sola - 2016
// -----------------------------------------------------------------------------

#include "arm2.hpp"

// -----------------------------------------------------------------------------

Arm Arm2::arm;
Cylinder Arm2::cylinder;

// -----------------------------------------------------------------------------

Arm2::Arm2(){}

// -----------------------------------------------------------------------------

void Arm2::draw(DrawMode mode) const{
  draw_arm(mode);
  draw_cylinder(mode);
}

// -----------------------------------------------------------------------------

void Arm2::draw_arm(DrawMode mode) const{
  glPushMatrix();
  arm.draw(mode);
  glPopMatrix();
}

// -----------------------------------------------------------------------------

void Arm2::draw_cylinder(DrawMode mode) const{
  glPushMatrix();
  glTranslated(-1.5,0,0);
  glRotated(get_beta(),0,0,1);
  glTranslated(0,-0.65,0);
  glScaled(0.05,1.3,0.05);
  cylinder.draw(mode);
  glPopMatrix();
}

// -----------------------------------------------------------------------------

double Arm2::get_beta() const{
  return -35+(speed/MAX_SPEED)*116;
}

// -----------------------------------------------------------------------------

double Arm2::get_cyl_length() const{
  return 1.3;
}

// -----------------------------------------------------------------------------
