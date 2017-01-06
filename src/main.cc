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

#include "camera.hpp"


// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=800,UI_window_height=800;


// ----------------------------------------------------------------------------
//
// CÓDIGO DEL ALUMNO
//
// ----------------------------------------------------------------------------


// Draw parameters
// -----------------------------------------------------------------------------


enum DrawItem { CUBE, TETRAHEDRON, FILE_MODEL, REVOLUTION, WATT, BOARD };
enum SelectIem { ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT };


// Parameters that control the number of divisions - RevolutionSurface
// -----------------------------------------------------------------------------

const int SPIN_JUMP = 1;
unsigned int num_surfaces = 50;
bool need_spin = false;


// Models
// -----------------------------------------------------------------------------


Cube cube;
Cube2 cube2;
Tetrahedron tetrahedron;
Board board;

Polyhedron file_model;
Polyhedron file_model2;
Polyhedron file_model3;

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


// Lighting
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

GLfloat light0_pos[4] = {0,10,0,1}; // Coordenadas homogéneas
GLfloat light1_pos[4] = {0,0,10,0}; // Coordenadas homogéneas


// Camera
// -----------------------------------------------------------------------------


enum ProjectionMode {PARALLEL,PERSPECTIVE};

ProjectionMode projection_mode = PERSPECTIVE;

Camera cameras[2];

int current_camera = 0;

bool mouse_move_camera = false;
double mouse_sensitivity = 0.5;

double ortho_zoom = 2;

int x_prev;
int y_prev;


// -----------------------------------------------------------------------------
//
// FUNCTIONS
//
// -----------------------------------------------------------------------------


// LOAD DATA
// -----------------------------------------------------------------------------


void load_textures(){
	/*
		Load all the textures.
	*/
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

void generate_models(){
	/*
		Generate RevolutionSurface objects from a profile of points.
	*/
	vector<Polyhedron::point> points;

	// Sphere
	sphere.spin(num_surfaces);

	// Cylinder
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

// -----------------------------------------------------------------------------

void read_models(){
	/*
		Load models from a '.ply' file.
	*/
	char filename1[] = "./modelos/ant.ply";
	char filename2[] = "./modelos/big_porsche.ply";
	char filename3[] = "./modelos/dolphins.ply";

	file_model.load_ply(filename1);
	file_model2.load_ply(filename2);
	file_model3.load_ply(filename3);
}


// UPDATE VIEW
// -----------------------------------------------------------------------------


void update_model(){
	/*
		Rotate de body of the Watt Object.
	*/

	// Only if the WATT Object is selected
	if(draw_item == WATT){
		rotate_angle += max_rotate*speed/1000;

		if(rotate_angle > max_rotate)
			rotate_angle -= max_rotate;

		glutPostRedisplay();
	}
}

// -----------------------------------------------------------------------------

void set_material0(){
	/*
		Active material0.
	*/
	glMaterialfv(GL_FRONT,GL_AMBIENT, (GLfloat *) &material0_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE, (GLfloat *) &material0_diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR, (GLfloat *) &material0_specular);
	glMaterialf(GL_FRONT,GL_SHININESS,50);
}

// -----------------------------------------------------------------------------

void set_material1(){
	/*
		Active material1.
	*/
	glMaterialfv(GL_FRONT,GL_AMBIENT, (GLfloat *) &material1_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE, (GLfloat *) &material1_diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR, (GLfloat *) &material1_specular);
	glMaterialf(GL_FRONT,GL_SHININESS,5);
}

// -----------------------------------------------------------------------------

void draw(){
	/*
	 		Draw the current object selected by the user.
	 */

	 // If it's needed, reload the revolution objects.
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

	// Default parameters
	glPointSize(4);

	// Draw
	switch (draw_item) {
		case CUBE:
			glPushMatrix();
				glTranslatef(0.8,0,0);
				cube.draw(draw_mode);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-0.8,0,0);
				cube2.draw(draw_mode);
			glPopMatrix();
			break;

		case TETRAHEDRON:
			tetrahedron.draw(draw_mode);
			break;

		case FILE_MODEL:
			switch (selected_item) {
				case ONE:
					file_model.draw(draw_mode);
					break;
				case TWO:
					file_model2.draw(draw_mode);
					break;
				case THREE:
					file_model3.draw(draw_mode);
					break;
				}
			break;

		// REVOLUTION MENU
		case REVOLUTION:
			switch (selected_item) {
				case ONE:
					cylinder.draw(draw_mode);
					break;
				case TWO:
					glass.draw(draw_mode);
					break;
				case THREE:
					inv_glass.draw(draw_mode);
					break;
				case FOUR:
					cone.draw(draw_mode);
					break;
				case FIVE:
					tube.draw(draw_mode);
					break;
				case SIX:
					sphere.draw(draw_mode);
					break;
				case SEVEN:
					pawn.draw(draw_mode);
					break;
				case EIGHT:
					scene.draw(draw_mode);

					// Set default texture/material
					glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,earth_texture -> tamX(),earth_texture -> tamY(),0,GL_RGB,GL_UNSIGNED_BYTE, (GLvoid *) (earth_texture -> leerPixels()));
					set_material0();
					break;
			}
			break;

		case WATT:
			watt.draw(draw_mode);
			break;

		case BOARD:
			board.draw(draw_mode);
			break;
	}

}

// -----------------------------------------------------------------------------

void disable_lighting(){
	/*
		Disable lighting.
	*/
	light_mode = NONE;
	glDisable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
}

// -----------------------------------------------------------------------------

void enable_lighting(){
	/*
		Enable lighting.
	*/
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
}

// -----------------------------------------------------------------------------

void draw_light0(){
	/*
		Rotate 'light0'.
	*/
	glPushMatrix();
	glRotatef(light0_angle,0,0,1);
	glLightfv(GL_LIGHT0,GL_POSITION,(GLfloat *) &light0_pos);
	glPopMatrix();
}

// -----------------------------------------------------------------------------

void draw_light1(){
	/*
		Rotate 'light1'.
	*/
	glPushMatrix();
	glRotatef(light1_angle,0,1,0);
	glLightfv(GL_LIGHT1,GL_POSITION,(GLfloat *) &light1_pos);
	glPopMatrix();
}

// -----------------------------------------------------------------------------

void init_light(){
	/*
		Initialize lighting parameters.
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

	// Default lighting
	light_mode = FLAT;
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

// INPUT EVENTS
// -----------------------------------------------------------------------------


void set_projection(){
	/*
		Set the camera mode.
	*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	switch(projection_mode){
		case PERSPECTIVE:

			// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
			//  Front_plane>0  Back_plane>PlanoDelantero)
			glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
			break;
		case PARALLEL:

			// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
			//  Front_plane>0  Back_plane>PlanoDelantero)
			glOrtho(-Window_width*ortho_zoom,Window_width*ortho_zoom,-Window_height*ortho_zoom,Window_height*ortho_zoom,Front_plane,Back_plane);
			break;
	}

}

// -----------------------------------------------------------------------------

void change_projection(){
	/*
		Change the camera mode.
	*/
	switch(projection_mode){
		case PERSPECTIVE:
			projection_mode = PARALLEL;
			break;
		case PARALLEL:
			projection_mode = PERSPECTIVE;
			break;
	}

	set_projection();
}

// -----------------------------------------------------------------------------

void on_mouse_clicked(int button, int status, int x, int y){
	/*
		Handle the 'mouse click' event.

		Click + Move -> Rotate camera.
	*/
	if(button == 0 && status == GLUT_DOWN){
		mouse_move_camera = true;
		y_prev = y;
		x_prev = x;
	}
	else if(button == 3){
		if(projection_mode == PERSPECTIVE)
			cameras[current_camera].add_z(0.1);
		else{
			ortho_zoom += 0.1;
			set_projection();
		}
	}
	else if(button == 4){
		if(projection_mode == PERSPECTIVE)
			cameras[current_camera].add_z(-0.1);
		else{
			ortho_zoom -= 0.1;
			set_projection();
		}
	}
	else
		mouse_move_camera = false;

	glutPostRedisplay();
}

// -----------------------------------------------------------------------------

void on_mouse_moved(int x, int y){
	/*
		Move the camera if the mouse button is clicked.
	*/
	if(mouse_move_camera){
		cameras[current_camera].add_y_angle((x-x_prev)*mouse_sensitivity);
		cameras[current_camera].add_x_angle((y-y_prev)*mouse_sensitivity);
		x_prev = x;
		y_prev = y;
		glutPostRedisplay();
	}
}

// -----------------------------------------------------------------------------

void normal_keys(unsigned char Tecla1,int x,int y){
	/*
		Key press events.
	*/

	// More keys
	int key_modifier = glutGetModifiers();

	switch(toupper(Tecla1)){
		case 'Q':
			exit(0);
			break;

		case 'P':
			if(key_modifier == GLUT_ACTIVE_ALT){
				change_projection();
			}
			else{
				disable_lighting();
				draw_mode = POINTS;
			}
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

// -----------------------------------------------------------------------------

void special_keys(int key,int x,int y)
{

	switch (key){
		case GLUT_KEY_LEFT:cameras[current_camera].add_y_angle(-1); break;
		case GLUT_KEY_RIGHT:cameras[current_camera].add_y_angle(1); break;
		case GLUT_KEY_UP:cameras[current_camera].add_x_angle(-1); break;
		case GLUT_KEY_DOWN:cameras[current_camera].add_x_angle(1); break;
		case GLUT_KEY_PAGE_UP:cameras[current_camera].add_position(0,0,0.1); break;
		case GLUT_KEY_PAGE_DOWN:cameras[current_camera].add_position(0,0,-0.1); break;
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


//**************************************************************************
//
//***************************************************************************

void clear_window()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

	// posicion del observador
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	cameras[current_camera].update_view();
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

// -----------------------------------------------------------------------------

void draw_scene(void){

	// Disable lighting
	glDisable(GL_LIGHTING);

	clear_window();

	// Select camera
	change_observer();


	draw_axis();

	// Lighting mode
	if(light_mode != NONE){
		glEnable(GL_LIGHTING);

		// Lighting - Position fixed
		draw_light0();
		draw_light1();
	}

	// Draw scene
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
	set_projection();
	glViewport(0,0,Ancho1,Alto1);
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

	// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
	// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
	glClearColor(1,1,1,1);

	// se habilita el z-bufer
	glEnable(GL_DEPTH_TEST);

	// Set the camera mode.
	set_projection();

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

	// Mouse events
	glutMouseFunc(on_mouse_clicked);			// Click
	glutMotionFunc(on_mouse_moved);				// Mover

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
	delete grass_texture;
	delete stars_texture;
	delete chess_texture;
	delete can_texture;

	return 0;
}
