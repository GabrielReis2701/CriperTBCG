#include <GL/gl.h>
#include <iostream>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "glut.h"
#include "geometry.h"
#include <stdlib.h>
#include "tgaload.h"
/* Definições da câmera */
#define y_min 60
#define ro_min 120
#define MAX_NO_TEXTURES 6
#define CUBE_TEXTURE 0

GLfloat cor_luz0[]        = { 2.0, 2.0, 2.0, 1.0};  // componentes de luz para reflexão difusa e especular
GLfloat cor_luz0_amb[]    = { 0.3, 0.3, 0.3, 1.0}; 
GLfloat mat_a_brilho[]    = { 50.0 };

GLUquadric* sphere = gluNewQuadric();

GLuint texture_id[MAX_NO_TEXTURES];


float eyex = 0, eyey = y_min, eyez = ro_min;
float angle = 0,anglex = 0,anglez = 0,angleMX=-60,angleMY=-30,angleMz=0;
int aux=0;

void initTexture (void)
{
	glBindTexture ( GL_TEXTURE_2D, texture_id[0] );
	image_t temp_image0;
	tgaLoad  ( "cabeca.tga", &temp_image0, TGA_FREE | TGA_LOW_QUALITY );
	
	glBindTexture ( GL_TEXTURE_2D, texture_id[1] );
	image_t temp_image1;
	tgaLoad  ( "cabeca_lado.tga", &temp_image1, TGA_FREE | TGA_LOW_QUALITY );
	
	glBindTexture ( GL_TEXTURE_2D, texture_id[2] );
	image_t temp_image2;
	tgaLoad  ( "corpo.tga", &temp_image2, TGA_FREE | TGA_LOW_QUALITY );
	
	glBindTexture ( GL_TEXTURE_2D, texture_id[3] );
	image_t temp_image3;
	tgaLoad  ( "pe.tga", &temp_image3, TGA_FREE | TGA_LOW_QUALITY );
	
	glBindTexture ( GL_TEXTURE_2D, texture_id[4] );
	image_t temp_image4;
	tgaLoad  ( "pe_tras.tga", &temp_image4, TGA_FREE | TGA_LOW_QUALITY );
	
}
void make_tex(void){
    unsigned char data[256][256][3];
    for (int y = 0; y < 255; y++) {
		for (int x = 0; x < 255; x++) {
	    unsigned char *p = data[y][x];
	    p[0] = p[1] = p[2] = (x ^ y) & 8 ? 255 : 0;
		}
	}
   
    glGenTextures (6, texture_id);
	glBindTexture ( GL_TEXTURE_2D, texture_id[0] );
	glBindTexture ( GL_TEXTURE_2D, texture_id[1] );
	glBindTexture ( GL_TEXTURE_2D, texture_id[2] );
	glBindTexture ( GL_TEXTURE_2D, texture_id[3] );
	glBindTexture ( GL_TEXTURE_2D, texture_id[4] );
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, (const GLvoid *) data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
}
void drawMBat(){
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture ( GL_TEXTURE_2D, texture_id[0] );
	//CABEÇA
	
	glBegin(GL_POLYGON);//FRENTE
	glTexCoord2f(0.0, 0.0);glVertex3f(-1,7,1.5);//A
	glTexCoord2f(1.0, 0.0);glVertex3f(1,7,1.5);//B
	glTexCoord2f(1.0, 1.0);glVertex3f(1,5,1.5);//C
	glTexCoord2f(0.0, 1.0);glVertex3f(-1,5,1.5);//D
	glEnd();
	
	glDisable(GL_TEXTURE_2D); 
	
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture ( GL_TEXTURE_2D, texture_id[1] );
	
	glBegin(GL_POLYGON);//LADO DIR
	glTexCoord2f(0.0, 0.0);glVertex3f(1,7,1.5);//B
	glTexCoord2f(1.0, 0.0);glVertex3f(1,7,-0.5);//B
	glTexCoord2f(1.0, 1.0);glVertex3f(1,5,-0.5);//C
	glTexCoord2f(0.0, 1.0);glVertex3f(1,5,1.5);//C
	glEnd();
	
	glBegin(GL_POLYGON);//LADO ESQ
	glTexCoord2f(0.0, 0.0);glVertex3f(-1,7,1.5);//A
	glTexCoord2f(1.0, 0.0);glVertex3f(-1,7,-0.5);//A
	glTexCoord2f(1.0, 1.0);glVertex3f(-1,5,-0.5);//D
	glTexCoord2f(0.0, 1.0);glVertex3f(-1,5,1.5);//D
	glEnd();
	
	glBegin(GL_POLYGON);//TRAS
	glTexCoord2f(0.0, 0.0);glVertex3f(-1,7,-0.5);//A
	glTexCoord2f(1.0, 0.0);glVertex3f(1,7,-0.5);//B
	glTexCoord2f(1.0, 1.0);glVertex3f(1,5,-0.5);//C
	glTexCoord2f(0.0, 1.0);glVertex3f(-1,5,-0.5);//D
	glEnd();
	
	glBegin(GL_POLYGON);//CIMA
	glTexCoord2f(0.0, 0.0);glVertex3f(-1,7,1.5);//A
	glTexCoord2f(1.0, 0.0);glVertex3f(-1,7,-0.5);//A
	glTexCoord2f(1.0, 1.0);glVertex3f(1,7,-0.5);//B
	glTexCoord2f(0.0, 1.0);glVertex3f(1,7,1.5);//B
	
	glBegin(GL_POLYGON);//Baixo
	glTexCoord2f(0.0, 0.0);glVertex3f(1,5,1.5);//C
	glTexCoord2f(1.0, 0.0);glVertex3f(1,5,-0.5);//C
	glTexCoord2f(1.0, 1.0);glVertex3f(-1,5,-0.5);//D
	glTexCoord2f(0.0, 1.0);glVertex3f(-1,5,1.5);//D
	
	glDisable(GL_TEXTURE_2D); 
	
	//CORPO
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture ( GL_TEXTURE_2D, texture_id[2] );
	
	glBegin(GL_POLYGON);//FRENTE
	glTexCoord2f(0.0, 0.0);glVertex3f(-0.65,5,1);//E
	glTexCoord2f(1.0, 0.0);glVertex3f(0.65,5,1);//F
	glTexCoord2f(1.0, 1.0);glVertex3f(0.65,2,1);//G
	glTexCoord2f(0.0, 1.0);glVertex3f(-0.65,2,1);//H
	glEnd();
	
	glBegin(GL_POLYGON);//BAIXO
	glTexCoord2f(0.0, 0.0);glVertex3f(0.65,2,1);//G
	glTexCoord2f(1.0, 0.0);glVertex3f(0.65,2,0);//G
	glTexCoord2f(1.0, 1.0);glVertex3f(-0.65,2,0);//H
	glTexCoord2f(0.0, 1.0);glVertex3f(-0.65,2,1);//H
	glEnd();
	
	glBegin(GL_POLYGON);//TRAS
	glTexCoord2f(0.0, 0.0);glVertex3f(-0.65,5,0);//E
	glTexCoord2f(1.0, 0.0);glVertex3f(0.65,5,0);//F
	glTexCoord2f(1.0, 1.0);glVertex3f(0.65,2,0);//G
	glTexCoord2f(0.0, 1.0);glVertex3f(-0.65,2,0);//H
	glEnd();
	
	glBegin(GL_POLYGON);//DIR
	glTexCoord2f(0.0, 0.0);glVertex3f(0.65,5,0);//F
	glTexCoord2f(1.0, 0.0);glVertex3f(0.65,5,1);//F
	glTexCoord2f(1.0, 1.0);glVertex3f(0.65,2,1);//G
	glTexCoord2f(0.0, 1.0);glVertex3f(0.65,2,0);//G
	glEnd();
	
	glBegin(GL_POLYGON);//ESQ
	glTexCoord2f(0.0, 0.0);glVertex3f(-0.65,5,0);//E
	glTexCoord2f(1.0, 0.0);glVertex3f(-0.65,5,1);//E
	glTexCoord2f(1.0, 1.0);glVertex3f(-0.65,2,1);//H
	glTexCoord2f(0.0, 1.0);glVertex3f(-0.65,2,0);//H
	glEnd();
	
	//BRACO ESQ
	
	glBegin(GL_POLYGON);//FRENTE
	glTexCoord2f(0.0, 0.0);glVertex3f(-1,4.51,1);//Q
	glTexCoord2f(1.0, 0.0);glVertex3f(-0.65,4.51,1);//P
	glTexCoord2f(1.0, 1.0);glVertex3f(-0.65,2.62,1);//S
	glTexCoord2f(0.0, 1.0);glVertex3f(-1,2.62,1);//R
	glEnd();
	
	glBegin(GL_POLYGON);//TRAS
	glTexCoord2f(0.0, 0.0);glVertex3f(-1,4.51,0);//Q
	glTexCoord2f(1.0, 0.0);glVertex3f(-0.65,4.51,0);//P
	glTexCoord2f(1.0, 1.0);glVertex3f(-0.65,2.62,0);//S
	glTexCoord2f(0.0, 1.0);glVertex3f(-1,2.62,0);//R
	glEnd();
	
	glBegin(GL_POLYGON);//LADO ESQ
	glTexCoord2f(0.0, 0.0);glVertex3f(-1,4.51,0);//Q
	glTexCoord2f(1.0, 0.0);glVertex3f(-1,4.51,1);//Q
	glTexCoord2f(1.0, 1.0);glVertex3f(-1,2.62,1);//R
	glTexCoord2f(0.0, 1.0);glVertex3f(-1,2.62,0);//R
	glEnd();
	
	//BRACO DIR
	
	glBegin(GL_POLYGON);//FRENTE
	glTexCoord2f(0.0, 0.0);glVertex3f(1,4.51,1);//M
	glTexCoord2f(1.0, 0.0);glVertex3f(0.65,4.51,1);//L
	glTexCoord2f(1.0, 1.0);glVertex3f(0.65,2.62,1);//O
	glTexCoord2f(0.0, 1.0);glVertex3f(1,2.62,1);//N
	glEnd();
	
	glBegin(GL_POLYGON);//TRAS
	glTexCoord2f(0.0, 0.0);glVertex3f(1,4.51,0);//M
	glTexCoord2f(1.0, 0.0);glVertex3f(0.65,4.51,0);//L
	glTexCoord2f(1.0, 1.0);glVertex3f(0.65,2.62,0);//O
	glTexCoord2f(0.0, 1.0);glVertex3f(1,2.62,0);//N
	glEnd();
	
	glBegin(GL_POLYGON);//LADO ESQ
	glTexCoord2f(0.0, 0.0);glVertex3f(1,4.51,0);//M
	glTexCoord2f(1.0, 0.0);glVertex3f(1,4.51,1);//M
	glTexCoord2f(1.0, 1.0);glVertex3f(1,2.62,1);//N
	glTexCoord2f(0.0, 1.0);glVertex3f(1,2.62,0);//N
	glEnd();
	
	glDisable(GL_TEXTURE_2D); 
	
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture ( GL_TEXTURE_2D, texture_id[3] );
	
	
	glBegin(GL_POLYGON);//PÉ FRENTE
	glTexCoord2f(0.0, 0.0);glVertex3f(-0.65,2,2);//H
	glTexCoord2f(1.0, 0.0);glVertex3f(0.65,2,2);//G
	glTexCoord2f(1.0, 1.0);glVertex3f(0.65,0,2);//K
	glTexCoord2f(0.0, 1.0);glVertex3f(-0.65,0,2);//J
	glEnd();
	
	glBegin(GL_POLYGON);//PÉ TRAS FRENTE
	glTexCoord2f(0.0, 0.0);glVertex3f(-0.65,2,0);//H
	glTexCoord2f(1.0, 0.0);glVertex3f(0.65,2,0);//G
	glTexCoord2f(1.0, 1.0);glVertex3f(0.65,0,0);//K
	glTexCoord2f(0.0, 1.0);glVertex3f(-0.65,0,0);//J
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
	
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture ( GL_TEXTURE_2D, texture_id[4] );
	
	//PÉ FRENTE
	 
	glBegin(GL_POLYGON);//TRAS
	glTexCoord2f(0.0, 0.0);glVertex3f(-0.65,2,1);//H
	glTexCoord2f(1.0, 0.0);glVertex3f(0.65,2,1);//G
	glTexCoord2f(1.0, 1.0);glVertex3f(0.65,0,1);//K
	glTexCoord2f(0.0, 1.0);glVertex3f(-0.65,0,1);//J
	glEnd();
	
	
	glBegin(GL_POLYGON);//CIMA
	glTexCoord2f(0.0, 0.0);glVertex3f(-0.65,2,2);//H
	glTexCoord2f(1.0, 0.0);glVertex3f(-0.65,2,1);//H
	glTexCoord2f(1.0, 1.0);glVertex3f(0.65,2,1);//G
	glTexCoord2f(0.0, 1.0);glVertex3f(0.65,2,2);//G
	glEnd();
	
	glBegin(GL_POLYGON);//ESQ
	glTexCoord2f(0.0, 0.0);glVertex3f(-0.65,2,2);//H
	glTexCoord2f(1.0, 0.0);glVertex3f(-0.65,2,1);//H
	glTexCoord2f(1.0, 1.0);glVertex3f(-0.65,0,1);//J
	glTexCoord2f(0.0, 1.0);glVertex3f(-0.65,0,2);//J
	glEnd();
	
	glBegin(GL_POLYGON);//DIR
	glTexCoord2f(0.0, 0.0);glVertex3f(0.65,2,2);//G
	glTexCoord2f(1.0, 0.0);glVertex3f(0.65,2,1);//G
	glTexCoord2f(1.0, 1.0);glVertex3f(0.65,0,1);//K
	glTexCoord2f(0.0, 1.0);glVertex3f(0.65,0,2);//K
	glEnd();
	
	glBegin(GL_POLYGON);//Baixo
	glTexCoord2f(1.0, 1.0);glVertex3f(-0.65,0,2);//J
	glTexCoord2f(0.0, 1.0);glVertex3f(-0.65,0,1);//J
	glTexCoord2f(1.0, 1.0);glVertex3f(0.65,0,1);//K
	glTexCoord2f(0.0, 1.0);glVertex3f(0.65,0,2);//K
	glEnd();
	
	//PÉ TRAS
	
	glBegin(GL_POLYGON);//TRAS
	glTexCoord2f(0.0, 0.0);glVertex3f(-0.65,2,-1);//H
	glTexCoord2f(1.0, 0.0);glVertex3f(0.65,2,-1);//G
	glTexCoord2f(1.0, 1.0);glVertex3f(0.65,0,-1);//K
	glTexCoord2f(0.0, 1.0);glVertex3f(-0.65,0,-1);//J
	glEnd();
	
	
	glBegin(GL_POLYGON);//CIMA
	glTexCoord2f(0.0, 0.0);glVertex3f(-0.65,2,0);//H
	glTexCoord2f(1.0, 0.0);glVertex3f(-0.65,2,-1);//H
	glTexCoord2f(1.0, 1.0);glVertex3f(0.65,2,-1);//G
	glTexCoord2f(0.0, 1.0);glVertex3f(0.65,2,0);//G
	glEnd();
	
	glBegin(GL_POLYGON);//ESQ
	glTexCoord2f(0.0, 0.0);glVertex3f(-0.65,2,0);//H
	glTexCoord2f(1.0, 0.0);glVertex3f(-0.65,2,-1);//H
	glTexCoord2f(1.0, 1.0);glVertex3f(-0.65,0,-1);//J
	glTexCoord2f(0.0, 1.0);glVertex3f(-0.65,0,0);//J
	glEnd();
	
	glBegin(GL_POLYGON);//DIR
	glTexCoord2f(0.0, 0.0);glVertex3f(0.65,2,0);//G
	glTexCoord2f(1.0, 0.0);glVertex3f(0.65,2,-1);//G
	glTexCoord2f(1.0, 1.0);glVertex3f(0.65,0,-1);//K
	glTexCoord2f(0.0, 1.0);glVertex3f(0.65,0,0);//K
	glEnd();
	
	glBegin(GL_POLYGON);//Baixo
	glTexCoord2f(1.0, 1.0);glVertex3f(-0.65,0,0);//J
	glTexCoord2f(0.0, 1.0);glVertex3f(-0.65,0,-1);//J
	glTexCoord2f(1.0, 1.0);glVertex3f(0.65,0,-1);//K
	glTexCoord2f(0.0, 1.0);glVertex3f(0.65,0,0);//K
	glEnd();
	
	glDisable(GL_TEXTURE_2D);

}

void display(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    /* Limpa o Buffer de Pixels */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /* Estabelece a cor da primitiva como preta */
    glColor3f (1.0, 1.0, 1.0);
    
    /* Define a posição do observador */
	gluLookAt(eyex, eyey, eyez, 0, 0, 0, 0, 1, 0);
	glRotatef(angle, 0,1,0);
	glRotatef(anglex, 1,0,0);
	glRotatef(anglez, 0,0,1);
    
    glTranslatef(angleMX,angleMY,angleMz);
    glPushMatrix();
    	glScalef(4,4,4);
		drawMBat();

	glPopMatrix();
	//Executa os comandos OpenGL 
	glFlush();
}

void TimerFunc(int valor) {
		if((angleMX>=-60 && angleMX <0) && (angleMY>=-30 && angleMY<30)){
			angleMX = angleMX +1;
			angleMY = angleMY +1;
		}
		if((angleMX>=0 && angleMX <60) && (angleMY<=30 && angleMY>0)){
			angleMX = angleMX +2;
			angleMY = angleMY -1;
		}
		if((angleMX<=60 && angleMX >0) && (angleMY<=0 && angleMY>-60)){
			angleMX = angleMX -1;
			angleMY = angleMY -1;
		}
		if((angleMX<=0 && angleMX >-60) && (angleMY>=-60 && angleMY<-30)){
			angleMX = angleMX -2;
			angleMY = angleMY +1;
		}
		//angle++;
	    glutPostRedisplay();
	    glutTimerFunc( 33, TimerFunc, 1);
}

void reshape(int width, int height) {
	glViewport(0,0,width,height); // Reset The Current Viewport
	
	glMatrixMode(GL_PROJECTION); // Select The Projection Matrix
	glLoadIdentity(); // Reset The Projection Matrix
	
	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(float)640/(float)480,0.1f,1000.0f);
	// Always keeps the same aspect as a 640 wide and 480 high window
	
	glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
	glLoadIdentity(); // Reset The Modelview Matrix
}

void key(unsigned char key, int x, int y) {
	switch(key) {
		case 27:
			exit(0);
			break;
		case 'y': /* e key rotates at elbow */
	 	 aux = (int) (angle + 5);
		 angle = aux % 360;
		 glutPostRedisplay();
		 break;
		case 'Y': /* e key rotates at elbow */
	 	 aux = (int) (angle - 5);
		 angle = aux % 360;
		 glutPostRedisplay();
		 break;
		 
		case 'x': /* e key rotates at elbow */
	 	 aux = (int) (anglex + 5);
		 anglex = aux % 360;
		 glutPostRedisplay();
		 break;
		case 'X': /* e key rotates at elbow */
	 	 aux = (int) (anglex - 5);
		 anglex = aux % 360;
		 glutPostRedisplay();
		 break;
		 
		case 'z': /* e key rotates at elbow */
	 	 aux = (int) (anglez + 5);
		 anglez = aux % 360;
		 glutPostRedisplay();
		 break;
		case 'Z': /* e key rotates at elbow */
	 	 aux = (int) (anglez - 5);
		 anglez = aux % 360;
		 glutPostRedisplay();
		 break;
			
	}
}

void init() {
	glClearColor(1,1,1,0);
	glClearDepth(1.0); // Enables Clearing Of The Depth Buffer
	glDepthFunc(GL_LESS); // The Type Of Depth Test To Do
	glEnable(GL_DEPTH_TEST); // Enables Depth Testing
	make_tex();
    initTexture ();
    //sphere = gluNewQuadric();
    glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH); // Enables Smooth Color Shading
}

/*
Funcao principal do programa.
*/
int main(int argc, char** argv)
{
	//Inicia a Telinha
	glutInit(&argc,argv);
	
    /*
    Estabelece o modo de exibicao a ser utilizado pela janela a ser
    neste caso utiliza-se de um buffer duplo, ou seja, a apresentacao
    execucao
    Define o modo de cores como RGBA
    */
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    
    /*
    Determina o tamanho em pixels da
    janela a ser criada
    */
    glutInitWindowSize (500, 500);
    
    /*
    Estabelece a posicao inicial para criacao da
    janela
    */
    glutInitWindowPosition (100, 100);
    
    /*
    Cria uma janela com base nos parametros especificados
    nas funcoes glutInitWindowSize e glutInitWindowPosition
    com o nome de titulo especificado em seu argumento
    */
    glutCreateWindow ("Projeto Base");
    
    /*
    Especifica os parametros inicias para as variaveis
    de estado do OpenGL
    */
    init ();
    //TimerFunc(angle);
    // Associa a funcao display como uma funcao de callback
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);
    TimerFunc(1);
    
    /*
    Inicia a execucao do programa OpenGL.
    O programa ira executar num loop infinito devendo
    o desenvolvedor especificar as condicoes de saida do mesmo
    atraves de interrupcoes no proprio programa ou atraves
    de comandos de mouse ou teclado como funcoes de callback
    */
    glutMainLoop();
    return 0;
}
