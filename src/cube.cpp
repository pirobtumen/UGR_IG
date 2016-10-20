// Informática Gráfica
//
// Alberto Sola - 2016
// -----------------------------------------------------------------------------

#include "cube.hpp"

// -----------------------------------------------------------------------------
// Implementación
// -----------------------------------------------------------------------------

Cube::Cube(){
	/*
	 * Genera un cubo en el espacio.
	 */
	points.resize(8);
	faces.resize(12);

	point p0(-0.5,0.5,-0.5);
	point p1(0.5,0.5,-0.5);
	point p2(-0.5,-0.5,-0.5);
	point p3(0.5,-0.5,-0.5);

	point p4(-0.5,0.5,0.5);
	point p5(0.5,0.5,0.5);
	point p6(-0.5,-0.5,0.5);
	point p7(0.5,-0.5,0.5);

	points[0] = p0;
	points[1] = p1;
	points[2] = p2;
	points[3] = p3;
	points[4] = p4;
	points[5] = p5;
	points[6] = p6;
	points[7] = p7;

	generate_faces();
}

// -----------------------------------------------------------------------------

// Prec: init_points.size() == 8
Cube::Cube( const vector_points & init_points ){
	/*
	 * Genera un cubo a partir de un vector de puntos.
	 */
	points = init_points;

	generate_faces();
}

// -----------------------------------------------------------------------------

void Cube::generate_faces(){
	/*
	 * Genera las caras automáticamente a partir de los vértices.
	 *
	 * Prec: points.size() == 8
	 */

	face face;

	face.x = 0;
	face.y = 2;
	face.z = 6;
	faces[0] = face;

	face.x = 0;
	face.y = 6;
	face.z = 4;
	faces[1] = face;

	face.x = 4;
	face.y = 6;
	face.z = 7;
	faces[2] = face;

	face.x = 4;
	face.y = 7;
	face.z = 5;
	faces[3] = face;

	face.x = 5;
	face.y = 7;
	face.z = 3;
	faces[4] = face;

	face.x = 5;
	face.y = 3;
	face.z = 1;
	faces[5] = face;

	face.x = 1;
	face.y = 3;
	face.z = 2;
	faces[6] = face;

	face.x = 1;
	face.y = 2;
	face.z = 0;
	faces[7] = face;

	face.x = 0;
	face.y = 5;
	face.z = 1;
	faces[8] = face;

	face.x = 0;
	face.y = 4;
	face.z = 5;
	faces[9] = face;

	face.x = 2;
	face.y = 3;
	face.z = 7;
	faces[10] = face;

	face.x = 2;
	face.y = 7;
	face.z = 6;
	faces[11] = face;

}

// -----------------------------------------------------------------------------
