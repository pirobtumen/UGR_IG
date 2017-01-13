#include "global.hpp"

LightMode light_mode = FLAT;
bool active_texture = true;

double rotate_angle = 0;
double speed = MIN_SPEED;

jpg::Imagen * earth_texture = NULL;
jpg::Imagen * chess_texture = NULL;
jpg::Imagen * stars_texture = NULL;
jpg::Imagen * grass_texture = NULL;
jpg::Imagen * can_texture = NULL;
jpg::Imagen * gold_texture = NULL;


// -----------------------------------------------------------------------------

void set_texture_material(){
	/*
		Active material0.
  */

  glMaterialfv(GL_FRONT,GL_AMBIENT, (GLfloat *) &material_texture_ambient);
  glMaterialfv(GL_FRONT,GL_DIFFUSE, (GLfloat *) &material_texture_diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR, (GLfloat *) &material_texture_specular);
  glMaterialf(GL_FRONT,GL_SHININESS,10);
}

// -----------------------------------------------------------------------------

void set_texture(jpg::Imagen * texture){
  set_texture_material();
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,texture -> tamX(),texture -> tamY(),0,GL_RGB,GL_UNSIGNED_BYTE, (GLvoid *) (texture -> leerPixels()));
}

// -----------------------------------------------------------------------------
