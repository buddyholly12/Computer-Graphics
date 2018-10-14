#include <iostream>
#include <fstream>
using namespace std;

#include "GL Libraries/GL/glut.h"
#include "Model.h"
#include "Matrix2.h"
#include "Vector.h"
#include "Transformation.h"
#include "Quadric.h"
#define WINDOW_SIZE 600

Model __3d_block, __3d_roof, __3d_roof_lr;
Model __decorations[3];
Quadric hiperbola;
Transformation transformation;

float SCALE_VALUE = 700;
float TRANSLATE[3];
float ANGLE_THETA = 0;
int rotates = 0;
void idle() {
	glutPostRedisplay();
}

void initWorld() {

	glOrtho(-WINDOW_SIZE, WINDOW_SIZE, -WINDOW_SIZE, WINDOW_SIZE, -WINDOW_SIZE, WINDOW_SIZE);

	glClearColor(0, 0, 0, 0);

	// FRONT RECT
	__3d_block.add_point(Vector(0.2, 0.1, 0.0, 1));
	__3d_block.add_point(Vector(0.9, 0.1, 0.0, 1));
	__3d_block.add_point(Vector(0.9, 0.575, 0.0, 1));
	__3d_block.add_point(Vector(0.2, 0.575, 0.0, 1));

	// BACK RECT
	__3d_block.add_point(Vector(0.2, 0.1, 0.5, 1));
	__3d_block.add_point(Vector(0.9, 0.1, 0.5, 1));
	__3d_block.add_point(Vector(0.9, 0.575, 0.5, 1));
	__3d_block.add_point(Vector(0.2, 0.575, 0.5, 1));

	// LEFT RECT
	__3d_block.add_point(Vector(0.2, 0.1, 0.5, 1));
	__3d_block.add_point(Vector(0.2, 0.1, 0.0, 1));
	__3d_block.add_point(Vector(0.2, 0.575, 0.0, 1));
	__3d_block.add_point(Vector(0.2, 0.575, 0.5, 1));

	// RIGHT RECT
	__3d_block.add_point(Vector(0.9, 0.1, 0.5, 1));
	__3d_block.add_point(Vector(0.9, 0.1, 0.0, 1));
	__3d_block.add_point(Vector(0.9, 0.575, 0.0, 1));
	__3d_block.add_point(Vector(0.9, 0.575, 0.5, 1));

	__3d_block.transformation_matrix = transformation.scale(Vector(SCALE_VALUE, SCALE_VALUE, SCALE_VALUE, 1));

	// LEFT TRIANGLE / ROOF
	__3d_roof.add_point(Vector(0.9, 0.575, 0.0, 1));
	__3d_roof.add_point(Vector(0.9, 0.575, 0.5, 1));
	__3d_roof.add_point(Vector(0.9, 0.8, 0.25, 1));

	// RIGHT TRIANGLE / ROOF
	__3d_roof.add_point(Vector(0.2, 0.575, 0.0, 1));
	__3d_roof.add_point(Vector(0.2, 0.575, 0.5, 1));
	__3d_roof.add_point(Vector(0.2, 0.8, 0.25, 1));

	__3d_roof.transformation_matrix = transformation.scale(Vector(SCALE_VALUE, SCALE_VALUE, SCALE_VALUE, 1));

	// FRONT ROOF
	__3d_roof_lr.add_point(Vector(0.2, 0.575, 0.0, 1));
	__3d_roof_lr.add_point(Vector(0.9, 0.575, 0.0, 1));
	__3d_roof_lr.add_point(Vector(0.9, 0.8, 0.25, 1));
	__3d_roof_lr.add_point(Vector(0.2, 0.8, 0.25, 1));

	// BACK ROOF
	__3d_roof_lr.add_point(Vector(0.2, 0.575, 0.5, 1));
	__3d_roof_lr.add_point(Vector(0.9, 0.575, 0.5, 1));
	__3d_roof_lr.add_point(Vector(0.9, 0.8, 0.25, 1));
	__3d_roof_lr.add_point(Vector(0.2, 0.8, 0.25, 1));

	__3d_roof_lr.transformation_matrix = transformation.scale(Vector(SCALE_VALUE, SCALE_VALUE, SCALE_VALUE, 1));

	// DOOR 
	__decorations[0].add_point(Vector(0.47, 0.105, 0.0, 1));
	__decorations[0].add_point(Vector(0.65, 0.105, 0.0, 1));
	__decorations[0].add_point(Vector(0.65, 0.46, 0.0, 1));
	__decorations[0].add_point(Vector(0.47, 0.46, 0.0, 1));

	// WINDOW 1
	__decorations[1].add_point(Vector(0.72, 0.25, 0.0, 1));
	__decorations[1].add_point(Vector(0.83, 0.25, 0.0, 1));
	__decorations[1].add_point(Vector(0.83, 0.4, 0.0, 1));
	__decorations[1].add_point(Vector(0.72, 0.4, 0.0, 1));

	// WINDOW 2
	__decorations[2].add_point(Vector(0.27, 0.25, 0.0, 1));
	__decorations[2].add_point(Vector(0.38, 0.25, 0.0, 1));
	__decorations[2].add_point(Vector(0.38, 0.4, 0.0, 1));
	__decorations[2].add_point(Vector(0.27, 0.4, 0.0, 1));

	__decorations[0].transformation_matrix = transformation.scale(Vector(SCALE_VALUE, SCALE_VALUE, SCALE_VALUE, 1));
	__decorations[1].transformation_matrix = transformation.scale(Vector(SCALE_VALUE, SCALE_VALUE, SCALE_VALUE, 1));
	__decorations[2].transformation_matrix = transformation.scale(Vector(SCALE_VALUE, SCALE_VALUE, SCALE_VALUE, 1));

	__3d_block.transformation_matrix.translate(Vector(TRANSLATE[0], TRANSLATE[1], TRANSLATE[2], 1));
	__3d_roof.transformation_matrix.translate(Vector(TRANSLATE[0], TRANSLATE[1], TRANSLATE[2], 1));
	// GEEKS WAY
	__3d_roof_lr.transformation_matrix = transformation.translate(__3d_roof_lr.transformation_matrix, Vector(TRANSLATE[0], TRANSLATE[1], TRANSLATE[2], 1));

	__decorations[0].transformation_matrix.translate(Vector(TRANSLATE[0], TRANSLATE[1], TRANSLATE[2], 1));
	__decorations[1].transformation_matrix.translate(Vector(TRANSLATE[0], TRANSLATE[1], TRANSLATE[2], 1));
	__decorations[2].transformation_matrix.translate(Vector(TRANSLATE[0], TRANSLATE[1], TRANSLATE[2], 1));

	if (rotates == 1) {
		__3d_block.transformation_matrix = __3d_block.transformation_matrix.multiplies(transformation.rotate_x(ANGLE_THETA));
		__3d_roof.transformation_matrix = __3d_roof.transformation_matrix.multiplies(transformation.rotate_x(ANGLE_THETA));
		__3d_roof_lr.transformation_matrix = __3d_roof_lr.transformation_matrix.multiplies(transformation.rotate_x(ANGLE_THETA));
		for (int i = 0; i < 3; i++) {
			__decorations[i].transformation_matrix = __decorations[i].transformation_matrix.multiplies(transformation.rotate_x(ANGLE_THETA));
		}
	}
	if (rotates == 2) {
		__3d_block.transformation_matrix = __3d_block.transformation_matrix.multiplies(transformation.rotate_y(ANGLE_THETA));
		__3d_roof.transformation_matrix = __3d_roof.transformation_matrix.multiplies(transformation.rotate_y(ANGLE_THETA));
		__3d_roof_lr.transformation_matrix = __3d_roof_lr.transformation_matrix.multiplies(transformation.rotate_y(ANGLE_THETA));
		for (int i = 0; i < 3; i++) {
			__decorations[i].transformation_matrix = __decorations[i].transformation_matrix.multiplies(transformation.rotate_y(ANGLE_THETA));
		}
	}
	if (rotates == 3) {
		__3d_block.transformation_matrix = __3d_block.transformation_matrix.multiplies(transformation.rotate_z(ANGLE_THETA));
		__3d_roof.transformation_matrix = __3d_roof.transformation_matrix.multiplies(transformation.rotate_z(ANGLE_THETA));
		__3d_roof_lr.transformation_matrix = __3d_roof_lr.transformation_matrix.multiplies(transformation.rotate_z(ANGLE_THETA));
		for (int i = 0; i < 3; i++) {
			__decorations[i].transformation_matrix = __decorations[i].transformation_matrix.multiplies(transformation.rotate_z(ANGLE_THETA));
		}
	}
}

void test() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// glRotatef(0.5, 1, 1, 1);
	
	glColor3f(0.75, 0.75, 0.25);
	__3d_block.draw_quads();
	
	glColor3f(1, 1, 1);
	__3d_roof.draw_triangles();

	glColor3f(1, 1, 0);
	__3d_roof_lr.draw_quads();

	glColor3f(1, 0, 0);
	__decorations[0].draw_quads();
	__decorations[1].draw_quads();
	__decorations[2].draw_quads();

	glutSwapBuffers();
}

void main(int argc, char **argv) {

	TRANSLATE[0] = -400;
	TRANSLATE[1] = -400;
	TRANSLATE[2] = 0;
	
	int choose = 2;
	cout << "TRANSLATE ?1. Ya 2. Tidak";
	cin >> choose;
	if (choose == 1) {
		cout << "input vector x: ";
		cin >> TRANSLATE[0];
		cout << "input vector y: ";
		cin >> TRANSLATE[1];
		cout << "input vector z: ";
		cin >> TRANSLATE[2];
	}
	cout << "ROTASI ?1. X 2. Y 3. Z 4. Tidak";
	cin >> choose;
	if (choose >= 1 && choose <= 3) {
		cout << "input angle_theta: ";
		cin >> ANGLE_THETA;
		rotates = choose;
	}
	cout << "SCALE ?1. Ya 2. Tidak";
	cin >> choose;
	if (choose == 1) {
		cout << "input SCALE VALUE";
		cin >> SCALE_VALUE;
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
	glutCreateWindow("uts grafkom");

	glutIdleFunc(idle);

	glutDisplayFunc(test);

	initWorld();

	glutMainLoop();

}