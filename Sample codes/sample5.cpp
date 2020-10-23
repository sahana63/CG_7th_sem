#include<glut/glut.h>

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
		glColor3f(1.0,0.0,0.0);
		glVertex2i(100,300);
		glVertex2i(201,300);
		glColor3f(0.0,1.0,1.0);
		glVertex2i(50,300);
		glVertex2i(50,30);
	glEnd();
	glFlush();
}

void myInit(){
		glClearColor(1.0,1.0,1.0,1.0);
		glColor3f(1.0,0.0,0.0);
		glLineWidth(2.0);
		gluOrtho2D(0.0,500.0,0.0,500.0);
}

int main(int argc, char** argv){
	glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
	glutCreateWindow("Drawing lines");
	glutDisplayFunc(display);
	myInit();
	glutMainLoop();
}