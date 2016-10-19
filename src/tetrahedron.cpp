#include "tetrahedron.hpp"

// -----------------------------------------------------------------------------
// Implementación
// -----------------------------------------------------------------------------

Tetrahedron::Tetrahedron(){
	/*
	 * Genera un tetraedro en el espacio.
	 */
	point point;

	float base_height = -0.3;
	float top_height = 0.6;

	points.resize(4);
	faces.resize(4);

	point.x = -0.5;
	point.y = 0;
	point.z = base_height;
	points[0] = point;

	point.x = 0.5;
	point.y = 0.5;
	point.z = base_height;
	points[1] = point;

	point.x = 0.5;
	point.y = -0.5;
	point.z = base_height;
	points[2] = point;

	point.x = 0;
	point.y = 0;
	point.z = top_height;
	points[3] = point;

	generate_faces();
}

// -----------------------------------------------------------------------------

// Prec: init_points.size() == 4
Tetrahedron::Tetrahedron( const vector_points & init_points ){
	/*
	 * Genera un tetraedro a partir de un vector de puntos.
	 */
	points = init_points;
	faces.resize(4);

	generate_faces();
}

// -----------------------------------------------------------------------------

void Tetrahedron::generate_faces(){
	/*
	 * Genera las caras de un tetraedro.
	 *
	 * Prec: vector_caras.size() == Caras del tetraedro (4)
	 */
	face face;
	face.x = 0;
	face.y = 1;
	face.z = 3;
	faces[0] = face;

	face.x = 0;
	face.y = 3;
	face.z = 2;
	faces[1] = face;

	face.x = 0;
	face.y = 1;
	face.z = 2;
	faces[2] = face;

	face.x = 1;
	face.y = 2;
	face.z = 3;
	faces[3] = face;

}
