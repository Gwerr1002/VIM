#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <unistd.h>
#include <math.h>

#define pi 3.1416

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
  float *mat = malloc(16);
  if(mat == NULL){
    printf("No se asigno memoria a la matriz\n");
    exit(1);
  }
  for (unsigned int i=0; i<16;i++){ mat[i]=0;}
  mat[0]=1; //La matriz se organiza en un orden de primero renglones
  mat[8]=cos(45*pi/180)/2;
  mat[5]=1;
  mat[9]=sin(45*pi/180)/2;
  mat[10]=1;
  mat[15]=1;
  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-3,3,-3,3,-3,3);
  glLoadMatrixf(mat); //Se activa la matriz de transformación en coordenadas
    cubo(); //Define un cubo
  glutSwapBuffers(); //Se despliega en doble buffer
  free(mat);
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
