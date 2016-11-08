// Informática Gráfica
//
// Alberto Sola - 2016
// -----------------------------------------------------------------------------

#include "base.hpp"

// -----------------------------------------------------------------------------
// Implementación
// -----------------------------------------------------------------------------

Base::Base(){
  draw_all();
}

// -----------------------------------------------------------------------------

void Base::draw_points(double r, double g, double b) const{
  glPushMatrix();
  glScaled(1,0.5,1);
  cube.draw_points();
  glPopMatrix();
}

// -----------------------------------------------------------------------------

void Base::draw_edges(double r, double g, double b) const{
  glPushMatrix();
  glScaled(1,0.5,1);
  cube.draw_edges();
  glPopMatrix();
}

// -----------------------------------------------------------------------------

void Base::draw_surfaces(double r, double g, double b) const{
  glPushMatrix();
  glScaled(1,0.5,1);
  cube.draw_surfaces();
  glPopMatrix();
}

// -----------------------------------------------------------------------------

void Base::draw_chess() const{
  glPushMatrix();
  glScaled(1,0.5,1);
  cube.draw_chess();
  glPopMatrix();
}

// -----------------------------------------------------------------------------

void Base::draw_all() const{
  draw_points(0,0,0);
  draw_edges(0,0,1);
  draw_surfaces(1,0,1);
}

// -----------------------------------------------------------------------------
