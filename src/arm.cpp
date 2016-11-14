// Informática Gráfica
//
// Alberto Sola - 2016
// -----------------------------------------------------------------------------

#include "arm.hpp"

// -----------------------------------------------------------------------------

Arm::Arm(){}

// -----------------------------------------------------------------------------

void Arm::draw(DrawMode mode) const{
  draw_sphere(mode);
  draw_cylinder(mode);
}

// -----------------------------------------------------------------------------

void Arm::draw_sphere(DrawMode mode) const{
  glPushMatrix();
  glTranslated(-3.2,0,0);
  glScaled(0.5,0.5,0.5);
  sphere.draw(mode);
  glPopMatrix();
}

// -----------------------------------------------------------------------------

void Arm::draw_cylinder(DrawMode mode) const{
  glPushMatrix();
  glTranslated(-1.5,0,0);
  glRotated(90,0,0,1);
  glScaled(0.1,3,0.1);
  cylinder.draw(mode);
  glPopMatrix();
}

// -----------------------------------------------------------------------------
