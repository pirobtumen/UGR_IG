#include "board.hpp"

// -----------------------------------------------------------------------------

Board::Board(){
  /*
    Generate the default size board.
  */
  generate_board(10);
}

// -----------------------------------------------------------------------------

void Board::generate_board(int num_squares){
  /*
    Generate a board of N*N squares.
  */
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
  // Select a region of the board
  const int BOARD_START_X = 1;
  const int BOARD_START_Y = 1;
  const int BOARD_END_X = num_squares-1;
  const int BOARD_END_Y = num_squares-1;

  // Select a region of the texture
  const double TEXTURE_START_U = 0.25;
  const double TEXTURE_START_V = 0.25;
  const double TEXTURE_END_U = 0.75;
  const double TEXTURE_END_V = 0.75;

  // Jump between two texture points
  const double JUMP_V = (double)(TEXTURE_END_V - TEXTURE_START_V)/num_squares;
  const double JUMP_U = (double)(TEXTURE_END_U - TEXTURE_START_U)/num_squares;

  const double max_u = BOARD_END_X-BOARD_START_X;
  const double max_v = BOARD_END_Y-BOARD_START_Y+(1-TEXTURE_END_V);
  double u;
  double v;

  // Generate texture points
  for(int y = 0; y <= num_squares; y++){
    for(int x = 0; x <= num_squares; x++){
      if(x < BOARD_START_X || x > BOARD_END_X || y < BOARD_START_Y || y > BOARD_END_Y){
        texture_vertex.push_back(std::make_pair(-1,-1));
      }
      else{
        u = x-BOARD_START_X;
        v = y-BOARD_START_Y;

        texture_vertex.push_back(std::make_pair(
          ((u/max_u)+TEXTURE_START_U)/(1+1-TEXTURE_END_U+TEXTURE_START_U),
          ((v/max_v)+TEXTURE_START_V)/(1+1-TEXTURE_END_V+TEXTURE_START_V)
        ));
      }
    }
  }

}

// -----------------------------------------------------------------------------

void Board::draw_texture(){
  /*
    Draw the texture.
  */
  glEnable(GL_TEXTURE_2D);
  glBegin(GL_TRIANGLES);

  for(int i = 0; i < faces.size(); i++){
    if( texture_vertex[faces[i]._0].first != -1 &&
        texture_vertex[faces[i]._1].first != -1 &&
        texture_vertex[faces[i]._2].first != -1    ){
      glTexCoord2f(texture_vertex[faces[i]._0].first,texture_vertex[faces[i]._0].second);
      glVertex3fv((GLfloat *) &points[faces[i]._0]);
      glTexCoord2f(texture_vertex[faces[i]._1].first,texture_vertex[faces[i]._1].second);
      glVertex3fv((GLfloat *) &points[faces[i]._1]);
      glTexCoord2f(texture_vertex[faces[i]._2].first,texture_vertex[faces[i]._2].second);
      glVertex3fv((GLfloat *) &points[faces[i]._2]);
    }

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
