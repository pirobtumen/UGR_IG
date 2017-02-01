#include "scene2.hpp"

Scene2::Scene2(){
  char filename[] = "./modelos/beethoven.ply";
  beethoven.load_ply(filename);
  selected_element = 0;
}

void Scene2::draw(DrawMode mode) const{

  const double start_x = -15;
  const double start_y = -15;
  const int num_model = 4;
  const double jump = 10;

  _vertex4<float> material1_ambient(0,0,0.8,1);
  _vertex4<float> material1_diffuse(0,0,1,1);
  _vertex4<float> material1_specular(0.6,0.6,0.6,1);

  int num_element;

  for(int x = 0; x < num_model; x++)
    for(int y = 0; y < num_model; y++){
      num_element = x*num_model + y + 1;
      glLoadName(num_element);

      glPushMatrix();
      glTranslatef(start_x + x*jump,0,0);
      glTranslatef(0,0,start_y + y*jump);
      if(num_element == selected_element){
        glMaterialfv(GL_FRONT,GL_AMBIENT, (GLfloat *) &material1_ambient);
        glMaterialfv(GL_FRONT,GL_DIFFUSE, (GLfloat *) &material1_diffuse);
        glMaterialfv(GL_FRONT,GL_SPECULAR, (GLfloat *) &material1_specular);
        glMaterialf(GL_FRONT,GL_SHININESS,5);
        beethoven.draw(mode);
        set_texture_material();
      }
      else
        beethoven.draw(mode);
      glPopMatrix();
    }


}

void Scene2::set_selected(int selected){
  selected_element = selected;
}
