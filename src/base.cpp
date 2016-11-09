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

  // Valores de escalado
  double sx = 1;
  double sy = 0.1;
  double sz = 1;

  // Valores de traslación
  double tx = 0;
  double ty = -0.75;
  double tz = 0;

  glPushMatrix();
  glTranslated(tx,ty,tz);
  glScaled(sx,sy,sz);
  cube.draw(mode);
  glPopMatrix();
}

// -----------------------------------------------------------------------------

void Base::draw_cylinder(DrawMode mode) const{

  // Valores de transformacion
  double tx = 0.05;
  double ty = 1.5;
  double tz = tx;

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
