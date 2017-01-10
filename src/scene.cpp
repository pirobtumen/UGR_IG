#include "scene.hpp"

Scene::Scene(){
  init();
}

void Scene::init(){
  char can_sup_name[] = "lata/lata-psup.ply";
  vector<Polyhedron::point> points;

  points.push_back(Polyhedron::point(0,1.4,0)); // Base superior
	points.push_back(Polyhedron::point(0.3,1.4,0));
	points.push_back(Polyhedron::point(0.5,1.2,0));
	points.push_back(Polyhedron::point(0.55,1,0));
	points.push_back(Polyhedron::point(0.5,0.8,0));
	points.push_back(Polyhedron::point(0.3,0.6,0));
	points.push_back(Polyhedron::point(0.5,0.6,0));
	points.push_back(Polyhedron::point(0.4,0.5,0));
	points.push_back(Polyhedron::point(0.4,-0.4,0));
	points.push_back(Polyhedron::point(0.5,-0.7,0));
	points.push_back(Polyhedron::point(1,-1.1,0));
	points.push_back(Polyhedron::point(1,-1.4,0));
	points.push_back(Polyhedron::point(0,-1.4,0)); // Base inferior

	pawn.set_points(points,50);

  points.clear();
  points.push_back(Polyhedron::point(0.5,-0.5,0));
  points.push_back(Polyhedron::point(0.5,0.5,0));

  can_mid.set_points(points,50);

  points.clear();
  points.push_back(Polyhedron::point(0,1.03,0));
  points.push_back(Polyhedron::point(0.027,1.03,0));
  points.push_back(Polyhedron::point(0.0418,1.03,0));
  points.push_back(Polyhedron::point(0.055,1.03,0));
  points.push_back(Polyhedron::point(0.069,1.03,0));
  points.push_back(Polyhedron::point(0.083,1.03,0));
  points.push_back(Polyhedron::point(0.097,1.03,0));
  points.push_back(Polyhedron::point(0.111,1.03,0));
  points.push_back(Polyhedron::point(0.125,1.03,0));
  points.push_back(Polyhedron::point(0.139,1.06,0));
  points.push_back(Polyhedron::point(0.153,1.06,0));
  points.push_back(Polyhedron::point(0.167,1.06,0));
  points.push_back(Polyhedron::point(0.181,1.06,0));
  points.push_back(Polyhedron::point(0.195,1.06,0));
  points.push_back(Polyhedron::point(0.209,1.06,0));
  points.push_back(Polyhedron::point(0.209,1.0812,0));
  points.push_back(Polyhedron::point(0.22,1.0812,0));
  points.push_back(Polyhedron::point(0.22,1.06,0));

  can_sup.set_points(points,50);
}

void Scene::draw(DrawMode mode) const{
  bool texture_status = active_texture;

  _vertex4<float> material0_ambient(0,0,0,1);
  _vertex4<float> material0_diffuse(0.1,0.1,0.1,1);
  _vertex4<float> material0_specular(0.5,0.5,0.5,0);

  _vertex4<float> material1_ambient(0,0,0,1);
  _vertex4<float> material1_diffuse(0.8,0.8,0.8,1);
  _vertex4<float> material1_specular(0.6,0.6,0.6,1);

  _vertex4<float> material2_ambient(0,0,0,1);
  _vertex4<float> material2_diffuse(0.6,0.6,0.6,1);
  _vertex4<float> material2_specular(0.6,0.6,0.6,1);

  glInitNames();
  glPushName(1);

  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,chess_texture -> tamX(),chess_texture -> tamY(),0,GL_RGB,GL_UNSIGNED_BYTE, (GLvoid *) (chess_texture -> leerPixels()));
  glPushMatrix();
  // No sé por qué pero es necesario invertir el tablero para que la luz
  // sea coherente.
  glRotatef(180,0,0,1);
  board.draw(mode);
  glPopMatrix();

  glPushName(2);

  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,grass_texture -> tamX(),grass_texture -> tamY(),0,GL_RGB,GL_UNSIGNED_BYTE, (GLvoid *) (grass_texture -> leerPixels()));
  glPushMatrix();
  glTranslatef(0,-0.01,0);
  glScaled(8,8,8);
  board.draw(mode);
  glPopMatrix();

  glPushName(3);

  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,stars_texture -> tamX(),stars_texture -> tamY(),0,GL_RGB,GL_UNSIGNED_BYTE, (GLvoid *) (stars_texture -> leerPixels()));
  glPushMatrix();
  glScaled(8,8,8);
  sphere.draw(mode);
  glPopMatrix();

  glPushName(4);

  glPushMatrix();
  glTranslatef(0.8,0.2,0.8);
  glRotatef(180,1,0,0);
  glRotatef(-90,0,1,0);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,can_texture -> tamX(),can_texture -> tamY(),0,GL_RGB,GL_UNSIGNED_BYTE, (GLvoid *) (can_texture -> leerPixels()));
  glScaled(0.15,0.3,0.15);
  can_mid.draw(mode);
  glPopMatrix();

  active_texture = false;

  glMaterialfv(GL_FRONT,GL_AMBIENT, (GLfloat *) &material2_ambient);
  glMaterialfv(GL_FRONT,GL_DIFFUSE, (GLfloat *) &material2_diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR, (GLfloat *) &material2_specular);
  glMaterialf(GL_FRONT,GL_SHININESS,10);

  glPushName(5);

  glPushMatrix();
  glTranslatef(0.8,-0.02,0.8);
  glScaled(0.35,0.35,0.35);
  can_sup.draw(mode);
  glPopMatrix();

  glMaterialfv(GL_FRONT,GL_AMBIENT, (GLfloat *) &material0_ambient);
  glMaterialfv(GL_FRONT,GL_DIFFUSE, (GLfloat *) &material0_diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR, (GLfloat *) &material0_specular);
  glMaterialf(GL_FRONT,GL_SHININESS,50);

  glPushName(6);

  glPushMatrix();
  glTranslatef(-0.19,0.075,0.2);
  glScaled(0.05,0.05,0.05);
  pawn.draw(mode);
  glPopMatrix();

  glMaterialfv(GL_FRONT,GL_AMBIENT, (GLfloat *) &material1_ambient);
  glMaterialfv(GL_FRONT,GL_DIFFUSE, (GLfloat *) &material1_diffuse);
  glMaterialfv(GL_FRONT,GL_SPECULAR, (GLfloat *) &material1_specular);
  glMaterialf(GL_FRONT,GL_SHININESS,5);

  glPushName(7);

  glPushMatrix();
  glTranslatef(0.2,0.075,-0.19);
  glScaled(0.05,0.05,0.05);
  pawn.draw(mode);
  glPopMatrix();

  active_texture = texture_status;
}
