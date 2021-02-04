#include<gl/glut.h>
#include<stdio.h>

int x1, y1, x2, y2;

// displays a point
void display(int x, int y){
	glBegin(GL_POINTS);
		glVertex2i(x, y);
	glEnd();
}

// implements bresenham's line drawing algorithm
void draw_line(){
	glClear(GL_COLOR_BUFFER_BIT);
	int dx, dy, i, p;
	int incx=1, incy=1, inc1, inc2;
	int x=x1, y=y1;

	dx = x2 - x1;
	dy = y2 - y1;

	if (dx<0){
		dx = -dx;
		incx = -1;
	}
	if (dy<0){
		dy = -dy;
		incy = -1;
	}

	// slope is less than 1
	if (dx>dy){
		p = 2 * dy - dx;			// initial decision parameter
		inc1 = 2 * (dy - dx);		
		inc2 = 2 * dy;
		for (i = 0; i<dx; i++){
			display(x, y);
			if (p >= 0){
				y += incy;
				p += inc1;
			} else
				p += inc2;
			x += incx;

		}
	} 
	// slope is greater than 1
	else{
		p = 2 * dx - dy;			// initial decision parameter
		inc1 = 2 * (dx - dy);
		inc2 = 2 * dx;
		for (i = 0; i<dy; i++){
			display(x, y);
			if (p >= 0){
				x += incx;
				p += inc1;
			}else
				p += inc2;
			y += incy;
		}
	}
	glFlush();
}

void myInit(){
	glClearColor(1, 1, 1, 1);
	glColor3f(0.0, 0.0, 1.0);
	glPointSize(2.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
}

int flag = 0;
void mymouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (flag == 0) {
			x1 = x;
			y1 = 500 - y;
			flag++;
			printf("point (%d,%d)\n", x1, y1);
		}
		else {
			x2 = x;
			y2 = 500 - y;
			printf("point (%d,%d)\n", x2, y2);
			flag = 0;
			draw_line();
		}
	}
}

void display() {}

int main(int argc, char *argv[]){
	printf("Enter points: x1, y1, x2, y2\n");		//For keyboard
	scanf_s("%d%d%d%d", &x1, &y1, &x2, &y2);		//For keyboard
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(5, 5);
	glutCreateWindow("Bresenham's Algorithm");
	//glutMouseFunc(mymouse);						//For mouse
	glutDisplayFunc(draw_line);						//For keyboard
	//glutDisplayFunc(display);						//For Mouse
	myInit();
	glutMainLoop();
}
