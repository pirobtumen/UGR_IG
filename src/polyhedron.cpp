// Informática Gráfica
//
// Alberto Sola - 2016
// -----------------------------------------------------------------------------

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

	switch (light_mode) {
		case FLAT:
			for( int i = start; i < num_faces; i += interval ){
				glNormal3fv( (GLfloat *) &face_normals[i] );
				glVertex3fv( (GLfloat *) &points[faces[i].x] );
				glVertex3fv( (GLfloat *) &points[faces[i].y] );
				glVertex3fv( (GLfloat *) &points[faces[i].z] );
			}
			break;

		case SMOOTH:
			for( int i = start; i < num_faces; i += interval ){
				glNormal3fv( (GLfloat *) &vertex_normals[faces[i].x] );
				glVertex3fv( (GLfloat *) &points[faces[i].x] );
				glNormal3fv( (GLfloat *) &vertex_normals[faces[i].y] );
				glVertex3fv( (GLfloat *) &points[faces[i].y] );
				glNormal3fv( (GLfloat *) &vertex_normals[faces[i].z] );
				glVertex3fv( (GLfloat *) &points[faces[i].z] );
			}
			break;

		case NONE:
			for( int i = start; i < num_faces; i += interval ){
				glVertex3fv( (GLfloat *) &points[faces[i].x] );
				glVertex3fv( (GLfloat *) &points[faces[i].y] );
				glVertex3fv( (GLfloat *) &points[faces[i].z] );
			}
			break;
	}

	glEnd();
}

// -----------------------------------------------------------------------------

void Polyhedron::calc_face_normal(){
	/*
		Calcula las normales de cada cara.
	*/
	unsigned int num_faces = faces.size();
	point normal;
	point a;
	point b;
	float module;

	face_normals.clear();
	face_normals.resize(num_faces);

	for(unsigned int i = 0; i < num_faces; i++){
		// Dado un triángulo tomamos dos vectores con un vértice en común
		a = points[faces[i]._0] - points[faces[i]._1];
		b = points[faces[i]._2] - points[faces[i]._1];

		// Producto escalar

		/*
			El vector normal puede tener dos sentidos. Uno estará iluminado y el otro
			no. Por tanto si al hacer un producto escalar las caras está oscuras,
			cambiamos al otro.

			Si hay caras iluminadas y otras no, esto es por el orden de los vértices
			de cara cada.

			1. Objetos de revolución: no es lo mismo instroducir el perfil de arriba
			hacia abajo que del revés. Uno se iluminará y el otro no.

			2. En este caso, tal y cómo se calculan las normales, hay que cambiar
			x por z en las caras no iluminadas al crear dichos objetos.
		*/
		//normal = a.cross_product(b);
		normal = b.cross_product(a);
		normal /= normal.module();

		face_normals[i] = normal;
	}
}

// -----------------------------------------------------------------------------

void Polyhedron::calc_vertex_normal(){
	/*
		Calcula las normales de cada vértice. O(n)

		Recorremos el vector de caras, y acumulamos la normal de dicha cara en
		la futura normal de cada vértice de dicha cara.

	*/
	point zero(0,0,0);
	unsigned int num_vertex = points.size();
	unsigned int num_faces = faces.size();

	vertex_normals.clear();

	// Inicializamos
	vertex_normals.resize(num_vertex);

	for(unsigned int i = 0; i < num_vertex; i++)
		vertex_normals[i] = zero;


	// Acumulamos
	for(unsigned int i = 0; i < num_faces; i++){
		vertex_normals[faces[i]._0] += face_normals[i];
		vertex_normals[faces[i]._1] += face_normals[i];
		vertex_normals[faces[i]._2] += face_normals[i];
	}

	// Normalizamos
	for(unsigned int i = 0; i < num_vertex; i++)
		vertex_normals[i] /= vertex_normals[i].module();

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

void Polyhedron::draw_points(double r, double g, double b) const{
	Object3D::draw_points(r,g,b);
}


// -----------------------------------------------------------------------------

void Polyhedron::draw_edges(double r, double g, double b) const{
	/*
	 * Dibuja las líneas (aristas) del modelo.
	 */
	glColor3f(r,g,b);
	glDisable(GL_LIGHTING);
	draw_triangles(GL_LINE);
	glEnable(GL_LIGHTING);
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

	glColor3f(0.03,0.54,0.73);

	draw_triangles(GL_FILL,0,2);

	glColor3f(0.03,0.22,0.52);

	draw_triangles(GL_FILL,1,2);

	glEnd();
}

// -----------------------------------------------------------------------------

void Polyhedron::draw_all() const{
	/*
	 * Dibuja las caras alternando el color de la cara.
	 */

	 draw_points();
	 draw_edges(0.03,0.54,0.73);
	 draw_surfaces();
}

// -----------------------------------------------------------------------------

void Polyhedron::draw(DrawMode mode) const{

	switch (mode) {
		case ALL:
			draw_all();
			break;
		case CHESS:
			draw_chess();
			break;
		case SURFACES:
			draw_surfaces();
			break;
		case EDGES:
			draw_edges();
			break;
		case POINTS:
			draw_points();
			break;
	}

}

// -----------------------------------------------------------------------------

bool Polyhedron::has_degenerate_triangles() const{

	unsigned int size = faces.size();
	bool degenerate = false;

	double area;

	for( unsigned int i = 0; i < size && !degenerate; i++ ){
		area = heron_formula( points[faces[i]._0],
													points[faces[i]._1],
													points[faces[i]._2]);

		if( area == 0 )
			degenerate = true;

	}

	return degenerate;
}

// -----------------------------------------------------------------------------

void Polyhedron::get_max_min_triangle_area() const{

	unsigned int size = faces.size();

	int max_ind = 0;
	int min_ind = 0;

	double area;

	double max_area = heron_formula( points[faces[0]._0],
												points[faces[0]._1],
												points[faces[0]._2]);;
	double min_area = heron_formula( points[faces[1]._0],
												points[faces[1]._1],
												points[faces[1]._2]);;

	for( unsigned int i = 2; i < size; i++ ){
		area = heron_formula( points[faces[i]._0],
													points[faces[i]._1],
													points[faces[i]._2]);

		if( area > max_area ){
			max_area = area;
			max_ind = i;
		}
		else if( area < min_area){
			min_area = area;
			min_ind = i;
		}

	}

	cout << min_ind << " - " << min_area << endl;
	cout << max_ind << " - " << max_area << endl;
}

// -----------------------------------------------------------------------------
