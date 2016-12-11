#include "cube2.hpp"

Cube2::Cube2(){
  generate_board(20);
}

void Cube2::draw(DrawMode mode) const{
    glPushMatrix();
      glTranslatef(0,0.5,0);
      Board::draw(mode);
      glRotatef(180,0,0,1);
      glTranslatef(0,1,0);
      Board::draw(mode);
    glPopMatrix();
    glPushMatrix();
      glTranslatef(0,0,0.5);
      glRotatef(90,1,0,0);
      Board::draw(mode);
    glPopMatrix();
    glPushMatrix();
      glRotatef(90,0,1,0);
      glTranslatef(0,0,0.5);
      glRotatef(90,1,0,0);
      Board::draw(mode);
    glPopMatrix();
    glPushMatrix();
      glRotatef(180,0,1,0);
      glTranslatef(0,0,0.5);
      glRotatef(90,1,0,0);
      Board::draw(mode);
    glPopMatrix();
    glPushMatrix();
      glRotatef(270,0,1,0);
      glTranslatef(0,0,0.5);
      glRotatef(90,1,0,0);
      Board::draw(mode);
    glPopMatrix();
}
