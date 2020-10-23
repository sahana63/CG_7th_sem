#include<glut/glut.h>

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_LOOP);
		glVertex2i(100,100);
		glVertex2i(100,300);
		glVertex2i(300,300);
		glVertex2i(300,100);
	glEnd();
	glFlush();
}

void myInit(){
		glClearColor(0.0,0.0,1.0,1.0);
		glColor3f(1.0,1.0,0.0);
		glLineWidth(4.0);
		gluOrtho2D(0.0,500.0,0.0,500.0);
}

int main(int argc, char** argv){
	glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
	glutCreateWindow("Line loop");
	glutDisplayFunc(display);
	myInit();
	glutMainLoop();
}