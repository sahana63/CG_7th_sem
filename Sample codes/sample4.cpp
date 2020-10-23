#include<glut/glut.h>

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
		glVertex2i(10,10);
		glVertex2i(10,490);
		glVertex2i(490,10);
		glVertex2i(250,250);
		glVertex2i(490,490);
	glEnd();
	glFlush();
}

void myInit(){
		glClearColor(0.0,0.0,1.0,1.0);
		glColor3f(0.0,1.0,1.0);
		glPointSize(10.0);
		gluOrtho2D(0.0,500.0,0.0,500.0);
}

int main(int argc, char** argv){
	glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
	glutCreateWindow("Sample 4");
	glutDisplayFunc(display);
	myInit();
	glutMainLoop();
}