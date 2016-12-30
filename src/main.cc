//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013-2016
//
// GPL
//**************************************************************************

// Alberto Sola - 2016

// Teclas:
//
// F1 - Tetraedro
// F2 - Cubo
//
// P - Puntos
// A - Aristas
// S - Sólido
// C - Ajedrez
// T - Puntos + Aristas + Sólidos

// Reducir los puntos del perfil X veces


#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include <iostream>

#include <vector>
#include "vertex.h"
#include "file_ply_stl.h"

#include "drawable.hpp"
#include "polyhedron.hpp"
#include "cube.hpp"
#include "tetrahedron.hpp"
#include "revolutionsurface.hpp"
#include "sphere.hpp"
#include "board.hpp"

#include "reguladorwatt.hpp"
#include "body.hpp"
#include "arm.hpp"
#include "arm2.hpp"
#include "base.hpp"
#include "piece.hpp"
#include "piecedoor.hpp"

#include "global.hpp"

#include "jpg_imagen.hpp"
#include "cube2.hpp"
#include "revolutionsurface2.hpp"
#include "scene.hpp"


// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=800,UI_window_height=800;


// ----------------------------------------------------------------------------
//
// CÓDIGO DEL ALUMNO
//
// ----------------------------------------------------------------------------

enum DrawItem { CUBE, TETRAHEDRON, FILE_MODEL, REVOLUTION, WATT, BOARD };
enum SelectIem { ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT };

const int SPIN_JUMP = 1;
unsigned int num_surfaces = 50;
bool need_spin = false;

Cube cube;
Cube2 cube2;
Tetrahedron tetrahedron;
Board board;

Polyhedron file_model;
Polyhedron file_model2;
Polyhedron file_model3;

//RevolutionSurface cylinder;
RevolutionSurface2 glass;
RevolutionSurface2 inv_glass;
RevolutionSurface2 cone;
RevolutionSurface2 tube;
RevolutionSurface2 pawn;
Sphere sphere;
Cylinder cylinder;

Watt watt;
Scene scene;

SelectIem selected_item = EIGHT;

DrawMode draw_mode = SURFACES;
DrawItem draw_item = REVOLUTION;

// Iluminación
// -----------------------------------------------------------------------------

int light0_angle = 0;
int light1_angle = 1;

GLfloat ambient_light[4] = {1,1,1,1};

float material0_ambient_strength = 0.4;
float material0_diffuse_strength = 0.5;
float material0_specular_strength = 0.2;

_vertex4<float> material0_ambient(0.8,0,0,1);
_vertex4<float> material0_diffuse(0.7,0,0,1);
_vertex4<float> material0_specular(0.5,0.5,0.5,0);

float material1_ambient_strength = 0.2;
float material1_diffuse_strength = 0.6;
float material1_specular_strength = 0.3;

_vertex4<float> material1_ambient(0,0,0.8,1);
_vertex4<float> material1_diffuse(0,0,0.8,1);
_vertex4<float> material1_specular(0.6,0.6,0.6,1);

_vertex4<float> light0_ambient(0.2,0.2,0.2,1);
_vertex4<float> light0_diffuse(0.8,0.8,0.8,1);
_vertex4<float> light0_specular(0.2,0.2,0.2,1);

_vertex4<float> light1_ambient(0.3,0.3,0.3,1);
_vertex4<float> light1_diffuse(0.6,0.6,0.6,1);
_vertex4<float> light1_specular(0.15,0.15,0.15,1);

// TODO: crear materiales
GLfloat light0_pos[4] = {0,10,0,1}; // Coordenadas homogéneas
GLfloat light1_pos[4] = {0,0,10,0}; // Coordenadas homogéneas

// Funciones
// -----------------------------------------------------------------------------

void read_polygon_from_file(char * filename, Polyhedron & model){
	_file_ply ply_reader;
	vector<float> vertex;
	vector<int> faces;

	unsigned int num_vertex;
	unsigned int num_faces;

	ply_reader.open(filename);
	ply_reader.read(vertex, faces);
	ply_reader.close();

	num_vertex = vertex.size();
	num_faces  = faces.size();

	model.clear();
	model.set_num_vertex(num_vertex/3);
	model.set_num_faces(num_faces/3);

	for( int i = 0; i < num_vertex; i+=3)
		model.add_point(vertex[i], vertex[i+1], vertex[i+2]);

	for( int i = 0; i < num_faces; i+=3)
		model.add_face(faces[i], faces[i+1], faces[i+2]);

	model.calc_face_normal();
	model.calc_vertex_normal();
}

// -----------------------------------------------------------------------------

void load_textures(){
	earth_texture = new jpg::Imagen("texturas/dia_8192.jpg");
	chess_texture = new jpg::Imagen("texturas/chess.jpg");
	stars_texture = new jpg::Imagen("texturas/stars.jpg");
	grass_texture = new jpg::Imagen("texturas/grass.jpg");
	can_texture = new jpg::Imagen("texturas/text-lata-1.jpg");

	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_DECAL);

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,earth_texture -> tamX(),earth_texture -> tamY(),0,GL_RGB,GL_UNSIGNED_BYTE, (GLvoid *) (earth_texture -> leerPixels()));
	//glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,chess_texture -> tamX(),chess_texture -> tamY(),0,GL_RGB,GL_UNSIGNED_BYTE, (GLvoid *) (chess_texture -> leerPixels()));
}

// -----------------------------------------------------------------------------

void update_model(){

	rotate_angle += max_rotate*speed/1000;

	if(rotate_angle > max_rotate)
		rotate_angle -= max_rotate;

	glutPostRedisplay();
}

// -----------------------------------------------------------------------------

void draw_object( const Drawable & obj ){

	obj.draw(draw_mode);

}

// -----------------------------------------------------------------------------

void draw(){
	/*
	 * Función encargada de dibujar un modelo.
	 */

	 // Recalcular los modelos generados por revolución si es necesario
 	if( need_spin ){
		sphere.spin(num_surfaces);
 		cylinder.spin(num_surfaces);
 		glass.spin(num_surfaces);
 		inv_glass.spin(num_surfaces);
 		cone.spin(num_surfaces);
 		tube.spin(num_surfaces);
 		pawn.spin(num_surfaces);

 		need_spin = false;
 	}

	glColor3f(0,0,0);
	glPointSize(4);

	switch (draw_item) {
		case CUBE:
			glPushMatrix();
				glTranslatef(0.8,0,0);
				draw_object(cube);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-0.8,0,0);
				draw_object(cube2);
			glPopMatrix();
			break;
		case TETRAHEDRON:
			draw_object(tetrahedron);
			break;
		case FILE_MODEL:

			switch (selected_item) {
				case ONE:
					draw_object(file_model);
					break;
				case TWO:
					draw_object(file_model2);
					break;
				case THREE:
					draw_object(file_model3);
					break;
				}
			break;

		case REVOLUTION:

			switch (selected_item) {
				case ONE:
					draw_object(cylinder);
					break;
				case TWO:
					draw_object(glass);
					break;
				case THREE:
					draw_object(inv_glass);
					break;
				case FOUR:
					draw_object(cone);
					break;
				case FIVE:
					draw_object(tube);
					break;
				case SIX:
					draw_object(sphere);
					break;
				case SEVEN:
					draw_object(pawn);
					break;
				case EIGHT:
					draw_object(scene);
					break;
			}

			break;

		case WATT:
			draw_object(watt);
			break;

		case BOARD:
			draw_object(board);
			break;
	}

}

// -----------------------------------------------------------------------------

void set_material0(){
	// Material por defecto
	glMaterialfv(GL_FRONT,GL_AMBIENT, (GLfloat *) &material0_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE, (GLfloat *) &material0_diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR, (GLfloat *) &material0_specular);
	glMaterialf(GL_FRONT,GL_SHININESS,50);
}

// -----------------------------------------------------------------------------

void set_material1(){
	// Material por defecto
	glMaterialfv(GL_FRONT,GL_AMBIENT, (GLfloat *) &material1_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE, (GLfloat *) &material1_diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR, (GLfloat *) &material1_specular);
	glMaterialf(GL_FRONT,GL_SHININESS,5);
}

// -----------------------------------------------------------------------------

void read_models(){
	char filename1[] = "./modelos/ant.ply";
	char filename2[] = "./modelos/big_porsche.ply";
	char filename3[] = "./modelos/dolphins.ply";

	file_model.load_ply(filename1);
	file_model2.load_ply(filename2);
	file_model3.load_ply(filename3);
}

// -----------------------------------------------------------------------------

void disable_lighting(){
	light_mode = NONE;
	glDisable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
}

// -----------------------------------------------------------------------------

void enable_lighting(){
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
}

// -----------------------------------------------------------------------------

void draw_light0(){
	glPushMatrix();
	glRotatef(light0_angle,0,0,1);
	glLightfv(GL_LIGHT0,GL_POSITION,(GLfloat *) &light0_pos);
	glPopMatrix();
}

// -----------------------------------------------------------------------------

void draw_light1(){
	glPushMatrix();
	glRotatef(light1_angle,0,1,0);
	glLightfv(GL_LIGHT1,GL_POSITION,(GLfloat *) &light1_pos);
	glPopMatrix();
}

// -----------------------------------------------------------------------------

void init_light(){
	/*
		Inicializamos los parámetros de iluminación
	*/
	material0_diffuse *= material0_diffuse_strength;
	material0_ambient *= material0_ambient_strength;
	material0_specular *= material0_specular_strength;

	material1_diffuse *= material1_diffuse_strength;
	material1_ambient *= material1_ambient_strength;
	material1_specular *= material1_specular_strength;

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambient_light);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);

	// Default mateiral
	set_material0();

	// Luz 0 - Posicional (w=0)
	glLightfv(GL_LIGHT1,GL_AMBIENT,(GLfloat *) &light0_ambient);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,(GLfloat *) &light0_diffuse);
	glLightfv(GL_LIGHT1,GL_SPECULAR,(GLfloat *) &light0_specular);
	draw_light0();

	// Luz 1 - Direccional (w=0)
	glLightfv(GL_LIGHT1,GL_POSITION,(GLfloat *) &light1_pos);
	glLightfv(GL_LIGHT1,GL_AMBIENT,(GLfloat *) &light1_ambient);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,(GLfloat *) &light1_diffuse);
	draw_light1();

	// Tipo de iluminación pr defecto
	glShadeModel(GL_FLAT);

	/*
		Si quieremos que se utilice el color dado a los triángulos.
	*/
	//glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	/*
		Si haces un glScale, independientemente de si utilizas marcos de pila
								glPushMatrix y glPopMatrix
		El escalado también influye en "normal matrix", por lo que hay que
		establecer GL_NORMALIZE para que se vuelvan a normalizar las normales
		y la iluminación se calcule bien.
	*/
	glEnable(GL_NORMALIZE);
}

// -----------------------------------------------------------------------------

void generate_models(){

	vector<Polyhedron::point> points;

	sphere.spin(num_surfaces);

	// Cilindro
	// ---------------------------------------------------------------------------

	cylinder.spin(num_surfaces);

	// Glass
	// ---------------------------------------------------------------------------

	points.clear();
	points.push_back(Polyhedron::point(0.75,0.5,0));
	points.push_back(Polyhedron::point(0.5,-0.5,0));
	points.push_back(Polyhedron::point(0,-0.5,0));

	glass.set_points(points,num_surfaces);

	// Inverted Glass
	// ---------------------------------------------------------------------------

	points.clear();
	points.push_back(Polyhedron::point(0,0.5,0));
	points.push_back(Polyhedron::point(0.5,0.5,0));
	points.push_back(Polyhedron::point(0.75,-0.5,0));

	inv_glass.set_points(points,num_surfaces);

	// Cone
	// ---------------------------------------------------------------------------

	points.clear();
	points.push_back(Polyhedron::point(0,0.5,0));
	points.push_back(Polyhedron::point(0.5,-0.5,0));
	points.push_back(Polyhedron::point(0,-0.5,0));

	cone.set_points(points,num_surfaces);

	// Tube
	// ---------------------------------------------------------------------------

	points.clear();
	points.push_back(Polyhedron::point(0.5,-0.5,0));
	points.push_back(Polyhedron::point(0.5,0.5,0));

	tube.set_points(points,num_surfaces);

	// Pawn
	// ---------------------------------------------------------------------------

	points.clear();
	points.push_back(Polyhedron::point(0,1.4,0)); // Base superior
	points.push_back(Polyhedron::point(0.3,1.4,0));
	points.push_back(Polyhedron::point(0.5,1.2,0));
	points.push_back(Polyhedron::point(0.55,1,0));
	points.push_back(Polyhedron::point(0.5,0.8,0));
	points.push_back(Polyhedron::point(0.3,0.6,0));
	points.push_back(Polyhedron::point(0.5,0.6,0));
	points.push_back(Polyhedron::point(0.4,0.5,0));
	points.push_back(Polyhedron::point(0.4,-0.4,0));
	points.push_back(Polyhedron::point(0.5,-0.7,0));
	points.push_back(Polyhedron::point(1,-1.1,0));
	points.push_back(Polyhedron::point(1,-1.4,0));
	points.push_back(Polyhedron::point(0,-1.4,0)); // Base inferior

	pawn.set_points(points,num_surfaces);

}


//**************************************************************************
//
//***************************************************************************

void clear_window()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
	//  Front_plane>0  Back_plane>PlanoDelantero)
	glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

	// posicion del observador
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0,0,-Observer_distance);
	glRotatef(Observer_angle_x,1,0,0);
	glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
	glBegin(GL_LINES);
	// eje X, color rojo
	glColor3f(1,0,0);
	glVertex3f(-AXIS_SIZE,0,0);
	glVertex3f(AXIS_SIZE,0,0);
	// eje Y, color verde
	glColor3f(0,1,0);
	glVertex3f(0,-AXIS_SIZE,0);
	glVertex3f(0,AXIS_SIZE,0);
	// eje Z, color azul
	glColor3f(0,0,1);
	glVertex3f(0,0,-AXIS_SIZE);
	glVertex3f(0,0,AXIS_SIZE);
	glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{
	GLfloat Vertices[8][3]= {{5,0,0},{4,4,0},{0,5,0},{-4,4,0},{-5,0,0},{-4,-4,0},{0,-5,0},{4,-4,0}};
	int i;

	glColor3f(0,1,0);
	glPointSize(4);

	glBegin(GL_POINTS);
	for (i=0;i<8;i++){
		glVertex3fv((GLfloat *) &Vertices[i]);
		}
	glEnd();
}


//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{
	// Deshabilitamos la luz
	glDisable(GL_LIGHTING);

	clear_window();
	change_observer();
	draw_axis();
	//draw_objects();

	// Iluminación
	if(light_mode != NONE){
		glEnable(GL_LIGHTING);

		// Lighting - Position fixed
		draw_light0();
		draw_light1();
	}

	// Modelos
	draw();

	glutSwapBuffers();
}

//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
	change_projection();
	glViewport(0,0,Ancho1,Alto1);
	glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y)
{
	// More keys
	int key_modifier = glutGetModifiers();

	switch(toupper(Tecla1)){
		case 'Q':
			exit(0);
			break;

		case 'P':
			disable_lighting();
			draw_mode = POINTS;
			break;

		case 'A':
			disable_lighting();
			draw_mode = EDGES;
			break;

		case 'S':
			disable_lighting();
			draw_mode = SURFACES;
			break;

		case 'C':
			disable_lighting();
			draw_mode = CHESS;
			break;

		case 'T':
			if(key_modifier == GLUT_ACTIVE_ALT){
				active_texture = !active_texture;
			}
			else{
				disable_lighting();
				draw_mode = ALL;
			}

			break;

		case '1':
			selected_item = ONE;
			break;

		case '2':
			selected_item = TWO;
			break;
		case '3':
			selected_item = THREE;
			break;
		case '4':
			selected_item = FOUR;
			break;
		case '5':
			selected_item = FIVE;
			break;
		case '6':
			selected_item = SIX;
			break;
		case '7':
			selected_item = SEVEN;
			break;
		case '8':
			selected_item = EIGHT;
			break;

		case '+':
			need_spin = true;
			num_surfaces += SPIN_JUMP;
			break;

		case '-':
			if(num_surfaces > SPIN_JUMP){
				need_spin = true;
				num_surfaces -= SPIN_JUMP;
			}
			break;

		case 'L':
			if(speed < MAX_SPEED)
				speed += SPEED_INC;
			break;

		case 'K':
			if(speed > MIN_SPEED)
				speed -= SPEED_INC;
			break;

		case 'I':
			enable_lighting();
			glShadeModel(GL_FLAT);
			light_mode = FLAT;
			break;

		case 'G':
			enable_lighting();
			glShadeModel(GL_SMOOTH);
			light_mode = SMOOTH;
			break;

		case 'E':
			light0_angle = (light0_angle + 5) % 360;
			draw_light0();
			break;

		case 'D':
			light0_angle = (light0_angle - 5) % 360;
			draw_light0();
			break;

		case 'R':
			light1_angle = (light1_angle + 5) % 360;
			draw_light1();
			break;

		case 'F':
			light1_angle = (light1_angle - 5) % 360;
			draw_light1();
			break;

		case 'Z':
			set_material0();
			break;

		case 'X':
			set_material1();
			break;

	}

	glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{

	switch (Tecla1){
		case GLUT_KEY_LEFT:Observer_angle_y--;break;
		case GLUT_KEY_RIGHT:Observer_angle_y++;break;
		case GLUT_KEY_UP:Observer_angle_x--;break;
		case GLUT_KEY_DOWN:Observer_angle_x++;break;
		case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
		case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
		case GLUT_KEY_F1:
			draw_item = TETRAHEDRON;
			break;
		case GLUT_KEY_F2:
			draw_item = CUBE;
			break;
		case GLUT_KEY_F3:
			draw_item = FILE_MODEL;
			break;
		case GLUT_KEY_F4:
			draw_item = REVOLUTION;
			break;
		case GLUT_KEY_F5:
			draw_item = WATT;
			break;
		case GLUT_KEY_F6:
			draw_item = BOARD;
			break;
		}

	glutPostRedisplay();
}


//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
	// se inicalizan la ventana y los planos de corte
	Window_width=0.5;
	Window_height=0.5;
	Front_plane=1;
	Back_plane=1000;

	// se inicia la posicion del observador, en el eje z
	Observer_distance=2*Front_plane;
	Observer_angle_x=0;
	Observer_angle_y=0;

	// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
	// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
	glClearColor(1,1,1,1);

	// se habilita el z-bufer
	glEnable(GL_DEPTH_TEST);
	//
	change_projection();
	//
	glViewport(0,0,UI_window_width,UI_window_height);
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{
	// Cargamos los modelos en memoria
	// ---------------------------------------------------------------------------
	read_models();
	generate_models();

	// Comprobamos si hay triángulos degenerados -> Sólo big_porsche degenerado
	// ---------------------------------------------------------------------------
	/*
	cout << "Degenerate: " << cube.has_degenerate_triangles() << endl;
	cout << "Degenerate: " << tetrahedron.has_degenerate_triangles() << endl;

	cout << "Degenerate: " << file_model.has_degenerate_triangles() << endl;
	cout << "Degenerate: " << file_model2.has_degenerate_triangles() << endl;
	cout << "Degenerate: " << file_model3.has_degenerate_triangles() << endl;

	cout << "Degenerate: " << cylinder.has_degenerate_triangles() << endl;
	cout << "Degenerate: " << glass.has_degenerate_triangles() << endl;
	cout << "Degenerate: " << inv_glass.has_degenerate_triangles() << endl;
	cout << "Degenerate: " << cone.has_degenerate_triangles() << endl;
	cout << "Degenerate: " << tube.has_degenerate_triangles() << endl;
	cout << "Degenerate: " << pawn.has_degenerate_triangles() << endl;
	*/

	// Max/Min area test
	// ---------------------------------------------------------------------------
	/*
	cube.get_max_min_triangle_area();
	tetrahedron.get_max_min_triangle_area();

	file_model.get_max_min_triangle_area();
	file_model2.get_max_min_triangle_area();
	file_model3.get_max_min_triangle_area();

	cylinder.get_max_min_triangle_area();
	glass.get_max_min_triangle_area();
	inv_glass.get_max_min_triangle_area();
	cone.get_max_min_triangle_area();
	tube.get_max_min_triangle_area();
	pawn.get_max_min_triangle_area();
	*/

	// ---------------------------------------------------------------------------

	// se llama a la inicialización de glut
	glutInit(&argc, argv);

	// se indica las caracteristicas que se desean para la visualización con OpenGL
	// Las posibilidades son:
	// GLUT_SIMPLE -> memoria de imagen simple
	// GLUT_DOUBLE -> memoria de imagen doble
	// GLUT_INDEX -> memoria de imagen con color indizado
	// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
	// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
	// GLUT_DEPTH -> memoria de profundidad o z-bufer
	// GLUT_STENCIL -> memoria de estarcido
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	// posicion de la esquina inferior izquierdad de la ventana
	glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

	// tamaño de la ventana (ancho y alto)
	glutInitWindowSize(UI_window_width,UI_window_height);

	// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
	// al bucle de eventos)
	glutCreateWindow("IG - Practica");

	// asignación de la funcion llamada "dibujar" al evento de dibujo
	glutDisplayFunc(draw_scene);
	// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
	glutReshapeFunc(change_window_size);
	// asignación de la funcion llamada "tecla_normal" al evento correspondiente
	glutKeyboardFunc(normal_keys);
	// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
	glutSpecialFunc(special_keys);

	// funcion de inicialización
	initialize();

	// Cambiamos la función IDLE para que actualice el modelo
	glutIdleFunc( update_model );

	// Inicializamos la luz
	init_light();

	// Cargamos las texturas
	load_textures();

	// inicio del bucle de eventos
	glutMainLoop();

	// Liberamos las texturas
	delete earth_texture;

	return 0;
}
