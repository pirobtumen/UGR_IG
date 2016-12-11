#include "board.hpp"

// -----------------------------------------------------------------------------

Board::Board(){
  generate_board(10);
}

// -----------------------------------------------------------------------------

void Board::generate_board(int num_squares){
  points.clear();
  faces.clear();
  face_normals.clear();
  vertex_normals.clear();
  texture_vertex.clear();

  generate_vertex(num_squares);
  generate_faces(num_squares);
  calc_face_normal();
  calc_vertex_normal();
  calc_texture_vertex(num_squares);
}

// -----------------------------------------------------------------------------

void Board::calc_texture_vertex(int num_squares){
  double jump = 1.0/num_squares; // Mismo para X y Z

  for(double v = 0; (1-v) >= -0.001f; v += jump) // Z
    for(double u = 0; (1-u) >= -0.001f; u += jump) // X
      texture_vertex.push_back(std::make_pair(u,v));

}

// -----------------------------------------------------------------------------

void Board::draw_texture(){
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_TRIANGLES);

  for(int i = 0; i < faces.size(); i++){
    glTexCoord2f(texture_vertex[faces[i]._0].first,texture_vertex[faces[i]._0].second);
    glVertex3fv((GLfloat *) &points[faces[i]._0]);
    glTexCoord2f(texture_vertex[faces[i]._1].first,texture_vertex[faces[i]._1].second);
    glVertex3fv((GLfloat *) &points[faces[i]._1]);
    glTexCoord2f(texture_vertex[faces[i]._2].first,texture_vertex[faces[i]._2].second);
    glVertex3fv((GLfloat *) &points[faces[i]._2]);
  }

  glEnd();
  glDisable(GL_TEXTURE_2D);
}

// -----------------------------------------------------------------------------

void Board::generate_vertex(int num_squares){
  double x_jump = 1.0/num_squares;
  double z_jump = 1.0/num_squares;

  point p;
  point p00(-0.5f,0,-0.5f);
  point pnn(0.5f,0,0.5f);

  p.x = -0.5f;
  p.y = 0;
  p.z = -0.5f;


  for(unsigned int z = 0; z <= num_squares; z++){
    for(unsigned int x = 0; x <= num_squares; x++){
      points.push_back(p);
      p.x += x_jump;
    }

    p.x = -0.5f;
    p.z += z_jump;
  }

}

// -----------------------------------------------------------------------------

void Board::generate_faces(int num_squares){
  int max_index = (num_squares+1);
  int stop = (num_squares+1)*num_squares - 1;
  face f;
  int i = 0;
  while(i < stop){
    if( (i+1)%max_index == 0)
      i++;

    f._0 = i+1+max_index;
    f._1 = i+1;
    f._2 = i;

    faces.push_back(f);

    f._0 = i;
    f._1 = i+max_index;
    f._2 = i+max_index+1;

    faces.push_back(f);

    i++;

  }
}

// -----------------------------------------------------------------------------
