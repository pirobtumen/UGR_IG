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
  cube.draw_points(r,g,b);
  glPopMatrix();
}

// -----------------------------------------------------------------------------

void Base::draw_edges(double r, double g, double b) const{
  glPushMatrix();
  glScaled(1,0.5,1);
  cube.draw_edges(r,g,b);
  glPopMatrix();
}

// -----------------------------------------------------------------------------

void Base::draw_surfaces(double r, double g, double b) const{
  glPushMatrix();
  glScaled(1,0.5,1);
  cube.draw_surfaces(r,g,b);
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

void Base::draw(DrawMode mode, double r, double g, double b) const{

  switch (mode) {
		case ALL:
			draw_all();
			break;
		case CHESS:
			draw_chess();
			break;
		case SURFACES:
			draw_surfaces(r,g,b);
			break;
		case EDGES:
			draw_edges(r,g,b);
			break;
		case POINTS:
			draw_points(r,g,b);
			break;
	}

}

// -----------------------------------------------------------------------------
