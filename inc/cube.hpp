// Informática Gráfica
//
// Alberto Sola - 2016
// -----------------------------------------------------------------------------

#ifndef __CUBE_HPP
#define __CUBE_HPP

#include "polyhedron.hpp"

// -----------------------------------------------------------------------------

/*
 * Cubo
 * ==============
 *
 * Clase base: Model
 *
 * TDA para representar un cubo en el espacio.
 * El contenedor de puntos almacena los vértices del cubo.
 *
 * Vértices: 8.
 * Caras: 12.
 *
 * Para generar automáticamente las caras a partir de los vértices,
 * el orden de los vértices en el contenedor ha de ser el siguiente.
 *
 *        /1*\
 *     /       \
 *  0*\          *5
 *  |   \     -/ |
 *  |    4*-/    |
 *  |     |      |
 *  |     |      *7
 *  2*\   |   -/
 *      \6*-/
 */
class Cube : public Polyhedron{
public:


	// Constructores
	//----------------------------------------------------------------------------
	Cube();
	Cube( const vector_points & init_points );

	// Métodos abstractos
	//----------------------------------------------------------------------------
	void generate_faces();

};

#endif
