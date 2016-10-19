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


#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>

#include <vector>
#include "vertex.h"
#include "file_ply_stl.h"

#include "polyhedron.hpp"
#include "cube.hpp"
#include "tetrahedron.hpp"

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

enum DrawMode { POINTS, EDGES, SURFACES, CHESS, ALL };
enum DrawItem { CUBE, TETRAHEDRON, FILE_MODEL };

Cube cube;
Polyhedron file_model;
Tetrahedron tetrahedron;

DrawMode draw_mode = POINTS;
DrawItem draw_item = TETRAHEDRON;

// Funciones
// ----------------------------------------------------------------------------

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

}

void draw_polyhedron( const Polyhedron & polyhedron ){

	switch (draw_mode) {
		case POINTS:
			polyhedron.draw_points();
			break;
		case EDGES:
			polyhedron.draw_edges();
			break;
		case SURFACES:
			polyhedron.draw_surfaces();
			break;
		case CHESS:
			polyhedron.draw_chess();
			break;
		case ALL:
			polyhedron.draw_all();
			break;
	}

}

void draw(){
	/*
	 * Función encargada de dibujar un modelo.
	 */
	glColor3f(0,0,0);
	glPointSize(4);

	switch (draw_item) {
		case CUBE:
			draw_polyhedron(cube);
			break;
		case TETRAHEDRON:
			draw_polyhedron(tetrahedron);
			break;
		case FILE_MODEL:
			draw_polyhedron(file_model);
			break;
	}

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
	clear_window();
	change_observer();
	draw_axis();
	//draw_objects();

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


	switch(toupper(Tecla1)){
		case 'Q':
			exit(0);
			break;

		case 'P':
			draw_mode = POINTS;
			break;

		case 'A':
			draw_mode = EDGES;
			break;

		case 'S':
			draw_mode = SURFACES;
			break;

		case 'C':
			draw_mode = CHESS;
			break;

		case 'T':
			draw_mode = ALL;
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

	char filename[] = "./modelos/big_porsche.ply";
	read_polygon_from_file(filename, file_model);

	// ------------------------------------------------------------------------

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

	// inicio del bucle de eventos
	glutMainLoop();
	return 0;
}
