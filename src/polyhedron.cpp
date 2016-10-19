#include "polyhedron.hpp"

// -----------------------------------------------------------------------------
// Implementación
// -----------------------------------------------------------------------------

Polyhedron::Polyhedron(){

}

// -----------------------------------------------------------------------------

void Polyhedron::draw_triangles(GLenum mode,int start=0, int interval=1) const{
	/*
	 * Dibuja los tríangulos del modelo.
	 *
	 * Dependiendo del modo, se dibujarán líneas o caras.
	 *
	 * GLenum mode: GL_LINE o GL_FILL.
	 */
	glPolygonMode(GL_FRONT_AND_BACK, mode);

	int num_faces = get_num_faces();

	glBegin(GL_TRIANGLES);

	for( int i = start; i < num_faces; i += interval ){
		glVertex3fv( (GLfloat *) &points[faces[i].x] );
		glVertex3fv( (GLfloat *) &points[faces[i].y] );
		glVertex3fv( (GLfloat *) &points[faces[i].z] );
	}

	glEnd();
}

// -----------------------------------------------------------------------------

void Polyhedron::add_face(index a, index b, index c){
	faces.push_back( Polyhedron::face(a,b,c) );
}

// -----------------------------------------------------------------------------

void Polyhedron::set_num_faces(unsigned int num){
	faces.reserve(num);
}

// -----------------------------------------------------------------------------

void Polyhedron::clear(){
	Object3D::clear();

	faces.clear();
}

// -----------------------------------------------------------------------------

void Polyhedron::set_face(index pos, index a, index b, index c){
	/*
	 * Establece una cara del modelo.
	 *
	 * Prec: pos < vector_faces.size()
	 */
	faces[pos][0] = a;
	faces[pos][1] = b;
	faces[pos][2] = c;
}

// -----------------------------------------------------------------------------

const Polyhedron::vector_faces & Polyhedron::get_faces() const{
	/*
	 * Devuelve las caras del modelo.
	 */
	return faces;
}

// -----------------------------------------------------------------------------

int Polyhedron::get_num_faces() const{
	/*
	 * Devuelve el número de caras.
	 */
	return faces.size();
}

// -----------------------------------------------------------------------------

void Polyhedron::draw_edges(double r, double g, double b) const{
	/*
	 * Dibuja las líneas (aristas) del modelo.
	 */
	glColor3f(r,g,b);
	draw_triangles(GL_LINE);
}

// -----------------------------------------------------------------------------

void Polyhedron::draw_surfaces(double r, double g, double b) const{
	/*
	 * Dibuja las caras del modelo.
	 */
	glColor3f(r,g,b);
	draw_triangles(GL_FILL);
}

// -----------------------------------------------------------------------------

void Polyhedron::draw_chess() const{
	/*
	 * Dibuja las caras alternando el color de la cara.
	 */

	int num_faces = get_num_faces();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glColor3f(0,1,0);

	draw_triangles(GL_FILL,0,2);

	glColor3f(1,0,0);

	draw_triangles(GL_FILL,1,2);

	glEnd();
}

// -----------------------------------------------------------------------------

void Polyhedron::draw_all() const{
	/*
	 * Dibuja las caras alternando el color de la cara.
	 */

	 draw_points(0,0,0);
	 draw_edges(0,0,1);
	 draw_surfaces(1,0,1);
}
