#include "mod3D.h"

void display(void);
void rota(void);
float ang = 0; //declaración global

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

void display(void) {
  init();
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glRotatef(ang,1,1,0);
  cubo();
  glFlush();
  glutSwapBuffers(); //Se despliega en doble buffer
}
void rota(void) {
  ang += 1;
  if (ang>360) ang = ang-360;
  glutPostRedisplay();
}
