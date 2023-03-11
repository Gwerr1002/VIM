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
  printf("Abriendo volumen\n");
  abrirVOL(volumen,name);
  printf("Volumen abierto\nTrazando...\n");
  copyzSliceOblique(volumen,slice,40);
  //copyzSlice(volumen,slice,50);
  free(volumen);
  interpola_Hermite(slice,10,2,2,2);
  //interpola_Bezier(slice,2);
  //interpola_BSpline(slice,1);
  initDespliegue();
  imShow(slice);
  free(slice);
}
