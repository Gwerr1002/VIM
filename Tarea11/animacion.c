#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <unistd.h>

float ang = 0; //declaración global

void cubo();
void piramid();
void init();

void display(void) {
  init();
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glRotatef(ang,1,1,0);
  cubo();
  piramid();
  glFlush();
  glutSwapBuffers(); //Se despliega en doble buffer
}
void rota(void) {
  ang += 1;
  if (ang>360) ang = ang-360;
  glutPostRedisplay();
}

int main(int argc, char **argv){
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
  glutInitWindowSize(640,480);
  glutInitWindowPosition(500,100);
  glutCreateWindow("Demo");
  glutDisplayFunc(display);
  glutIdleFunc(rota);
  glutMainLoop(); //hasta aquí se crea la ventana
}

void init() {
  glEnable(GL_DEPTH_TEST); //Habilita Z-Buffer
  glClearColor(0.0,0.0,0.0,0.0); //pone fondo en negro
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  //Habilita la limpieza de pantalla y el DEPTH_BUFFER para eliminar las superficies escondidas
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1,2,-1,2,-1,2);
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

void piramid() {
  glColor3f(0,1,1);//base
  glBegin(GL_QUADS);
    glVertex3f(1,1,.5);
    glVertex3f(1,1.5,.5);
    glVertex3f(.5,1.5,.5);
    glVertex3f(.5,1,.5);
  glEnd();
  glColor3f(1,0,0);
  glBegin(GL_TRIANGLES);
    glVertex3f(0.75,1.25,0);
    glVertex3f(1,1,.5);
    glVertex3f(1,1.5,.5);
  glEnd();
  glColor3f(0,1,0);
  glBegin(GL_TRIANGLES);
    glVertex3f(0.75,1.25,0);
    glVertex3f(1,1.5,.5);
    glVertex3f(.5,1.5,.5);
  glEnd();
  glColor3f(0,0,1);
  glBegin(GL_TRIANGLES);
    glVertex3f(0.75,1.25,0);
    glVertex3f(.5,1.5,.5);
    glVertex3f(.5,1,.5);
  glEnd();
  glColor3f(1,.5,0);
  glBegin(GL_TRIANGLES);
    glVertex3f(.75,1.25,0);
    glVertex3f(.5,1,.5);
    glVertex3f(1,1,.5);
  glEnd();
}
