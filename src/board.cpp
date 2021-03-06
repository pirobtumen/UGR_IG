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
  bool INV_X = false;
  bool INV_Y = false;

  // Select a region of the board
  const int BOARD_START_X = 0;
  const int BOARD_START_Y = 0;
  const int BOARD_END_X = num_squares;
  const int BOARD_END_Y = num_squares;

  // Select a region of the texture
  const double TEXTURE_START_U = 0;
  const double TEXTURE_START_V = 0;
  const double TEXTURE_END_U = 1;
  const double TEXTURE_END_V = 1;

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
        u = (((x-BOARD_START_X)/max_u)+TEXTURE_START_U)/(1+1-TEXTURE_END_U+TEXTURE_START_U);
        v = (((y-BOARD_START_Y)/max_v)+TEXTURE_START_V)/(1+1-TEXTURE_END_V+TEXTURE_START_V);

        if(INV_X)
          u = 1 - u;

        if(INV_Y)
          v = 1 - v;

        texture_vertex.push_back(std::make_pair(u,v));
      }
    }
  }

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
