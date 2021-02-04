#include<gl/glut.h>
#include<stdio.h>
#include<math.h>

int xc, yc, r;
int rx, ry, xce, yce;
int flag=0;

// plots the points of a circle according to 8-fold symmetry
void draw_circle(int xc, int yc, int x, int y){
	glBegin(GL_POINTS);
		glVertex2i(xc + x, yc + y);
		glVertex2i(xc - x, yc + y);
		glVertex2i(xc + x, yc - y);
		glVertex2i(xc - x, yc - y);
		glVertex2i(xc + y, yc + x);
		glVertex2i(xc - y, yc + x);
		glVertex2i(xc + y, yc - x);
		glVertex2i(xc - y, yc - x);
	glEnd();

}

// implements Bresenham's circle drawing algorithm
void circle_bres(){
	glClear(GL_COLOR_BUFFER_BIT);
	int x = 0, y = r;

	//initial decision parameter
	int d = 3 - 2 * r;
	while (x <= y){
		draw_circle(xc, yc, x, y);
		if (d < 0)
			d = d + 4 * x + 6;
		else{
			d = d + 4 * (x - y) + 10;
			y--;
		}
		x++;
	}
	//glLineWidth(3.0);
	// glBegin(GL_LINES);
	// 	glColor3f(1,0,0);
	// 	glVertex2i(xc, yc);
	// 	glVertex2i(xc + x, yc + y);
	// 			glVertex2i(xc, yc);
	// 	glVertex2i(xc - x, yc + y);
	// 			glVertex2i(xc, yc);
	// 	glVertex2i(xc + x, yc - y);
	// 			glVertex2i(xc, yc);
	// 	glVertex2i(xc - x, yc - y);
	// 			glVertex2i(xc, yc);
	// 	glVertex2i(xc + y, yc + x);
	// 			glVertex2i(xc, yc);
	// 	glVertex2i(xc - y, yc + x);
	// 			glVertex2i(xc, yc);
	// 	glVertex2i(xc + y, yc - x);
	// 			glVertex2i(xc, yc);
	// 	glVertex2i(xc - y, yc - x);
	// glEnd();

	glFlush();
}

/*
int p1_x, p2_x, p1_y, p2_y;
int point1_done = 0;

void myMouseFunccircle(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && point1_done == 0)
	{
		p1_x = x - 250;
		p1_y = 250 - y;
		point1_done = 1;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		p2_x = x - 250;
		p2_y = 250 - y;
		xc = p1_x;
		yc = p1_y;
		float exp = (p2_x - p1_x) * (p2_x - p1_x) + (p2_y - p1_y) * (p2_y - p1_y);
		r = (int)(sqrt(exp));
		circlebres();
		point1_done = 0;
	}
}
*/

// plots the points of a ellipse according to 4-fold symmetry
void draw_ellipse(int xce, int yce, int x, int y){
	glBegin(GL_POINTS);
		glVertex2i(x + xce, y + yce);
		glVertex2i(-x + xce, y + yce);
		glVertex2i(x + xce, -y + yce);
		glVertex2i(-x + xce, -y + yce);
	glEnd();
}

// implements mid point ellipse drawing algorithm
void mid_point_ellipse(){
	glClear(GL_COLOR_BUFFER_BIT);
	float dx, dy, d1, d2, x=0, y=ry;

	// Initial decision parameter of region 1 
	d1 = (ry * ry) - (rx * rx * ry) + (0.25 * rx * rx);
	dx = 2 * ry * ry * x;
	dy = 2 * rx * rx * y;

	// For region 1 
	while (dx < dy){
		draw_ellipse(xce, yce, x, y);
		if (d1 < 0){
			x++;
			dx = dx + (2 * ry * ry);
			d1 = d1 + dx + (ry * ry);
		}else{
			x++;
			y--;
			dx = dx + (2 * ry * ry);
			dy = dy - (2 * rx * rx);
			d1 = d1 + dx - dy + (ry * ry);
		}
	}

	// Decision parameter of region 2 
	d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5))) +
		((rx * rx) * ((y - 1) * (y - 1))) -
		(rx * rx * ry * ry);

	// region 2
	while (y >= 0){
		draw_ellipse(xce, yce, x, y);
		if (d2 > 0){
			y--;
			dy = dy - (2 * rx * rx);
			d2 = d2 + (rx * rx) - dy;
		}else{
			y--;
			x++;
			dx = dx + (2 * ry * ry);
			dy = dy - (2 * rx * rx);
			d2 = d2 + dx - dy + (rx * rx);
		}
	}
	glFlush();
}

/*int p1e_x, p2e_x, p1e_y, p2e_y, p3e_x, p3e_y;
int point1e_done = 0;
void myMouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && point1e_done == 0)
	{
		p1e_x = x - 250;
		p1e_y = 250 - y;
		xce = p1e_x;
		yce = p1e_y;
		point1e_done = 1;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && point1e_done == 1)
	{
		p2e_x = x - 250;
		p2e_y = 250 - y;
		float exp = (p2e_x - p1e_x) * (p2e_x - p1e_x) + (p2e_y - p1e_y) * (p2e_y - p1e_y);
		rx = (int)(sqrt(exp));
		//midptellipse();
		point1e_done = 2;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && point1e_done == 2)
	{
		p3e_x = x - 250;
		p3e_y = 250 - y;
		float exp = (p3e_x - p1e_x) * (p3e_x - p1e_x) + (p3e_y - p1e_y) * (p3e_y - p1e_y);
		ry = (int)(sqrt(exp));
		midptellipse();
		point1e_done = 0;
	}
}

void myDrawing()
{ }
void myDrawingc()
{ }*/

void myReshape(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		gluOrtho2D(-250.0, 250.0, -250.0 * (GLfloat)h / (GLfloat)w,
			250.0 * (GLfloat)h / (GLfloat)w);
	else
		gluOrtho2D(-250.0 * (GLfloat)w / (GLfloat)h,
			250.0 * (GLfloat)w / (GLfloat)h, -250.0, 250.0);
	glMatrixMode(GL_MODELVIEW);
}

void minit(){
	glClearColor(1, 1, 1, 1);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(3.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-250, 250, -250, 250);
}

int main(int argc, char* argv[]){
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	/* 
	//FOR MOUSE
	int id1 = glutCreateWindow("Circle");
	glutSetWindow(id1);
	glutMouseFunc(myMouseFunccircle);
	glutDisplayFunc(myDrawingc);
	minit();
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(600, 100);
	int id2 = glutCreateWindow("Ellipse");
	glutSetWindow(id2);
	glutMouseFunc(myMouseFunc);
	glutDisplayFunc(myDrawing);
	//END MOUSE 
	*/ 
	//FOR KEYBOARD
	printf("Enter 1 to draw circle , 2 to draw ellipse\n");
	int ch;
	scanf_s("%d",&ch);
	switch(ch){
		case 1: 
			printf_s("Enter coordinates of centre of circle and radius\n");
			scanf_s("%d%d%d",&xc,&yc,&r);
			glutCreateWindow("Circle");
			glutDisplayFunc(circle_bres);
			break;
		case 2: 
			printf_s("Enter coordinates of centre of standard ellipse and major and minor radius\n");
			scanf_s("%d%d%d%d",&xce,&yce,&rx,&ry);
			glutCreateWindow("Ellipse");
			glutDisplayFunc(mid_point_ellipse);
			break;
	}
	//END KEYBOARD 
	glutReshapeFunc(myReshape);
	minit();
	glutMainLoop();
	}
