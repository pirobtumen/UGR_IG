// Informática Gráfica
//
// Alberto Sola - 2016
// -----------------------------------------------------------------------------

#ifndef __POLYHEDRON_HPP
#define __POLYHEDRON_HPP


#include <vector>
#include "vertex.h"
#include "object3d.hpp"
#include <GL/glut.h>

// -----------------------------------------------------------------------------

/*
 * Poliedro
 * ================
 *
 * TDA para representar un poliedro en el espacio.
 *
 * Para ello almacena los vértices de dicho poliedro en un contenedor.
 * En otro contenedor almacena las caras (mediante triángulos) que lo forman.
 *
 * Para generar un nuevo modelo, será necesario heredar esta clase
 * e implementar el método abstracto "generate_faces".
 *
 */
class Polyhedron : public Object3D{
public:
	typedef _vertex3<index> face;
	typedef vector<face> vector_faces;

protected:
	vector_faces faces;

	void draw_triangles(GLenum mode, int start, int interval) const;

public:

	// Constructores
	// ---------------------------------------------------------------------------
	Polyhedron();

	// Modificadores
	// ---------------------------------------------------------------------------
	void add_face(index a, index b, index c);
	void set_face(index pos, index a, index b, index c);

	void set_num_faces(unsigned int num);
	void clear();

	// Consultores
	// ---------------------------------------------------------------------------
	const vector_faces & 		get_faces() const;
	int 										get_num_faces() const;

	// Dibujar
	// ---------------------------------------------------------------------------
	void draw_edges(double r=0, double g=0, double b=0) const;
	void draw_surfaces(double r=0, double g=0, double b=0) const;
	void draw_chess() const;
	void draw_all() const;
};

// -----------------------------------------------------------------------------

#endif
