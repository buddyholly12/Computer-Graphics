
#include "Vector.h"
#include "Matrix.h"
#include "Matrix2.h"
#include "Quadric.h"
#include "Hirearchy.h"
#include "Transformation.h"
#include "RGBColor.h"
#include "GL Libraries\GL\glut.h"

#define WINDOW_SIZE 500

Hirearchy __kipas_system[10];
/*
*	0. kaki
*	1. badan
*	2. leher
*	3. keping 3x
*/
Transformation transformation;

Quadric tabung;

void idle() {
	glutPostRedisplay();
}

void initWorld() {

	glOrtho(-WINDOW_SIZE, WINDOW_SIZE, -WINDOW_SIZE, WINDOW_SIZE, -WINDOW_SIZE, WINDOW_SIZE);

	glClearColor(0, 0, 0, 0);

	float orange[3] = { 1, 0.5, 0 };
	float white[3] = { 255, 255, 255 };

	Matrix2 _badan_transform, _leher_transform, _kaki_transform, _keping_transform;

	Quadric _badan_kipas, _leher_kipas, _kaki_kipas_, _keping_kipas;
	
	_kaki_transform.translate(Vector(0, -400, 0, 1));
	_kaki_transform.rotate_y(30); // 60
	_kaki_transform = _kaki_transform.multiplies(transformation.rotate_z(50));
	
	_badan_transform.translate(Vector(0, 200, 0, 1));
	
	_leher_transform.translate(Vector(0, 200, 100, 1));
	_leher_transform.rotate_x(80);

	_badan_kipas.elipse(100, 200);
	_leher_kipas.elipse(100, 200);
	_kaki_kipas_.elipse(200, 50);
	_keping_kipas.elipse(75, 25);

	__kipas_system[0].set_quadric(_kaki_kipas_);
	__kipas_system[0].set_color(white);
	__kipas_system[0].set_matrix_transformation(_kaki_transform);
	__kipas_system[0].set_index(-1);

	__kipas_system[1].set_quadric(_badan_kipas);
	__kipas_system[1].set_color(orange);
	__kipas_system[1].set_index(0);
	__kipas_system[1].set_matrix_transformation(_badan_transform);

	__kipas_system[2].set_quadric(_leher_kipas);
	__kipas_system[2].set_color(white);
	__kipas_system[2].set_index(1);
	__kipas_system[2].set_matrix_transformation(_leher_transform);

	_keping_transform.translate(Vector(0, -200, 100, 1));
	__kipas_system[3].set_quadric(_keping_kipas);
	__kipas_system[3].set_color(orange);
	__kipas_system[3].set_index(2);
	__kipas_system[3].set_matrix_transformation(_keping_transform);

	_keping_transform.translate(Vector(100, -200, 0, 1));
	__kipas_system[4].set_quadric(_keping_kipas);
	__kipas_system[4].set_color(white);
	__kipas_system[4].set_index(2);
	__kipas_system[4].set_matrix_transformation(_keping_transform);

	_keping_transform.translate(Vector(-100, -200, 0, 1));
	__kipas_system[5].set_quadric(_keping_kipas);
	__kipas_system[5].set_color(orange);
	__kipas_system[5].set_index(2);
	__kipas_system[5].set_matrix_transformation(_keping_transform);

	_keping_transform.translate(Vector(0, -200, -100, 1));
	__kipas_system[6].set_quadric(_keping_kipas);
	__kipas_system[6].set_color(white);
	__kipas_system[6].set_index(2);
	__kipas_system[6].set_matrix_transformation(_keping_transform);

	tabung.tube(100);

}

float theta = 2, theta_bor = 0;
bool arah = 1;
void test() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// ROTASI ARAH BADAN KIPAS
	if (arah == 1) { 
		theta += 0.01;
		if (theta >= 4) 
			arah = 0;
	}
	else {
		theta -= 0.01;
		if (theta <= 2) 
			arah = 1;
	}
	glRotatef(1, 0, 1, 0);
	tabung.draw_wire();

	// THETA ROTASI LEHER KIPAS
	theta_bor += 1;
	if (theta_bor >= 6) 
		theta_bor = 0;

	// ROTASI LEHER KIPAS
	__kipas_system[2]._matrix_transformation2 = __kipas_system[2]._matrix_transformation2.multiplies(transformation.rotate_y(theta_bor));

	// ROTASI BADAN KIPAS
	__kipas_system[1]._matrix_transformation2.rotate_y(theta);
	
	// DRAW MODEL
	for (int i = 0; i < 7; i++) {
		__kipas_system[i].draw2(__kipas_system);
	}

	glutSwapBuffers();
}

void main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
	glutCreateWindow("uts grafkom");

	glutIdleFunc(idle);

	glutDisplayFunc(test);

	initWorld();

	glutMainLoop();

}
