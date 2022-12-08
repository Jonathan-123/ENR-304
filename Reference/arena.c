// Compile with: gcc arena.c -o arena -lGL -lGLU -lglut
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

#define Lx 20
#define Ly 20

int WAS_IN_X = 1, WAS_IN_Y = 1;

float 
	bug_x=0, 
	bug_y=4, 
	bug_vx = 0.02,
	bug_vy = 0.04,
	X0 = 0,
	X1 = Lx/2,
	X2 = Lx/2,
	X3 = 0,
	Y0 = 0,
	Y1 = 0,
	Y2 = Ly/2,
	Y3 = Ly/3;

void Initialize(void);
void display(void);
void draw_box(void);
void draw_arena(void);
void draw_points(void);
void draw_polynomial(void);
void draw_axes(void);
void draw_bug(float, float);
void animate_bug(void);
void key(unsigned char, int, int);
void Timer (int);

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(200, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Examples");
    glutDisplayFunc(display);  // display function is display
	glutKeyboardFunc(key);     // keystroke interpreter is key
    Initialize();
	Timer(0);
    glutMainLoop();
    return 0;
}

void Initialize(void){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(-Lx, Lx, -Ly, Ly);
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
	draw_axes();
	draw_box();
	draw_arena();
	draw_points();
	draw_polynomial();
	draw_bug(bug_x, bug_y);
    glutSwapBuffers();
	animate_bug();
}

void draw_axes(void){
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
        glVertex2f(-0.8*Lx, 0.0);
        glVertex2f(0.8*Lx, 0.0);
        glVertex2f(0.0, -0.8*Ly);
        glVertex2f(0.0, 0.8*Ly);
    glEnd();
}

void draw_box(void){
    glColor3f(0.0, 0.5, 0.5);
    glRectf(-10.0, 1.0, -5.0, 6.0);
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

void draw_points(void){
    glColor3f(0.0, 0.0, 1.0);
    glPointSize(5.0);        // make the point 5 in width
    glBegin(GL_POINTS);
        glVertex2f(-1.0, -1.0);
        glVertex2f(-2.0, -2.0);
        glVertex2f(-3.0, -3.0);
        glVertex2f(-4.0, -4.0);
        glVertex2f(-5.0, -5.0);
    glEnd();
}

void draw_polynomial(void){
    glColor3f(1.0, 0.0, 1.1);
    glPointSize(2.0);

    float x, y;
    glBegin(GL_POINTS);
        for(x=-70; x < 70; x++){
			y = x*x*x/800 - x*x/100 + x/50 + 1;
			glVertex2f(x/20, y/20);
        }
    glEnd();

}

void draw_bug(float x, float y){
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(20.0);
    glBegin(GL_POINTS);
        glVertex2f(x,y);
    glEnd();
/* for circular bugs
		int sides = 10; 
		float R = 0.2;
		float PI = 3.14;
		glEnable(GL_LINE_SMOOTH);
		glLineWidth(5.0);
		glBegin(GL_LINES);
			glColor4f(0.4, 0.8, 0.9, 1.0);
			for(int i = 0; i <= sides; i++) {
				glVertex2f(x,y);
				glVertex2f( x+R*cos(2*PI*i/sides), y+R*sin(2*PI*i/sides) );
			}
		glEnd();
*/
}

void animate_bug(void){
		// the following animates a black bug
		// the timer function calls the display function 
		// every 5 ms and that is what animates it via
		// the following
		bug_x += bug_vx;
		bug_y += bug_vy;
		if( bug_x >= X0 && bug_x <= X1) WAS_IN_X = 1;
		if( bug_y >= Y0 && bug_y <= Y3 + bug_x*(Y2-Y3)/(X2-X3)) WAS_IN_Y = 1;
		if( bug_x < X0 || bug_x > X1 && WAS_IN_X){ 
			bug_vx = -bug_vx;
			WAS_IN_X = 0;
		}
		if( bug_y < Y0 || bug_y > Y3 + bug_x*(Y2-Y3)/(X2-X3) && WAS_IN_Y){ 
			bug_vy = -bug_vy;
			WAS_IN_Y = 0;
		}
}

void key(unsigned char key, int x, int y){
	switch(key) {
	case 'q': exit(0);
	default: break;
	}
}

void Timer (int iUnused){
	glutPostRedisplay();
	glutTimerFunc(5, Timer, 0);
}

