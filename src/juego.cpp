#include "mundo.h"
#include "freeglut.h"

Mundo world;

//Los callback, funciones que seran llamadas automaticamente por glut cuando sucedan eventos
//No hace falta llamarlas explicitamente
void OnDraw(void); 
void OnTimer(int value); //esta funcion sera llamada cuando transcurra una tiempo
void OnKeyboardDown(unsigned char key, int x, int y); //cuando se pulse una tecla
void OnMouseClick(int button, int state, int x, int y);

int main(int argc, char* argv[]){
	//Inicializar el gestor de ventanas GLUT y crear la ventana
	glutInit(&argc, argv);
	glutInitWindowSize(1408, 792);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("AjedrezKramnik");

	glutSetWindow(glutGetWindow());
	glutPositionWindow(52, 0);
	//glutFullScreen();

	//Iluminación
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	glShadeModel(GL_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Perspectiva
	glMatrixMode(GL_PROJECTION);
	gluPerspective(60.0, 1408.0 / 792.0, 0.1, 50.0);
	//Registrar los callbacks
	glutDisplayFunc(OnDraw);
	glutTimerFunc(25, OnTimer, 0);
	glutKeyboardFunc(OnKeyboardDown);
	glutMouseFunc(OnMouseClick);

	//object.inicializa();
	world.inicializa();

	//Pasar el control a GLUT para que llame a los callbacks
	glutMainLoop();
	return 0;
}
void OnDraw(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	world.dibuja();

	//NO TOCAR 
	glutSwapBuffers();
	//
}
void OnKeyboardDown(unsigned char key, int x, int y) {
	world.tecla(key);
	return;
}
void OnMouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		world.leftClick(x, y);
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		world.rightClick(x, y); 
	}
}
void OnTimer(int value){
	//Código de animacion
	world.rotarOjo();
	OnDraw();

	// NO BORRAR
	glutTimerFunc(30, OnTimer, 0);
	glutPostRedisplay();
}