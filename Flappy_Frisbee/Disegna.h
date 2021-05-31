// Include GLM; libreria matematica per le opengl
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include "ShaderMaker.h"
#include "GestioneEventi.h"
#include <stdlib.h>     /* srand, rand */
#define PI 3.14159265358979323846

typedef struct { float x, y, z, r, g, b, a; } Point;


void disegna_piano(float x, float y, float width, float height, vec4 color_top, vec4 color_bot, Point* piano);

void costruisci_disco(int nTriangles, int step, vec4 color_top, vec4 color_bot, Point* Disco);



void costruisci_ostacolo_quadrato(float x, float y, float width, float height, vec4 color_top, vec4 color_bot, Point* Ostacolo);

void costruisci_ostacolo_cuore(int nTriangles, int step, vec4 color_top, vec4 color_bot, Point* Cuore);

void costruisci_luna(int nTriangles, int step, vec4 color_top, vec4 color_bot, Point* Luna);

