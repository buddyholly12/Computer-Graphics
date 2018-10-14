// bezier stuff
#include <iostream>
#include <vector>
#include <fstream>
#include "Vector.h"
#include "Matrix2.h"
#include "Transformation.h"
#include "GL Libraries/GL/glut.h"
using namespace std;

#define WINDOW_SIZE 600
#define phi 3.14159



float factorial(int n) {
	if (n <= 1)
		return(1);
	else
		n = n * factorial(n - 1);
	return n;
}
float kombinasi(float n, float k) {
	float result = factorial(n) / (factorial(k)*factorial(n - k));
	return result;
}
Vector get_calculated_bezier_point(vector<Vector> v, float t) {
	int size = v.size();
	float x = 0, y = 0;
	for (int i = 0; i < size; i++) {
		// x += kombinasi((float)(size - 1), (float)i) * pow((1 - t) * 1.0, (size - i - 1) * 1.0) * pow(t*1.0, i) * v[i].x;
		// y += kombinasi((float)(size - 1), (float)i) * pow((1 - t) * 1.0, (size - i - 1) * 1.0) * pow(t, i) * v[i].y;

		// keep the column consistent~
		x += kombinasi((float)(size - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (size - 1 - i)) * v[i].x;
		y += kombinasi((float)(size - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (size - 1 - i)) * v[i].y;
	}
	return Vector(x, y, 0, 1);
}

vector <Vector> to_draw_points;
void DrawBezier(vector<Vector> v) {
	glBegin(GL_POINTS);

	for (float t = 0; t <= 1; t += 0.001) {
		Vector calculated_v = get_calculated_bezier_point(v, t);
		glVertex3d(calculated_v.x, calculated_v.y, calculated_v.z);
		// to_draw_points.push_back(calculated_v);
	}

	glEnd();
}
int countpos = 0;
bool arah = 1;
vector <Vector> titik_awal[10];
void draw_cylinder(int __rad, int __height, int __size) {

	float temp = __rad;
	int count_t = 0;
	for (int i = -(__height / 2); i < __height / 2; i += __size) {

		int __count = 0;
		for (float j = -3.14; j < 3.14; j += 0.01) {
			float __x1 = __rad * sin(j);
			float __y1 = __rad * cos(j);

			glBegin(GL_POINTS);

			glVertex3d(__x1, i, __y1);

			glEnd();
			
			if (i + __size < (__height / 2)) {
				__count++;
				if (__count%__size == 0) {

					titik_awal[count_t++].push_back(Vector(__x1, __y1, 0, 1));
					
					glBegin(GL_LINES);
					glVertex3d(__x1, i + __size, __y1);
					glVertex3d(__x1, i, __y1);
					glEnd();
				}
			}
		}

		for (float j = -3.14; j < 3.14; j += 0.01) {
			float __x1 = (__rad - 20) * sin(j);
			float __y1 = (__rad - 20) * cos(j);

			glBegin(GL_POINTS);

			glVertex3d(__x1, i, __y1);

			glEnd();

			if (i + __size < (__height / 2)) {
				__count++;
				if (__count%__size == 0) {
					glBegin(GL_LINES);
					glVertex3d(__x1, i + __size, __y1);
					glVertex3d(__x1, i, __y1);
					glEnd();
				}
			}
		}
	}

	// DrawBezier(to_draw_points);
}

void draw_circle(float rad, float depth, int __size, int __height) {
	
	glColor3f(1, 0, 0);

	int __count = 0;
	for (float i = -3.14; i < 3.14; i += 0.01) {
		float x = rad * sin(i);
		float y = rad * cos(i);
		glBegin(GL_POINTS);
		glVertex3d(x, depth, y);
		glEnd();
		//if (i + __size < (__height / 2)) {
		//	__count++;
		//	if (__count%__size == 0) {
		//		glBegin(GL_LINES);
		//		glVertex3d(x, i + __size, y);
		//		glVertex3d(x, i, y);
		//		glEnd();
		//	}
		//}

	}
	glColor3f(1, 1, 1);
	for (float i = -3.14; i < 3.14; i += 0.01) {
		float x = (rad - 20) * sin(i);
		float y = (rad - 20) * cos(i);
		glBegin(GL_POINTS);
		glVertex3f(x, depth, y);
		glEnd();
	}
}

void draw_vase() {
	float rad = 90;
	float depth = 200;
	float delta_rad = 5;

	while (depth > 150) {
		draw_circle(rad, depth, 10, 50);
		rad -= delta_rad / 2;
		depth -= 10;
	}
	while (depth > 0) {
		draw_circle(rad, depth, 10, 50);
		rad += delta_rad;
		depth -= 10;
	}
	while (depth > -150) {
		draw_circle(rad, depth, 10, 50);
		depth -= 10;
	}
	while (depth > -170) {
		draw_circle(rad, depth, 10, 50);
		rad -= delta_rad * 2;
		depth -= 1.5;
	}
}

void idle() {
	glutPostRedisplay();
}

Transformation transformation;
vector <Vector> points[10];
vector <Vector> transformed_points;
void initCanvas() {
	// INIT CANVAS
	glOrtho(-WINDOW_SIZE, WINDOW_SIZE, -WINDOW_SIZE, WINDOW_SIZE, -WINDOW_SIZE, WINDOW_SIZE);

	// CLEAR
	glClearColor(0, 0, 0, 0);
	
	points[0].push_back(Vector(0, 0, 0, 1));
	points[0].push_back(Vector(-200, -200, 0, 1));
	points[0].push_back(Vector(200, -300, 0, 1));
	points[0].push_back(Vector(0, -400, 0, 1));
	
	// DrawBezier(points);
	float theta = 0;
	for (int i = 0; i < 4; i++) {
		if (i == 3) {
			break;
		}
		theta += 30;
		// int len = points[i].size();
		for (int j = 0; j < points[i].size(); j++) {
			Vector v(0, 0, 0, 1);
			v = transformation.rotate_y(theta).multiplies(points[i][j]);
			points[i + 1].push_back(v);
			v.showVectorOnConsole();
		}
	}

}
float theta = 0;
void test() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	// glRotatef(10, 0, 1, 0);

	glRotatef(1, 1, 1, 0);

	draw_vase();
	// draw_cylinder(100, 400, 20);

	//glBegin(GL_LINES);
	//for (int i = 0; i < to_draw_points.size(); i++) {
	//	glVertex3d(to_draw_points[i].x, to_draw_points[i].y, to_draw_points[i].z);
	//}
	//glEnd();

	//for (int i = 0; i < 6; i++) {
	//	DrawBezier(points[i]);
	//}

	// DrawBezier(points[0]);

	glutSwapBuffers();
}

void OnMouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		float ox = x - WINDOW_SIZE / 2;
		float oy = y - WINDOW_SIZE / 2;
		points[0].push_back(Vector(ox * 2, -oy * 2, 0, 1));
		cout << ox * 2 << " : " << -oy * 2 << endl;
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		points[0].clear();
	}
}

void main(int argc, char **argv) {
	//float theta = 0;
	//for (float x = 0; x < 3.14; x += 0.1) {
	//	float y = x * sin(x);
	//	cout << y << endl;
	//	Vector v(x, y, 0, 1);
	//	theta += 0.1;
	//	v = transformation.rotate_y(theta).multiplies(transformation.scale(Vector(100, 100, 100, 1))).multiplies(v);
	//	v.showVectorOnConsole();
	//	to_draw_points.push_back(v);
	//}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
	glutCreateWindow("uts grafkom");

	glutIdleFunc(idle);

	glutDisplayFunc(test);

	initCanvas();

	glutMouseFunc(OnMouseClick);

	glutMainLoop();
}
