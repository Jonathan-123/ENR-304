// Compile with: gcc balls.c -o balls -lGL -lGLU -lglut -lm
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define Lx 20
#define Ly 20
#define NUM_BALLS 100
#define SIDES_BALLS 10
#define R_BALLS 0.2
#define PI 3.14

float 
	ball_x[NUM_BALLS], 
	ball_y[NUM_BALLS], 
	ball_vx[NUM_BALLS],
	ball_vy[NUM_BALLS],
	X0 = -Lx/2,
	Y0 = -Ly/2,
	X1 = Lx/2,
	Y1 = -Ly/2,
	X2 = Lx/2,
	Y2 = Ly/2,
	X3 = -Lx/2,
	Y3 = Ly/2;

void Initialize(void);
void display(void);
void draw_arena(void);
void draw_ball(float, float);
void animate_ball(void);
void key(unsigned char, int, int);
void Timer (int);

int main(int argc, char *argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Balls");
	glutDisplayFunc(display);// display function is display
	glutKeyboardFunc(key);   // keystroke interpreter is key
	Initialize();
	Timer(0);
	glutMainLoop();
	return 0;
}

void Initialize(void){
	glClearColor(1.0, 1.0, 1.0, 1.0);
	gluOrtho2D(-Lx, Lx, -Ly, Ly);
	for (int k=0; k<NUM_BALLS; k++){
		ball_x[k] = rand()%(Lx/2);
		ball_y[k] = rand()%(Ly/2);
		ball_vx[k] = (rand()%10)/100.0;
		ball_vy[k] = (rand()%10)/100.0;
	}
}

void Timer (int iUnused){
	glutPostRedisplay();
	glutTimerFunc(5, Timer, 0);
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	draw_arena();
	for (int k=0; k<NUM_BALLS; k++){
		draw_ball(ball_x[k], ball_y[k]);
	}
	animate_ball();
	glutSwapBuffers();
}

void draw_arena(void){
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(X0,Y0);
		glVertex2f(X1,Y1);
		glVertex2f(X2,Y2);
		glVertex2f(X3,Y3);
	glEnd();			 
}

void draw_ball(float x, float y){
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(5.0);
	glEnable(GL_LINE_SMOOTH);
/*
	glBegin(GL_POINTS);
		glVertex2f(x, y);
	glEnd();
*/
// for circular balls
	glLineWidth(5.0);
	glBegin(GL_LINES);
		glColor4f(0.2, 0.2, 0.9, 1.0);
		for(int i = 0; i <= SIDES_BALLS; i++) {
			glVertex2f(x,y);
			glVertex2f( x+R_BALLS*cos(2*PI*i/SIDES_BALLS), y+R_BALLS*sin(2*PI*i/SIDES_BALLS) );
		}
	glEnd();
}

void animate_ball(void){
	for (int k=0; k<NUM_BALLS; k++){
		ball_x[k] += ball_vx[k];
		ball_y[k] += ball_vy[k];
		if( ball_x[k] < X0 || ball_x[k] > X1) ball_vx[k] = -ball_vx[k];
		if( ball_y[k] < Y0 || ball_y[k] > Y3) ball_vy[k] = -ball_vy[k];
	}
}

void key(unsigned char key, int x, int y){
	switch(key) {
		case 'q': exit(0);
		default: break;
	}
}
