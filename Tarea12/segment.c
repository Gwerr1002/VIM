#include "seg.h"

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
  unsigned char *segment1 = malloc(x_size * y_size * z_size);
  unsigned char *segment2 = malloc(x_size * y_size * z_size);
  unsigned char *sig1 = malloc(x_size * y_size * z_size);
  unsigned char *sig2 = malloc(x_size * y_size * z_size);
  abrirVOL(volumen);
  initDespliegue();
  clean(segment1);
  clean(segment2);
  printf("Arreglo limpio\n");
  //sigmoidFilter(unsigned char *vol,float max,float min,float beta,float alpha)
  //craneo
  sigmoidFilter(sig1,volumen,255,0,80,5);//80
  segmentar(segment1,sig1,200,255);
  free(sig1);
  //sigmoidFilterBilateral(volumen,255,0,20,70,5,5);//55,0,20,100,5,5 curioso
  //materia
  sigmoidFilterBilateral(sig2,volumen,255,0,60,90,0.1,.5);
  segmentar(segment2,sig2,200,255);
  free(volumen);
  free(sig2);
  unsigned char *res = malloc(x_size * y_size * z_size);
  clean(res);
  resta_bin(res,segment2,segment1);
  printf("Segmentado\n");
  printf("Despilegue\n");
  shapeSlices(res);
}
