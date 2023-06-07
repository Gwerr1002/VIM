#include "mod3D.h"

void display(void);
void rota(void);
float ang = 0; //declaración global

int main(int argc, char **argv){
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
  glutInitWindowSize(600,400);
  glutInitWindowPosition(500,100);
  glutCreateWindow("Demo");
  glutDisplayFunc(display);
  glutIdleFunc(rota);
  glutMainLoop(); //hasta aquí se crea la ventana
}

void display(void) {
  setDimensions(256,256,109);
  setLen(5503266); //materia blanca
  //setLen(8230230);
  unsigned char *strips = malloc(len);
  load_poly(strips);
  init();
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glRotatef(ang,0,1,0);
  show_poly(strips);
  glEnd();
  glFlush();
  glutSwapBuffers(); //Se despliega en doble buffer
}
void rota(void) {
  ang += 5;
  if (ang>360) ang = ang-360;
  glutPostRedisplay();
}
