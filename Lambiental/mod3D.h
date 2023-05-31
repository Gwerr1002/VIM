#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <unistd.h>
#include <math.h>


void init(){
  glClearColor(0,0,0,0);
  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHT0);
  float luz_ambient[]= {1,0,0,1};
  glLightfv(GL_LIGHT0,GL_AMBIENT,luz_ambient);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-3,3,-3,3,-3,3);
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
