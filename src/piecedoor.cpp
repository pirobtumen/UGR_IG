#include "piecedoor.hpp"

// -----------------------------------------------------------------------------

Piece PieceDoor::piece;
Cube PieceDoor::door;

// -----------------------------------------------------------------------------

PieceDoor::PieceDoor(){
  draw(DrawMode::ALL);
}

// -----------------------------------------------------------------------------

void PieceDoor::draw(DrawMode mode) const{
  double sx = 0.04;
  double sy = 1.2;
  double sz = sx;

  double tx = -0.15;
  double ty = -0.65;
  double tz = 0;

  piece.draw(mode);

  glPushMatrix();
  glTranslated(tx,ty,tz);
  glScaled(sx,sy,sz);
  door.draw(mode);
  glPopMatrix();

}

// -----------------------------------------------------------------------------
