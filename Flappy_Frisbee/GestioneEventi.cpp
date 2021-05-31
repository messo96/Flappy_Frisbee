#include "Lib.h"
extern float posx_disco, posy_disco;
extern int width, height;
extern float gapx_disco, gapy_disco;
extern float gapx_ostacolo[nOstacoli], gapy_ostacolo[nOstacoli];
extern bool left, right, up, down;
extern float posx_ostacolo[nOstacoli], posy_ostacolo[nOstacoli];
extern float gapx_ombra, gapy_ombra;
extern float posx_sole, posy_sole;
extern float posx_luna, posy_luna;
extern float rotate_angle_disc;
bool day;

bool colpito;

int life = 0;
int difficult = 5;
int velocity = 20;
extern int r;
float x = 180.0;
float y = 0.0;

#define PI 3.14159265358979323846

void restart() {
	colpito = false;
	posy_disco = float(height / 2);
	gapx_ombra = 20.0;
	gapy_ombra = 10.0;
}

void discDie() {
	if (posy_disco >= gapx_disco) {
		rotate_angle_disc = 90;
		posy_disco-= 10;
	}
}


void move_ostacolo(float *posx, float *posy, float gapx_ostacolo, float gapy_ostacolo) {

	if (*posx <  -gapx_ostacolo) {
		*posx = float(width) + 400;
		r = rand();
		*posy = float(rand() % height / 2);
	}
	else {
		*posx = *posx - difficult;

	}
}

void checkCollision() {
	for (int i = 0; i < nOstacoli; i+=2) { //quadrato
		if(posx_disco < (posx_ostacolo[i] + gapx_ostacolo[i]) &&
			(posx_disco + gapx_disco) > posx_ostacolo[i] &&
			posy_disco < (posy_ostacolo[i] + gapy_ostacolo[i]) &&
			(posy_disco + gapy_disco) >posy_ostacolo[i]) {
			life++;
			colpito = true;
			printf("\nColpito\t n. %i by %i", life, i);
			//exit(0);
		}
	}
	
	for (int i = 1; i < nOstacoli; i += 2) { //cuore
		if (posx_disco < (posx_ostacolo[i] + gapx_ostacolo[i] + 50) &&
			(posx_disco + gapx_disco) > posx_ostacolo[i] &&
			posy_disco < (posy_ostacolo[i] + gapy_ostacolo[i] + 50) &&
			(posy_disco + gapy_disco) >posy_ostacolo[i]) {
			life++;
			colpito = true;
			printf("\nColpito\t n. %i by %i", life, i);
			//exit(0);
		}
	}
}


void daily_sun() {
	if (posx_sole >= float(width-250) || posx_luna >= float(width-250)) {
		x = 180.0;
		y = 0.0;
		posx_sole = 0;
		posy_sole = 0;
		posx_luna = 0;
		posy_luna = 0;

		day = day ? false : true;
	}
	else {
		x -= 0.1;
		y += 0.1;
	}
	
	
	if (day) {
		posx_sole = float(width) - abs(cos(x * 2 * PI / 180.0)) * float(width) + 100.0;
		posy_sole = abs(sin(y * 2 * PI * 2 / 180.0)) * float(height) - 60.0;
	}
	else {
		posx_luna = float(width) - abs(cos(x * 2 * PI / 180.0)) * float(width) + 100.0;
		posy_luna = abs(sin(y * 2 * PI * 2 / 180.0)) * float(height) - 60.0;
	}


	//printf("\nxsole: %f \t ysole: %f\nx: %f \t y: %f", x, y, cos(x * 2 * PI / 180.0), sin(y * 2 * PI / 180.0));
}

void keyboardPressedEvent(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		left = true;
		break;

	case 'd':
		right = true;
		break;

	case 'w':
		up = true;
		break;
	case 's':

		down = true;
		break;

	case 'r':
		restart();
		break;

	case 27:
		exit(0);
		break;

	default:
		break;
	}
}

void keyboardReleasedEvent(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		left = false;
		break;

	case 'd':
		right = false;
		break;

	case 'w':
		up = false;
		break;
	
	case 's':
		down = false;
		break;

	default:
		break;
	}
}
void update(int a)
{
	if (!colpito) {

		if (left && posx_disco > gapx_disco)
			posx_disco -= velocity;

		if (right && posx_disco < (width - gapx_disco))
			posx_disco += velocity;

		if (up && posy_disco < (height / 2 - gapy_disco)) {
			posy_disco += velocity;
			gapx_ombra -= velocity / 10;
			gapy_ombra -= velocity / 10;
		}

		if (down && posy_disco > gapy_disco) {
			posy_disco -= velocity;
			gapx_ombra += velocity / 10;
			gapy_ombra += velocity / 10;
		}

		//printf("\nPosx: %f\tPosy:%f1nPosx ostacolo: %f", posx_disco, posy_disco, posx_ostacolo);
		checkCollision();
		for (int i = 0; i < nOstacoli; i++) {
			move_ostacolo(&posx_ostacolo[i], &posy_ostacolo[i], gapx_ostacolo[i], gapy_ostacolo[i]);
		}
	}
	else
		discDie();

	daily_sun();

	glutPostRedisplay();
	glutTimerFunc(24, update, 0);



}


