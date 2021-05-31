#include "Disegna.h"



void disegna_piano(float x, float y, float width, float height, vec4 color_top, vec4 color_bot, Point* piano)
{

	piano[0].x = x;
	piano[0].y = y;
	piano[0].z = 0;
	piano[0].r = color_bot.r; piano[0].g = color_bot.g; piano[0].b = color_bot.b; piano[0].a = color_bot.a;


	piano[1].x = x + width;
	piano[1].y = y;
	piano[1].z = 0;
	piano[1].r = color_top.r; piano[1].g = color_top.g; piano[1].b = color_top.b; piano[1].a = color_top.a;


	piano[2].x = x + width;
	piano[2].y = y + height;
	piano[2].z = 0;
	piano[2].r = color_bot.r; piano[2].g = color_bot.g; piano[2].b = color_bot.b; piano[2].a = color_bot.a;


	piano[3].x = x + width;
	piano[3].y = y + height;
	piano[3].z = 0;
	piano[3].r = color_bot.r; piano[3].g = color_bot.g; piano[3].b = color_bot.b; piano[3].a = color_bot.a;

	piano[4].x = x;
	piano[4].y = y + height;
	piano[4].z = 0;
	piano[4].r = color_top.r; piano[4].g = color_top.g; piano[4].b = color_top.b; piano[4].a = color_top.a;


	piano[5].x = x;
	piano[5].y = y;
	piano[5].z = 0;
	piano[5].r = color_bot.r; piano[5].g = color_bot.g; piano[5].b = color_bot.b; piano[5].a = color_bot.a;
}

void costruisci_disco(int nTriangles, int step, vec4 color_top, vec4 color_bot, Point* Disco) {
	int i;
	float stepA = (2 * PI) / nTriangles;


	int componenti = 0;
	for (i = 0; i < nTriangles; i += step)
	{
		Disco[componenti].x = cos((double)i * stepA);
		Disco[componenti].y = sin((double)i * stepA);
		Disco[componenti].z = 0.0;
		Disco[componenti].r = color_top.r;
		Disco[componenti].g = color_top.g;
		Disco[componenti].b = color_top.b;
		Disco[componenti].a = color_top.a;
		Disco[componenti + 1].x = cos((double)(i + 1) * stepA);
		Disco[componenti + 1].y = sin((double)(i + 1) * stepA);
		Disco[componenti + 1].z = 0.0;
		Disco[componenti + 1].r = color_top.r; Disco[componenti + 1].g = color_top.g; Disco[componenti + 1].b = color_top.b; Disco[componenti + 1].a = color_top.a;

		Disco[componenti + 2].x = 0.0;
		Disco[componenti + 2].y = 0.0;
		Disco[componenti + 2].z = 0.0;
		Disco[componenti + 2].r = color_bot.r; Disco[componenti + 2].g = color_bot.g; Disco[componenti + 2].b = color_bot.b; Disco[componenti + 2].a = color_bot.a;

		componenti += 3;

	}
}



void costruisci_ostacolo_quadrato(float x, float y, float width, float height, vec4 color_top, vec4 color_bot, Point* Ostacolo) {

	Ostacolo[0].x = x;
	Ostacolo[0].y = y;
	Ostacolo[0].z = 0;
	Ostacolo[0].r = color_bot.r; Ostacolo[0].g = color_bot.g; Ostacolo[0].b = color_bot.b; Ostacolo[0].a = color_bot.a;


	Ostacolo[1].x = x + width;
	Ostacolo[1].y = y;
	Ostacolo[1].z = 0;
	Ostacolo[1].r = color_top.r; Ostacolo[1].g = color_top.g; Ostacolo[1].b = color_top.b; Ostacolo[1].a = color_top.a;


	Ostacolo[2].x = x + width;
	Ostacolo[2].y = y + height;
	Ostacolo[2].z = 0;
	Ostacolo[2].r = color_bot.r; Ostacolo[2].g = color_bot.g; Ostacolo[2].b = color_bot.b; Ostacolo[2].a = color_bot.a;


	Ostacolo[3].x = x + width;
	Ostacolo[3].y = y + height;
	Ostacolo[3].z = 0;
	Ostacolo[3].r = color_bot.r; Ostacolo[3].g = color_bot.g; Ostacolo[3].b = color_bot.b; Ostacolo[3].a = color_bot.a;

	Ostacolo[4].x = x;
	Ostacolo[4].y = y + height;
	Ostacolo[4].z = 0;
	Ostacolo[4].r = color_bot.r; Ostacolo[4].g = color_bot.g; Ostacolo[4].b = color_bot.b; Ostacolo[4].a = color_bot.a;

	Ostacolo[5].x = x;
	Ostacolo[5].y = y;
	Ostacolo[5].z = 0;
	Ostacolo[5].r = color_bot.r; Ostacolo[5].g = color_bot.g; Ostacolo[5].b = color_bot.b; Ostacolo[5].a = color_bot.a;

}

void costruisci_ostacolo_cuore(int nTriangles, int step, vec4 color_top, vec4 color_bot, Point* Cuore) {
	int i;
	float stepA = (2 * PI) / nTriangles;


	int componenti = 0;
	for (i = 0; i < nTriangles; i += step)
	{
		Cuore[componenti].x = 16 * pow(sin((double)i * stepA), 3);
		Cuore[componenti].y = 13 * cos((double)i * stepA) - 5 * cos(2 * (double)i * stepA) - 2 * cos(3 * (double)i * stepA) - cos(4 * (double)i * stepA);
		Cuore[componenti].z = 0.0;
		Cuore[componenti].r = color_top.r;
		Cuore[componenti].g = color_top.g;
		Cuore[componenti].b = color_top.b;
		Cuore[componenti].a = color_top.a;

		Cuore[componenti + 1].x = 16 * pow(sin((double)i * stepA), 3);
		Cuore[componenti + 1].y = 13 * cos((double)(i + 1) * stepA) - 5 * cos(2 * (double)(i + 1) * stepA) - 2 * cos(3 * (double)(i + 1) * stepA) - cos(4 * (double)(i + 1) * stepA);
		Cuore[componenti + 1].z = 0.0;
		Cuore[componenti + 1].r = color_top.r; Cuore[componenti + 1].g = color_top.g; Cuore[componenti + 1].b = color_top.b; Cuore[componenti + 1].a = color_top.a;

		Cuore[componenti + 2].x = 16 * pow(sin((double)i * stepA), 3);
		Cuore[componenti + 2].y = 13 * cos((double)(i + 1) * stepA) - 5 * cos(2 * (double)(i + 1) * stepA) - 2 * cos(3 * (double)(i + 1) * stepA) - cos(4 * (double)(i + 1) * stepA);
		Cuore[componenti + 2].z = 0.0;
		Cuore[componenti + 2].r = color_bot.r; Cuore[componenti + 2].g = color_bot.g; Cuore[componenti + 2].b = color_bot.b; Cuore[componenti + 2].a = color_bot.a;

		componenti += 3;

	}
}

void costruisci_luna(int nTriangles, int step, vec4 color_top, vec4 color_bot, Point* Luna) {
	int i;
	float stepA = (2 * PI) / nTriangles;


	int componenti = 0;
	for (i = 0; i < nTriangles; i += step)
	{
		Luna[componenti].x = 3 * sin((double)i * stepA);
		Luna[componenti].y = 0.5 - cos(2 * (double)i * stepA) - cos((double)i * stepA);
		Luna[componenti].z = 0.0;
		Luna[componenti].r = color_top.r;
		Luna[componenti].g = color_top.g;
		Luna[componenti].b = color_top.b;
		Luna[componenti].a = color_top.a;

		Luna[componenti + 1].x = 3 * sin((double)i * stepA);
		Luna[componenti + 1].y = 0.5 - cos(2 * (double)i * stepA) - cos((double)i * stepA);
		Luna[componenti + 1].z = 0.0;
		Luna[componenti + 1].r = color_top.r; Luna[componenti + 1].g = color_top.g; Luna[componenti + 1].b = color_top.b; Luna[componenti + 1].a = color_top.a;

		Luna[componenti + 2].x = 3 * sin((double)i * stepA);
		Luna[componenti + 2].y = 0.5 - cos(2 * (double)i * stepA) - cos((double)i * stepA);
		Luna[componenti + 2].z = 0.0;
		Luna[componenti + 2].r = color_bot.r; Luna[componenti + 2].g = color_bot.g; Luna[componenti + 2].b = color_bot.b; Luna[componenti + 2].a = color_bot.a;

		componenti += 3;

	}
}

