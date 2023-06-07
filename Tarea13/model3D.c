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
  setDimensions(256,256,109);
  unsigned char *segmentacion = malloc(x_size * y_size * z_size);
  unsigned char *vol = malloc(x_size * y_size * z_size);
  abrirVOL(segmentacion,name);
  abrirVOL(vol,"../RMHEA109S");
  init();
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glRotatef(ang,1,1,0);
  show3D(segmentacion,vol);
  glEnd();
  glFlush();
  glutSwapBuffers(); //Se despliega en doble buffer
}
void rota(void) {
  ang += 5;
  if (ang>360) ang = ang-360;
  glutPostRedisplay();
}
