// Written by Jonathan 12/7/2022
// simulates spheres with constant x-velocity


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float hours = 4.5;							//amount of time spent on this program
int particles = 16;							//number of particles
int N = 1000;								//number of iterations
double r = 1;								//radius of circle
float dx = 0.01;							//step size along x


int main(){

	float direction[particles];					//stores the direction each particle is travelling
	double inside;								//r squared - x squared
	double x[particles];						//stores the x-coords of each particle
	double y[particles];						//stores the y-coords of each particle
	double Xinitial[particles];					//stores the initial x-coords of each particle
	double R[particles];						//stores the distance from the origin of each particle

	for (int i=0; i<particles; i++){			//sets initial positions of particles
		x[i] = -1*(i+1)*(1/sqrt(2));			//set initial x-coords
		y[i] = (i+1)*(1/sqrt(2));				//set initial y-ccords
		Xinitial[i] = x[i];						//save initial x-position
		R[i] = r*(i+1);							//set radius from origin
		direction[i] = 1;						//set direction of travel
	}

	for (int j=0; j<N; j++){						//number of iterations
		for (int i=0; i<particles; i++){			//iterates through each particle
			x[i] = x[i] + (direction[i]*dx);		//new x[i]
			inside = pow(R[i],2) - pow(x[i],2);		//calculate the inside of sqrt for y[i]
			if (x[i] >= -Xinitial[i]){				//if y value hits a boundary, change direction
				direction[i] =-1;
			}
			if (x[i] <= Xinitial[i]){
				direction[i] =1;
			}
			
			y[i] = sqrt(inside);				//new y[i]
			
			printf("%0.2lf\t%0.2lf\n",x[i],y[i]);
			//printf("x=%0.2lf\ty=%0.2lf\tdirection=%d\n",x[i],y[i],direction);
		}
	}



return 0;
}		//end of main

