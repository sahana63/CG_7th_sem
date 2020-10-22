#include<glut/glut.h>
#include<stdio.h>

int m;
typedef float point[3];
point tetra[4] = { {0,100,-100},{0,0,100},{100,-100,-100},{-100,-100,-100} };
void tetrahedron(void);
void myinit(void);
void draw_triangle(point p1, point p2, point p3);

int main(int argv, char** argc)
{
	printf("Enter the number of iterations: ");
	scanf("%d", &m);
	glutInit(&argv, argc);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Seirpinski Gasket");
	glutDisplayFunc(tetrahedron);
	glEnable(GL_DEPTH_TEST);
	myinit();
	glutMainLoop();
}

void draw_triangle(point p1, point p2, point p3)
{

	glVertex3fv(p1);
	glVertex3fv(p2);
	glVertex3fv(p3);

}
void draw_tetra(point p1, point p2, point p3, point p4)
{
	
	glColor3f(1.0, 0.0, 0.0);
	draw_triangle(p1, p2, p3);
	glColor3f(0.0, 1.0, 0.0);
	draw_triangle(p1, p3, p4);
	glColor3f(0.0, 0.0, 1.0);
	draw_triangle(p1, p4, p2);
	glColor3f(0.0, 0.0, 0.0);
	draw_triangle(p2, p3, p4);

}

void divide_tetra(point a, point b, point c,point d, int m)
{
	point mid[6];
	int j;
	if (m > 0) {
		for (j = 0; j < 3; j++) mid[0][j]=(a[j]+b[j])/2;
		for (j = 0; j < 3; j++) mid[1][j]=(a[j]+c[j])/2;
		for (j = 0; j < 3; j++) mid[2][j]=(a[j]+d[j])/2;
		for (j = 0; j < 3; j++) mid[3][j]=(b[j]+c[j])/2;
		for (j = 0; j < 3; j++) mid[4][j]=(c[j]+d[j])/2;
		for (j = 0; j < 3; j++) mid[5][j]=(b[j]+d[j])/2;

		divide_tetra(a,mid[0], mid[1], mid[2], m - 1);
		divide_tetra(mid[0],b,mid[3], mid[5], m - 1);
		divide_tetra(mid[1],mid[3], c, mid[4], m - 1);
		divide_tetra(mid[2],mid[4], d, mid[5], m - 1);

	}
	else
		draw_tetra(a, b, c,d);
}
void myinit()
{
	glClearColor(1, 1, 1, 1);
	glOrtho(-150.0, 150.0, -150.0, 150.0, -150.0, 150.0);
}
void tetrahedron(void)
{
	//myinit();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	divide_tetra(tetra[0], tetra[1], tetra[2],tetra[3], m);
	glEnd();
	glFlush();
}

