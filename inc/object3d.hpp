// Informática Gráfica
//
// Práctica 1. Modelado de objetos.
//
// Alberto Sola - 2016

// -----------------------------------------------------------------------------

#ifndef __OBJECT3D_HPP
#define __OBJECT3D_HPP

#include <vector>
#include <GL/glut.h>
#include "vertex.h"

// -----------------------------------------------------------------------------

class Object3D{
public:
  typedef float coordinate;
	typedef unsigned int index;
	typedef _vertex3<coordinate> point;
  typedef vector<point> vector_points;

protected:
  vector_points points;

public:
  // Constructores
	// ---------------------------------------------------------------------------
  Object3D();

	// Modificadores
	// ---------------------------------------------------------------------------
  void add_point(coordinate x, coordinate y, coordinate z);
  void set_point(index pos, const point & point);

  void set_num_vertex(unsigned int num);

  void clear();

	// Consultores
	// ---------------------------------------------------------------------------
	const vector_points & 	get_points() const;
	int 										get_num_points() const;

  // Dibujar
  // ---------------------------------------------------------------------------
  void draw_points(double r=0, double g=0, double b=0) const;

};

// -----------------------------------------------------------------------------

#endif
