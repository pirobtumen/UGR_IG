// Informática Gráfica
//
// Alberto Sola - 2016

// -----------------------------------------------------------------------------

#ifndef _REV_SURFACE
#define _REV_SURFACE

#include "polyhedron.hpp"
#include <math.h>

#define PI 3.1415

class RevolutionSurface : public Polyhedron{
private:
  unsigned int surface_points_number;

  void generate_points( unsigned int num_surfaces );
  void generate_surfaces( unsigned int num_surfaces );
  void generate_covers( unsigned int num_surfaces );

public:
  RevolutionSurface();
  RevolutionSurface( const vector_points & points );
  RevolutionSurface( const vector_points & points, unsigned int num_surfaces );

  void set_points( const vector_points & points );
  void spin( unsigned int num_surfaces );
};

// -----------------------------------------------------------------------------

#endif
