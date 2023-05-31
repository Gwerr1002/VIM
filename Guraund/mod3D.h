#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <unistd.h>
#include <math.h>


void init(){
  float	luz_blanca[]={1,1,1,0},luz_pos[]={1,0,0,0};
  float	lmodel_ambient[]={1,1,1,1.0};	//Color	de	la	luz	ambiental
  float	mat_especular[]={1,1,1,1};
  glClearColor(0,0,0,0.0);			//pone	fondo	en	negro
  glShadeModel(GL_SMOOTH);				//Sombreado	de	Gouraud
  glMaterialfv(GL_FRONT,GL_SPECULAR,mat_especular);
  glLightfv(GL_LIGHT0,	GL_POSITION,	luz_pos);
  glLightfv(GL_LIGHT0,	GL_DIFFUSE,	luz_blanca);
  glLightfv(GL_LIGHT0,	GL_AMBIENT,	luz_blanca);
  glLightfv(GL_LIGHT0,	GL_SPECULAR,	luz_blanca);
  glEnable(GL_LIGHTING);				//Habilita	modo	iluminación
  glEnable(GL_LIGHT0);						//Habilita	la	fuente	de	luz
  glEnable(GL_DEPTH_TEST);		//Habilita	Z-Buffer
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	 //Habilita	 la	limpieza	de	pantalla	y	Z-Buffer
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1,2,-1,2,-2,2);		//Proyección	ortográfica
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void cubo() {
  glColor3f(1,0,0);
  glBegin(GL_QUADS);//frontal
    glVertex3f(.25,-.25,-.25);
    glVertex3f(.25,.25,-.25);
    glVertex3f(.25,.25,.25);
    glVertex3f(.25,-.25,.25);
  glEnd();
  glColor3f(1,1,1);//trasera
  glBegin(GL_QUADS);
    glVertex3f(-.25,-.25,-.25);
    glVertex3f(-.25,.25,-.25);
    glVertex3f(-.25,.25,.25);
    glVertex3f(-.25,-.25,.25);
  glEnd();
  glColor3f(0,1,0);//inferior
  glBegin(GL_QUADS);
    glVertex3f(.25,-.25,-.25);
    glVertex3f(.25,.25,-.25);
    glVertex3f(-.25,.25,-.25);
    glVertex3f(-.25,-.25,-.25);
  glEnd();
  glColor3f(0,0,1);//superior
  glBegin(GL_QUADS);
    glVertex3f(.25,-.25,.25);
    glVertex3f(.25,.25,.25);
    glVertex3f(-.25,.25,.25);
    glVertex3f(-.25,-.25,.25);
  glEnd();
  glColor3f(1,1,0);//lateral derecho
  glBegin(GL_QUADS);
    glVertex3f(.25,.25,.25);
    glVertex3f(.25,.25,-.25);
    glVertex3f(-.25,.25,-.25);
    glVertex3f(-.25,.25,.25);
  glEnd();
  glColor3f(0,1,1);//lateral izquierdo
  glBegin(GL_QUADS);
    glVertex3f(.25,-.25,.25);
    glVertex3f(.25,-.25,-.25);
    glVertex3f(-.25,-.25,-.25);
    glVertex3f(-.25,-.25,.25);
  glEnd();
}
