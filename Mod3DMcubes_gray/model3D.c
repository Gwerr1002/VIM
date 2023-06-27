#include "mod3D.h"

void display(void);
void rota(void);
float ang = 0; //declaración global

int main(int argc, char **argv){
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
  glutInitWindowSize(1500,650);
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
  unsigned char *vol = malloc(x_size * y_size * z_size);
  load_poly(strips);
  abrirVOL(vol,"../RMHEA109S");
  init();
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glRotatef(ang,0,1,0);
  show_poly_gray(strips,vol);
  free(vol);
  free(strips);
  glEnd();
  glFlush();
  glutSwapBuffers(); //Se despliega en doble buffer
}
void rota(void) {
  ang += 5;
  if (ang>360) ang = ang-360;
  glutPostRedisplay();
}
