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

  double alpha = get_alpha();

  glPushMatrix();
  glRotated(alpha,0,0,1);
  arm.draw(mode);
  glPopMatrix();

  glPushMatrix();
  glRotated(180,0,1,0);
  glRotated(alpha,0,0,1);
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
  static const double arm_length = arm.get_cyl_length();
  double alpha = sin( (90-get_alpha())*2*PI/360 );
  double beta = sin( (90-arm.get_beta())*2*PI/360 );
  double height = 0;

  height -= (arm_length/alpha)*beta;

  std::cout << 90-get_alpha() << " - " << 90-arm.get_beta() << " - " << arm_length << " - " << height << std::endl;

  glPushMatrix();
  glTranslated(0,height,0);
  door.draw(mode);
  glPopMatrix();
}

// -----------------------------------------------------------------------------

double Body::get_alpha() const{
  return 5-(speed/MAX_SPEED-1)*60;
}

// -----------------------------------------------------------------------------
