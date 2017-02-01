#include "revolutionsurface2.hpp"

// -----------------------------------------------------------------------------

RevolutionSurface2::RevolutionSurface2(){}

// -----------------------------------------------------------------------------

RevolutionSurface2::RevolutionSurface2(const vector_points & points){
  set_points(points);
}

// -----------------------------------------------------------------------------

RevolutionSurface2::RevolutionSurface2(const vector_points & points, unsigned int num_divisions){
  set_points(points,num_divisions);
}

// -----------------------------------------------------------------------------

void RevolutionSurface2::spin_profile(unsigned int num_divisions){
  /*
    Rotate the profile 'num_divisions' times.
  */
  double jump = (double)(2*M_PI)/num_divisions;
  double angle = jump;
  double radius;

  point new_point;

  for(unsigned int n = 1; n < num_divisions; n++){

    for(unsigned int i = 0; i < profile_length; i++){
      radius = sqrt(points[i].x*points[i].x + points[i].z*points[i].z);


      new_point.x = cos(angle)*radius;
      new_point.y = points[i].y;
      new_point.z = sin(angle)*radius;

      points.push_back(new_point);
    }

    angle += jump;
  }

  // Repeat the first profile
  for(int i = 0; i < profile_length; i++)
    points.push_back(points[i]);

}

// -----------------------------------------------------------------------------

void RevolutionSurface2::generate_faces(unsigned int num_divisions){
  /*
    Genereate the triangle mesh as if it were a board.
  */
  int max_index = profile_length;
  int stop = profile_length*num_divisions - 1;  // Skip the last line
  face f;
  int i = 0;
  while(i < stop){
    // Skip the last vertex of each line
    if( (i+1)%max_index == 0)
      i++;

    f._0 = i+1+max_index;
    f._1 = i+1;
    f._2 = i;

    // Add if the area is not 0
    if(heron_formula( points[f._0], points[f._1], points[f._2]) != 0)
      faces.push_back(f);

    f._0 = i;
    f._1 = i+max_index;
    f._2 = i+max_index+1;

    // Add if the area is not 0
    if(heron_formula( points[f._0], points[f._1], points[f._2]) != 0)
      faces.push_back(f);

    i++;

  }
}

// -----------------------------------------------------------------------------

void RevolutionSurface2::set_points(const vector_points & new_points, unsigned int divisions){
  /*
    Set the first progile with angle 0.
  */
  double radius;
  point rotated_point;

  profile_length = new_points.size();

  for(unsigned int i = 0; i < profile_length; i++){
    // Rotate each point to 0º
    radius = sqrt(new_points[i].x*new_points[i].x + new_points[i].z*new_points[i].z);

    rotated_point.x = radius;
    rotated_point.y = new_points[i].y;
    rotated_point.z = 0;

    points[i] = rotated_point;
  }

  spin(divisions);
}

// -----------------------------------------------------------------------------

void RevolutionSurface2::spin(unsigned int num_divisions){
  /*
    Spin the profile.
  */
  // Reset
  points.resize(profile_length);
  faces.clear();
  face_normals.clear();
  vertex_normals.clear();
  texture_vertex.clear();

  // Generate object
  spin_profile(num_divisions);
  generate_faces(num_divisions);
  calc_face_normal();
  calc_vertex_normal();
  calc_texture_vertex(num_divisions);
}

// -----------------------------------------------------------------------------

void RevolutionSurface2::calc_texture_vertex(unsigned int divisions){
  /*
    Calcule each vertex the same way as the board.
  */

  // Select a region of the board
  const int BOARD_START_X = 0;
  const int BOARD_START_Y = 0;
  const int BOARD_END_X = profile_length - 1;
  const int BOARD_END_Y = divisions;

  // Select a region of the texture
  const double TEXTURE_START_U = 0;
  const double TEXTURE_START_V = 0;
  const double TEXTURE_END_U = 1;
  const double TEXTURE_END_V = 1;

  // Jump between two texture points
  const double JUMP_U = (double)(TEXTURE_END_U - TEXTURE_START_U)/profile_length;
  const double JUMP_V = (double)(TEXTURE_END_V - TEXTURE_START_V)/divisions;

  const double max_u = BOARD_END_X-BOARD_START_X+(1-TEXTURE_END_U);
  const double max_v = BOARD_END_Y-BOARD_START_Y+(1-TEXTURE_END_V);
  double u;
  double v;

  // Generate texture points
  for(int y = 0; y <= divisions; y++){
    for(int x = 0; x < profile_length; x++){
      if(x < BOARD_START_X || x > BOARD_END_X || y < BOARD_START_Y || y > BOARD_END_Y){
        texture_vertex.push_back(std::make_pair(-1,-1));
      }
      else{
        u = (((x-BOARD_START_X)/max_u)+TEXTURE_START_U)/(1+1-TEXTURE_END_U+TEXTURE_START_U);
        v = (((y-BOARD_START_Y)/max_v)+TEXTURE_START_V)/(1+1-TEXTURE_END_V+TEXTURE_START_V);

        texture_vertex.push_back(std::make_pair(1-v,u)); // Transpose + Invert X
      }
    }
  }

}

// -----------------------------------------------------------------------------
