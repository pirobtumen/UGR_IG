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
  double sx = 1.75;
  double sy = 0.125;
  double sz = 1.75;

  // Valores de traslación
  double tx = 0;
  double ty = -3.2;
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
  double sx = 0.08;
  double sy = 4;
  double sz = sx;

  glPushMatrix();
  glTranslated(0,-1.2,0);
  glScaled(sx,sy,sz);
  cylinder.draw(mode);
  glPopMatrix();

}

// -----------------------------------------------------------------------------

void Base::draw(DrawMode mode) const{

  draw_cube(mode);
  draw_cylinder(mode);

}

// -----------------------------------------------------------------------------
