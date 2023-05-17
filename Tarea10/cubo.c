//Muestra la proyección ortográfica isométrica mediante rotaciones
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <unistd.h>

void display();
void cubo();

void main(int argc,char **argv){
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
  glutInitWindowSize(700,580);
  glutInitWindowPosition(50,100);
  glutCreateWindow("Despliegue de Obj. 3D");
  glutDisplayFunc(display);
  glutMainLoop(); //hasta aquí se crea la ventana
}

void display(){
  //init();
  //glOrtho(3,3,3,3,3,3);
  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
    glRotatef(45,1,0,0);
    glRotatef(45,0,1,0);
    cubo(); //Define un cubo
  glPopMatrix();
  glutSwapBuffers(); //Se despliega en doble buffer
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
  glFlush();
}
