#include "open.h"

char name[] = "../RMHEA109S";
void display();

void main(int argc,char **argv){
  glutInit(&argc,argv);
  setDimensions(256,256,109);
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
  glutInitWindowSize(x_size,y_size);
  glutInitWindowPosition(500,100);
  glutCreateWindow("Apertura de archivos");
  glutDisplayFunc(display);
  glutMainLoop(); //hasta aquí se crea la ventana
}

void display(/* arguments */) {
  unsigned char *volumen = malloc(x_size * y_size * z_size);
  unsigned char *slice = malloc(x_size*y_size);
  float complex a = 1 + 1*I,b = 1e4 + 1*I,c = 1 + 1*I,d = 1 + 1*I;
  abrirVOL(volumen,name);
  copyzSlice(volumen,slice,40);
  free(volumen);
  unsigned char *transformation = malloc(x_size*y_size);
  clean(transformation);
  imApplyMobius(slice, transformation, a, b, c,d, 10);
  
  initDespliegue();
  imShow(transformation);
  free(slice);
  free(transformation);
}
