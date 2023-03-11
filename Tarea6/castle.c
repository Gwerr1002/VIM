#include "open.h"

char name[] = "RMHEA109S";
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

void display(void) {
  unsigned char *volumen = malloc(x_size * y_size * z_size);
  unsigned char *slice = malloc(x_size*y_size);
  int zslice = 40;
  printf("Abriendo volumen\n");
  abrirVOL(volumen,name);
  printf("Volumen abierto\nAplicando transformacion\n");
  copyzSlice(volumen,slice,zslice);
  free(volumen);
  initDespliegue();
  //imShow(slice);

  double centro[2] = {150,150};
  //imshowCaslte(unsigned char *im, float alpha, float a, float b, float c, float d, int centro[2], float radio)
  imshowCastel(slice, 1.5, -0.2, 0.1, 0.1, -0.2, centro, 50);
  /*
  double centro[2] = {150,150};
  //imshowCaslte(unsigned char *im, float alpha, float a, float b, float c, float d, int centro[2], float radio)
  imshowCastel(slice, 3, -0.2, -0.5, -.1, -0.2, centro, 50);
  /*
  double centro[2] = {128,128};
  imshowCastel(slice, 3, 0, 0, 0, 0.52, centro, 100);
  */
  free(slice);
}
