// Informática Gráfica
//
// Alberto Sola - 2016
// -----------------------------------------------------------------------------

#include "body.hpp"

// -----------------------------------------------------------------------------

Body::Body(){}

// -----------------------------------------------------------------------------

void Body::draw(DrawMode mode) const{
  draw_arms(mode);
  draw_top(mode);
  draw_door(mode);
}

// -----------------------------------------------------------------------------

void Body::draw_arms(DrawMode mode) const{
  glPushMatrix();
  glTranslated(-1.5,-0.1,0);
  glRotated(5,0,0,1);
  arm.draw(mode);
  glPopMatrix();

  glPushMatrix();
  glTranslated(1.5,-0.1,0);
  glRotated(180,0,1,0);
  glRotated(5,0,0,1);
  arm.draw(mode);
  glPopMatrix();
}

// -----------------------------------------------------------------------------

void Body::draw_top(DrawMode mode) const{
  glPushMatrix();
  top.draw(mode);
  glPopMatrix();
}

// -----------------------------------------------------------------------------

void Body::draw_door(DrawMode mode) const{
  glPushMatrix();
  glTranslated(0,-0.3,0);
  door.draw(mode);
  glPopMatrix();
}

// -----------------------------------------------------------------------------
