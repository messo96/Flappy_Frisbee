// Flappy_Frisbee.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//
#include "Disegna.h" //include lib GLM e GL


using namespace glm;
//parametri keyboard
bool left = false;
bool right = false;
bool up = false;
bool down = false;
int width = 1280;
int height = 720;
float posx_disco = (float(width) * 0.5);
float posy_disco = (float(height)* 0.5);
float gapx_disco = 50.0;
float gapy_disco = 30.0;
float gapx_ombra = 20.0;
float gapy_ombra = 10.0;
float posx_ostacolo[nOstacoli];
float posy_ostacolo[nOstacoli];
float gapx_ostacolo[nOstacoli];
float gapy_ostacolo[nOstacoli];
float gapx_quadrato = 60.0;
float gapy_quadrato = 60.0;
float gapx_cuore = 3.0;
float gapy_cuore = 3.0;
float posx_sole = float(width);
float posy_sole = float(height/2);
float posx_luna = float(width);
float posy_luna = float(height / 2);
float rotate_angle_disc = 0.0;
int r;
 
static unsigned int programId;


unsigned int vertice_piano = 6;
int nTriangles_palla = 30;
int vertice_disco = 6 * nTriangles_palla;
int vertice_ostacolo = 6;
int vertice_ostacolo_cuore = 50 * nTriangles_palla;

vec4 col_cielo_top;
vec4 col_cielo_bot;

// parametri del disco
double delta = 1.5; // forza di gravita
double 	VelocitaVerticale = 20; //velocita verticale (pixel per frame)
double VelocitaOrizzontale = 0; //velocita orizzontale (pixel per frame)


unsigned int VAO_PRATO, VAO_CIELO, VAO_SOLE, VAO_LUNA, VAO_DISCO, VAO_OMBRA_DISCO, VAO_OSTACOLO, VAO_CUORE;
unsigned int VBO_PRATO, VBO_CIELO, VBO_SOLE, VBO_LUNA, VBO_DISCO, VBO_OMBRA_DISCO, VBO_OSTACOLO, VBO_CUORE, MatrixProj, MatModel;


Point* Cielo = new Point[vertice_piano];
Point* Sole = new Point[vertice_disco];
Point* Luna = new Point[vertice_disco];
Point* Prato = new Point[vertice_piano];
Point* Disco = new Point[vertice_disco];
Point* Ombra_Disco = new Point[vertice_disco];
Point* Ostacolo = new Point[vertice_disco];
Point* Cuore = new Point[vertice_ostacolo_cuore];

mat4 Projection;  //Matrice di proiezione
mat4 Model; //Matrice per il cambiamento di sistema di riferimento: da Sistema diriferimento dell'oggetto a sistema di riferimento nel Mondo



void INIT_VAO() {
	GLenum ErrorCheckValue = glGetError();

	char* vertexShader = (char*)"vertexShader_C_M.glsl";
	char* fragmentShader = (char*)"fragmentShader_C_M.glsl";

	programId = ShaderMaker::createProgram(vertexShader, fragmentShader);
	glUseProgram(programId);

	

	// CIELO_________________________
	
	 col_cielo_top = { 0.0, 1.0, 1.0, 1.0 };
	 col_cielo_bot = { 0.8, 1.0, 1.0, 1.0 };

	disegna_piano(0, 0, 1, 1, col_cielo_bot, col_cielo_top, Cielo);


	//Genero un VAO_CIELO
	glGenVertexArrays(1, &VAO_CIELO);
	//Ne faccio il bind (lo collego, lo attivo)
	glBindVertexArray(VAO_CIELO);

	//AL suo interno genero un VBO
	glGenBuffers(1, &VBO_CIELO);

	//Ne faccio il bind (lo collego, lo attivo, assegnandogli il tipo GL_ARRAY_BUFFER)
	glBindBuffer(GL_ARRAY_BUFFER, VBO_CIELO);

	//Carico i dati vertices sulla GPU
	glBufferData(GL_ARRAY_BUFFER, vertice_piano * sizeof(Point), &Cielo[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Scollego il VAO
	glBindVertexArray(0);



	// SOLE_________________________


	vec4 col_sole_top = { 1.0,1.0,1.0,1.0 };
	vec4 col_sole_bot = { 1.0, 0.8627, 0.0, 1.0 }; 
	

	costruisci_disco(nTriangles_palla, 1, col_sole_top, col_sole_bot, Sole);


	//Genero un VAO_SOLE
	glGenVertexArrays(1, &VAO_SOLE);
	//Ne faccio il bind (lo collego, lo attivo)
	glBindVertexArray(VAO_SOLE);

	//AL suo interno genero un VBO
	glGenBuffers(1, &VBO_SOLE);

	//Ne faccio il bind (lo collego, lo attivo, assegnandogli il tipo GL_ARRAY_BUFFER)
	glBindBuffer(GL_ARRAY_BUFFER, VBO_SOLE);

	//Carico i dati vertices sulla GPU
	glBufferData(GL_ARRAY_BUFFER, vertice_disco * sizeof(Point), &Sole[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Scollego il VAO
	glBindVertexArray(0);



	// LUNA_________________________


	vec4 col_luna_top = { 0.6, 0.6, 0.6, 0.8 };
	vec4 col_luna_bot = { 0.7, 0.8, 0.7, 0.8 };


	costruisci_luna(nTriangles_palla, 1, col_luna_top, col_luna_bot, Luna);


	//Genero un VAO_LUNA
	glGenVertexArrays(1, &VAO_LUNA);
	//Ne faccio il bind (lo collego, lo attivo)
	glBindVertexArray(VAO_LUNA);

	//AL suo interno genero un VBO
	glGenBuffers(1, &VBO_LUNA);

	//Ne faccio il bind (lo collego, lo attivo, assegnandogli il tipo GL_ARRAY_BUFFER)
	glBindBuffer(GL_ARRAY_BUFFER, VBO_LUNA);

	//Carico i dati vertices sulla GPU
	glBufferData(GL_ARRAY_BUFFER, vertice_disco * sizeof(Point), &Luna[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Scollego il VAO
	glBindVertexArray(0);



	// PRATO_________________________


	vec4 col_prato_top = { 0.0, 1.0, 0.0, 1.0 };
	vec4 col_prato_bot = { 0.2, 1.0, 0.5, 1.0 };

	disegna_piano(0, 0, 1, 1, col_prato_top, col_prato_bot, Prato);


	//Genero un VAO_PRATO
	glGenVertexArrays(1, &VAO_PRATO);
	//Ne faccio il bind (lo collego, lo attivo)
	glBindVertexArray(VAO_PRATO);

	//AL suo interno genero un VBO
	glGenBuffers(1, &VBO_PRATO);

	//Ne faccio il bind (lo collego, lo attivo, assegnandogli il tipo GL_ARRAY_BUFFER)
	glBindBuffer(GL_ARRAY_BUFFER, VBO_PRATO);

	//Carico i dati vertices sulla GPU
	glBufferData(GL_ARRAY_BUFFER, vertice_piano * sizeof(Point), &Prato[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Scollego il VAO
	glBindVertexArray(0);


	// DISCO_________________________

	vec4 col_disco_top = { 1.0, 1.0, 1.0, 1.0 };
	vec4 col_disco_bot = { 0.8, 0.8, 0.8, 1.0 };

	costruisci_disco(nTriangles_palla, 1, col_disco_top, col_disco_bot, Disco);


	//Genero un VAO_DISCO
	glGenVertexArrays(1, &VAO_DISCO);
	//Ne faccio il bind (lo collego, lo attivo)
	glBindVertexArray(VAO_DISCO);

	//AL suo interno genero un VBO
	glGenBuffers(1, &VBO_DISCO);

	//Ne faccio il bind (lo collego, lo attivo, assegnandogli il tipo GL_ARRAY_BUFFER)
	glBindBuffer(GL_ARRAY_BUFFER, VBO_DISCO);

	//Carico i dati vertices sulla GPU
	glBufferData(GL_ARRAY_BUFFER, vertice_disco * sizeof(Point), &Disco[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Scollego il VAO
	glBindVertexArray(0);

	// OMBRA_________________________

	vec4 col_ombra_top = { 0.5, 0.4, 0.4, 0.7 };
	vec4 col_ombra_bot = { 0.4, 0.3, 0.3, 0.7 };

	costruisci_disco(nTriangles_palla, 1, col_ombra_top, col_ombra_bot, Ombra_Disco);


	//Genero un VAO_DISCO
	glGenVertexArrays(1, &VAO_OMBRA_DISCO);
	//Ne faccio il bind (lo collego, lo attivo)
	glBindVertexArray(VAO_OMBRA_DISCO);

	//AL suo interno genero un VBO
	glGenBuffers(1, &VBO_OMBRA_DISCO);

	//Ne faccio il bind (lo collego, lo attivo, assegnandogli il tipo GL_ARRAY_BUFFER)
	glBindBuffer(GL_ARRAY_BUFFER, VBO_OMBRA_DISCO);

	//Carico i dati vertices sulla GPU
	glBufferData(GL_ARRAY_BUFFER, vertice_disco * sizeof(Point), &Ombra_Disco[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Scollego il VAO
	glBindVertexArray(0);



	// OSTACOLO_________________________

	vec4 col_ostacolo_top = { 0.0, 0.0, 0.0, 1.0 };

	  costruisci_ostacolo_quadrato(0, 0, 1, 1, col_ostacolo_top, col_ostacolo_top, Ostacolo);

	//Genero un VAO_OSTACOLO
	glGenVertexArrays(1, &VAO_OSTACOLO);
	//Ne faccio il bind (lo collego, lo attivo)
	glBindVertexArray(VAO_OSTACOLO);

	//AL suo interno genero un VBO
	glGenBuffers(1, &VBO_OSTACOLO);

	//Ne faccio il bind (lo collego, lo attivo, assegnandogli il tipo GL_ARRAY_BUFFER)
	glBindBuffer(GL_ARRAY_BUFFER, VBO_OSTACOLO);

	//Carico i dati vertices sulla GPU
	glBufferData(GL_ARRAY_BUFFER, vertice_ostacolo * sizeof(Point), &Ostacolo[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Scollego il VAO
	glBindVertexArray(0);


	// CUORE_________________________

	vec4 col_ostacolo_cuore_top = { 1.0, 0.0, 0.0, 1.0 };

	costruisci_ostacolo_cuore(500, 1, col_ostacolo_cuore_top, col_ostacolo_cuore_top, Cuore);

	//Genero un VAO_OSTACOLO_CUORE
	glGenVertexArrays(1, &VAO_CUORE);
	//Ne faccio il bind (lo collego, lo attivo)
	glBindVertexArray(VAO_CUORE);

	//AL suo interno genero un VBO
	glGenBuffers(1, &VBO_CUORE);

	//Ne faccio il bind (lo collego, lo attivo, assegnandogli il tipo GL_ARRAY_BUFFER)
	glBindBuffer(GL_ARRAY_BUFFER, VBO_CUORE);

	//Carico i dati vertices sulla GPU
	glBufferData(GL_ARRAY_BUFFER, vertice_ostacolo_cuore * sizeof(Point), &Cuore[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Scollego il VAO
	glBindVertexArray(0);


	//Definisco il colore che verrà assegnato allo schermo
	glClearColor(0.0, 0.0, 0.0, 0.0);

	Projection = ortho(0.0f, float(width), 0.0f, float(height));


}



void drawScene() {

	//Passo al Vertex Shader il puntatore alla matrice Projection, che sarà associata alla variabile Uniform mat4 Projection
	//all'interno del Vertex shader. Uso l'identificatio MatrixProj

	glUniformMatrix4fv(MatrixProj, 1, GL_FALSE, value_ptr(Projection));

	//Passo al Vertex Shader il puntatore alla matrice Model, che sarà associata alla variabile Uniform mat4 Projection
	//all'interno del Vertex shader. Uso l'identificativo MatModel

	glClear(GL_COLOR_BUFFER_BIT);

	//______________________________________________________________________________________________________________

	//AGGIUNGO CIELO AL MODELLO
	Model = mat4(1.0);
	Model = translate(Model, vec3(0.0, float(height) / 2, 0.0));
	Model = scale(Model, vec3(float(width), float(height) / 2, 1.0));
	glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(Model));

	glBindVertexArray(VAO_CIELO);
	glPointSize(4.0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, vertice_piano);
	glBindVertexArray(0);


	//______________________________________________________________________________________________________________

	//AGGIUNGO SOLE AL MODELLO
	Model = mat4(1.0);
	Model = translate(Model, vec3(posx_sole, posy_sole, 0.0));
	Model = scale(Model, vec3(30.0, 30.0, 1.0));
	glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(Model));

	glBindVertexArray(VAO_SOLE);
	glPointSize(4.0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, vertice_disco);
	glBindVertexArray(0);


	//______________________________________________________________________________________________________________

	//AGGIUNGO LUNA AL MODELLO
	Model = mat4(1.0);
	Model = translate(Model, vec3(posx_luna, posy_luna, 0.0));
	Model = scale(Model, vec3(10.0, 10.0, 1.0));
	Model = rotate(Model, radians(float(-45)), vec3(0.0, 0.0, 1.0));
	glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(Model));

	glBindVertexArray(VAO_LUNA);
	glPointSize(4.0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertice_disco);
	glBindVertexArray(0);



	//______________________________________________________________________________________________________________

	//AGGIUNGO PRATO AL MODELLO
	Model = mat4(1.0);
	Model = scale(Model, vec3(float(width), float(height) / 2, 1.0));
	glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(Model));

	glBindVertexArray(VAO_PRATO);
	glPointSize(4.0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, vertice_piano);
	glBindVertexArray(0);

	//______________________________________________________________________________________________________________
	//AGGIUNGO DISCO AL MODELLO
	Model = mat4(1.0);
	Model = translate(Model, vec3(posx_disco, posy_disco, 1.0));
	Model = scale(Model, vec3(gapx_disco, gapy_disco, 0.0)); 
	Model = rotate(Model, radians(rotate_angle_disc), vec3(0.0, 0.0, 1.0));
	glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(Model));

	glBindVertexArray(VAO_DISCO);
	glPointSize(4.0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, vertice_disco);
	glBindVertexArray(0);



	//______________________________________________________________________________________________________________
	//AGGIUNGO OMBRA AL MODELLO
	Model = mat4(1.0);
	Model = translate(Model, vec3(posx_disco, 20, 1.0));
	Model = scale(Model, vec3(gapx_ombra, gapy_ombra, 0.0));
	glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(Model));

	glBindVertexArray(VAO_OMBRA_DISCO);
	glPointSize(4.0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, vertice_disco);
	glBindVertexArray(0);


	//______________________________________________________________________________________________________________

	
	for (int i = 0; i < nOstacoli; i++) {
		if (i % 2 == 0) {
			//AGGIUNGO OSTACOLO AL MODELLO
			Model = mat4(1.0);
			Model = translate(Model, vec3(posx_ostacolo[i], posy_ostacolo[i], 1.0));
			Model = scale(Model, vec3(gapx_ostacolo[i], gapy_ostacolo[i], 0.0));
			glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(Model));
			glBindVertexArray(VAO_OSTACOLO);
			glPointSize(4.0);
			glDrawArrays(GL_TRIANGLES, 0, vertice_ostacolo);
		}
		else {
			//AGGIUNGO CUORE AL MODELLO
			Model = mat4(1.0);
			Model = translate(Model, vec3(posx_ostacolo[i], posy_ostacolo[i], 1.0));
			Model = scale(Model, vec3(gapx_ostacolo[i], gapy_ostacolo[i], 0.0));
			glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(Model));
			glBindVertexArray(VAO_CUORE);
			glPointSize(4.0);
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDrawArrays(GL_TRIANGLE_FAN, 0, vertice_ostacolo_cuore);
		}
		
		glBindVertexArray(0);
	}
	


	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	srand(time(NULL));
	r = rand();
	for (int i = 0; i < nOstacoli; i++) {
		if (i % 2 == 0) {
			gapx_ostacolo[i] = gapx_quadrato;
			gapy_ostacolo[i] = gapy_quadrato;
		}
		else {
			gapx_ostacolo[i] = gapx_cuore;
			gapy_ostacolo[i] = gapy_cuore;
		}
		posx_ostacolo[i] = float(width) + 400*i;
		posy_ostacolo[i] = float(rand() % height / 2);
	}




	glutInit(&argc, argv);

	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(width, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Flappy Frisbee 2D");
	glutDisplayFunc(drawScene);
	//Evento tastiera tasi premuti
	glutKeyboardFunc(keyboardPressedEvent);
	//Evento tastiera tasto rilasciato

	glutKeyboardUpFunc(keyboardReleasedEvent);

	

	//gestione animazione
	glutTimerFunc(66, update, 0);

	glewExperimental = GL_TRUE;
	glewInit();

	INIT_VAO();
	//Chiedo che mi venga restituito l'identificativo della variabile uniform mat4 Projection (in vertex shader).
	//QUesto identificativo sarà poi utilizzato per il trasferimento della matrice Projection al Vertex Shader
	MatrixProj = glGetUniformLocation(programId, "Projection");
	//Chiedo che mi venga restituito l'identificativo della variabile uniform mat4 Model (in vertex shader)
	//QUesto identificativo sarà poi utilizzato per il trasferimento della matrice Model al Vertex Shader
	MatModel = glGetUniformLocation(programId, "Model");


	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutMainLoop();
}
