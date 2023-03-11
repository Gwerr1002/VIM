#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <unistd.h>
#include <math.h>

int x_size, y_size, z_size;

void setDimensions(int dimx,int dimy, int dimz){
  x_size = dimx;
  y_size = dimy;
  z_size = dimz;
}

//--------Abrir y leer un volumen-------------
void abrirVOL(unsigned char *vol,char *name) {
  FILE *file;
  //256 256 190
  if ((file = fopen(name, "rb")) == NULL){
    // control del error de apertura
    printf( " Error en la apertura.\n Exit. \n ");
    exit(1);
  }
  for(int z = 0 ; z < z_size; z++){
    for(int x = 0; x < x_size; x++){
      for(int y = 0; y < y_size; y++){
        fread(&vol[x+x_size*y+x_size*y_size*z],1,1,file);
      }
    }
  }
  fclose (file);
}

//-------Copiar un corte-----------
void copyzSlice(unsigned char *vol,unsigned char *slice,int z) {
  for(int x = 0; x < x_size; x++){
    for(int y = 0; y < y_size; y++){
      slice[x+x_size*y] = vol[x+x_size*y+x_size*y_size*z];
    }
  }
}

//-----Inicializar Despliegue------
void initDespliegue(void) {
glClearColor(0.0,0.0,0.0,0.0); //pone fondo en negro
glClear(GL_COLOR_BUFFER_BIT); //Habilita la limpieza de pantalla
glOrtho(0,x_size-1,0,y_size-1,0,1); //Define el sistema de referencia
}

//---------Formar Cortes-----------
void shapeSlices(unsigned char *vol) {
  for(int z = 0; z<z_size; z++){
    glNewList(z,GL_COMPILE_AND_EXECUTE);
    for (int y=0; y<y_size; y++){
      for (int x=0; x<x_size; x++){
        glColor3f((float)vol[x+x_size*y+x_size*y_size*z]/256,(float)vol[x+x_size*y+x_size*y_size*z]/256,(float)vol[x+x_size*y+x_size*y_size*z]/256);
        glBegin(GL_POINTS);
        glVertex2i(x,y);
        glEnd();
      }
    }
    glEndList();
    glCallList(z); //Se llama a la primera figura de la lista
    glutSwapBuffers(); //Se despliega en doble buffer
    //sleep(.01);
  }
}


//Funciones para la transformacion castle_angel

double lambda(double x, double y, double centro[2], double radio){
  double lambda = sqrt(pow(x-centro[0],2.0)+pow(y-centro[1],2.0))/(sqrt(2.0)*radio);
  //printf("%fl\n", lambda);
  if(lambda > 1.0){lambda = 1.0;}
  return lambda;
}

//---------Castle Angel-------------

void castel_angel(double *xy,int pixelx, int pixely, double alfa, double a, double b, double c, double d, double centro[2], double radio) {
  double xi = (double)pixelx, yi = (double)pixely;
  double l = lambda(xi, yi, centro, radio);
  xy[0]=(1-pow(l,alfa))*((1+a)*xi+b*yi)+pow(l,alfa)*xi;
  //printf("%fl ",xy[0]);
  xy[1]=(1-pow(l,alfa))*(c*xi+(1+d)*yi)+pow(l,alfa)*yi;
  //printf("%fl\n",xy[1]);
}

void imshowCastel(unsigned char *im, double alpha, double a, double b, double c, double d, double centro[2], double radio) {
  double *xy = malloc(2);
  glNewList(1,GL_COMPILE_AND_EXECUTE);
  for(int x = 0; x < x_size; x++){
    for(int y = 0; y < y_size; y++){
      castel_angel(xy,x,y,alpha, a, b, c, d, centro, radio);
      glColor3f((float) im[x+x_size*y]/256,(float) im[x+x_size*y]/256,(float) im[x+x_size*y]/256);
      glBegin(GL_POINTS);
        glVertex2i((int)xy[0],(int)xy[1]);
      glEnd();
    }
  }
  glEndList();
  glCallList(1); //Se llama a la primera figura de la lista
  glutSwapBuffers(); //Se despliega en doble buffer
}
