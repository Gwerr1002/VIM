#include"open.h"

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
  printf("Abriendo volumen\n");
  abrirVOL(volumen,name);
  printf("Volumen abierto\nDespliegue\n");
  initDespliegue();
  rotatez(45);
  shapeSlices(volumen);
}
