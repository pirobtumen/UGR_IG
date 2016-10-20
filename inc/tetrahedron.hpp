// Informática Gráfica
//
// Alberto Sola - 2016
// -----------------------------------------------------------------------------

#ifndef __TETRAHEDRON_HPP
#define __TETRAHEDRON_HPP

#include "polyhedron.hpp"

// -----------------------------------------------------------------------------

/*
 * Tetraedro
 * ============
 *
 * Clase base: Model
 *
 * TDA para representar un tetraedro en el espacio.
 *
 * Vértices: 4.
 * Caras: 4.
 *
 * Para generar automáticamente las caras, los vértices han de estar
 * en la siguiente disposición:
 *
 *      d
 *           c
 *
 * a
 *         b
 *
 * Base: A,B,C
 * Altura: D
 * Vector de vértices [A,B,C,D]
 */
class Tetrahedron : public Polyhedron{
public:

	// Constructores
	//----------------------------------------------------------------------------
	Tetrahedron();
	Tetrahedron( const vector_points & init_points );

	// Métodos abstractos
	//----------------------------------------------------------------------------
	void generate_faces();

};

// -----------------------------------------------------------------------------

#endif
