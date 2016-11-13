// Informática Gráfica
//
// Alberto Sola - 2016
// -----------------------------------------------------------------------------

#include "arm2.hpp"

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
  glTranslated(0.75,-0.15,0);
  glRotated(75,0,0,1);
  glScaled(0.05,1.3,0.05);
  cylinder.draw(mode);
  glPopMatrix();
}

// -----------------------------------------------------------------------------
