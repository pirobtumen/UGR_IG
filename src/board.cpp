#include "board.hpp"

Board::Board(){
  int num_squares = 5;
  int stop = (num_squares+1)*num_squares - 1;
  int max_index = (num_squares+1);
  float x_jump = 1.0/num_squares;
  float z_jump = 1.0/num_squares;

  face f;

  point p;
  point p00(-0.5,0,-0.5);
  point pnn(0.5,0,0.5);

  p.y = 0;

  for(float z = p00.z; z <= pnn.z; z += z_jump){
    for(float x = p00.x; x <= pnn.x; x += x_jump){
      p.x = x;
      p.z = z;

      points.push_back(p);
    }
  }

  // Caras
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

  calc_face_normal();
  calc_vertex_normal();
}
