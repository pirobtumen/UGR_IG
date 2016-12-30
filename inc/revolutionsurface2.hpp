// Informática Gráfica
//
// Alberto Sola - 2016
// -----------------------------------------------------------------------------


#ifndef __REV_SURFACE_2
#define __REV_SURFACE_2

#include "board.hpp"
#include <math.h>

#define PI 3.1415

/*
  Revolution Surface 2
  ==============================================================================

  Revolution Surface that supports textures.

  The vertex of a revolution object can be stored the same way a board stores
  the data. Imagine a 4x4 board:

  Abstract Data Type          Representation

     0  1  2  3
     4  5  6  7         -->   0 1 2 3, 4 5 6 7, ....
     8  9  10 11
     12 13 14 15

  The revolution object is also a board, but it's curved. So we only have
  to store the profile points in the first line, and generate the others
  like if it were a board.

*/
class RevolutionSurface2 : public Board{
protected:
  unsigned int profile_length;

private:
  void calc_texture_vertex(unsigned int divisions);
  void generate_faces(unsigned int num_divisions);
  void spin_profile(unsigned int num_divisions);

public:
  RevolutionSurface2();
  RevolutionSurface2( const vector_points & points );
  RevolutionSurface2( const vector_points & points, unsigned int num_divisions );

  void set_points( const vector_points & points, unsigned int divisions = 10 );
  void spin( unsigned int num_divisions );
};

// -----------------------------------------------------------------------------

#endif
