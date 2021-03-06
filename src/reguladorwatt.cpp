// Informática Gráfica
//
// Alberto Sola - 2016
// -----------------------------------------------------------------------------

#include "reguladorwatt.hpp"

// -----------------------------------------------------------------------------

Base Watt::base;
Body Watt::body;

// -----------------------------------------------------------------------------

Watt::Watt(){
  draw(DrawMode::ALL);
}

// -----------------------------------------------------------------------------

void Watt::draw(DrawMode mode) const{
  glPushMatrix();
  glTranslated(0,1,0);
  base.draw(mode);

  glPushMatrix();
  glTranslated(0,0.75,0);
  glRotated(rotate_angle,0,1,0);
  body.draw(mode);
  glPopMatrix();

  glPopMatrix();
}

// -----------------------------------------------------------------------------
