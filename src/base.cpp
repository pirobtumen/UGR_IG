// Informática Gráfica
//
// Alberto Sola - 2016
// -----------------------------------------------------------------------------

#include "base.hpp"

// -----------------------------------------------------------------------------
// Implementación
// -----------------------------------------------------------------------------

Base::Base(){
  draw(DrawMode::ALL);
}

// -----------------------------------------------------------------------------

void Base::draw_cube(DrawMode mode) const{

  // Valores de transformacion
  double tx = 1;
  double ty = 0.1;
  double tz = 1;

  glPushMatrix();
  glScaled(tx,ty,tz);
  cube.draw(mode);
  glPopMatrix();
}

// -----------------------------------------------------------------------------

void Base::draw_cylinder(DrawMode mode) const{

  // Valores de transformacion
  double tx = 0.1;
  double ty = 1;
  double tz = 0.1;

  glPushMatrix();
  glScaled(tx,ty,tz);
  cylinder.draw(mode);
  glPopMatrix();

}

// -----------------------------------------------------------------------------

void Base::draw(DrawMode mode) const{

  draw_cube(mode);
  draw_cylinder(mode);

}

// -----------------------------------------------------------------------------
