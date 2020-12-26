#include<glut/glut.h>
#include<stdio.h>

int m,x=10;
typedef float point[3];
point tetra[4] = { {0,100,-100},{0,0,100},{100,-100,-100},{-100,-100,-100} };

void draw_triangle(point p1, point p2, point p3){
	glVertex3fv(p1);
	glVertex3fv(p2);
	glVertex3fv(p3);

}
void draw_tetra(point p1, point p2, point p3, point p4){
	glColor3f(0.0, 0.0, 0.0);
	draw_triangle(p1, p2, p3);
	glColor3f(1.0, 0.0, 0.0);
	draw_triangle(p1, p3, p4);
	glColor3f(0.0, 0.0, 1.0);
	draw_triangle(p1, p4, p2);
	glColor3f(0.0, 1.0, 0.0);
	draw_triangle(p2, p3, p4);
}
point figure[8]={{0,0,1},{2,0,1},{2,3,1},{0,2,1},{0,0,0},{2,0,0},{2,3,0},{0,2,0}};
void tetrahedron(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(2.0);
	glBegin(GL_QUAD_STRIP);
	 for(int i=0;i<4;i++)
	 	glVertex3fv(figure[i]);
	 glColor3f(0.0, 1.0, 0.0);
		glVertex3fv(figure[7]);
		glVertex3fv(figure[5]);
		glVertex3fv(figure[6]);
		glVertex3fv(figure[7]);
		glVertex3fv(figure[2]);
		glVertex3fv(figure[1]);
	glEnd();
	glFlush();
}

void Rotate(){
	glRotatef(45, 1.0, 0.0, 0.0);
	tetrahedron();
	glFlush();
	glMatrixMode(GL_PROJECTION);
}

void Translate(){
	glTranslatef(20, 10.0,0.0);
	tetrahedron();
	glFlush();
	glMatrixMode(GL_PROJECTION);
}

void Scale(int btn){
	printf("Scale");
	int p;
	if (btn==3) p=2;
	else p=0.5;
	glScalef(p, p,p);
	tetrahedron();
	glFlush();
	glMatrixMode(GL_PROJECTION);
}

void mouse(int btn, int state, int x, int y){
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		Rotate();
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		Translate();
       if (btn==3 || btn==4){
       	Scale(btn);
	// glMatrixMode(GL_PROJECTION);
	// glLoadIdentity();
	// glOrtho(-250.0+x, 250.0+x, -250.0+x, 250.0-x, -250.0+x, 250.0-x);
	// glMatrixMode(GL_MODELVIEW);
}
}

void myReshape(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-10.0, 10.0, -10.0 * (GLfloat)h / (GLfloat)w,
			250.0 * (GLfloat)h / (GLfloat)w, -250.0, 250.0);
	else
		glOrtho(-250.0 * (GLfloat)w / (GLfloat)h,
			250.0 * (GLfloat)w / (GLfloat)h, -250.0, 250.0, -250.0, 250.0);
	glMatrixMode(GL_MODELVIEW);
}

void myinit(){
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argv, char** argc)
{
	glutInit(&argv, argc);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Tetrahedron");
	glutDisplayFunc(tetrahedron);
	glutMouseFunc(mouse);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	myinit();
	glutMainLoop();
}