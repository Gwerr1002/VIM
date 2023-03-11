#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <unistd.h>
#include <complex.h>

int x_size, y_size, z_size;

void setDimensions(int dimx,int dimy, int dimz){
  x_size = dimx;
  y_size = dimy;
  z_size = dimz;
}

void copyzSlice(unsigned char *vol,unsigned char *slice,int z) {
  for(int x = 0; x < x_size; x++){
    for(int y = 0; y < y_size; y++){
      slice[x+x_size*y] = vol[x+x_size*y+x_size*y_size*z];
    }
  }
}

//-----Abrir volumen de imagenes------
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

//-----Inicializar Despliegue------
void initDespliegue(void) {
glClearColor(0.0,0.0,0.0,0.0); //pone fondo en negro
glClear(GL_COLOR_BUFFER_BIT); //Habilita la limpieza de pantalla
glOrtho(0,x_size-1,0,y_size-1,0,1); //Define el sistema de referencia
}

void imShow(unsigned char *im) {
  glNewList(0,GL_COMPILE_AND_EXECUTE);
  for(int x = 0; x < x_size; x++){
    for(int y = 0; y < y_size; y++){
      glColor3f((float) im[x+x_size*y]/256,(float) im[x+x_size*y]/256,(float) im[x+x_size*y]/256);
      glBegin(GL_POINTS);
      glVertex2i(x,y);
      glEnd();
    }
  }
  glEndList();
  glCallList(0); //Se llama a la primera figura de la lista
  glutSwapBuffers(); //Se despliega en doble buffer
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

//--------Rotar volumenes---------
void rotatez(int angle) {
  glTranslated((float)x_size/2,(float)y_size/2,0);
  glRotatef(angle,0,0,1);
  //Rota sobre el eje z
  glTranslated(-(float)x_size/2,-(float)y_size/2,0);
}

//-------------Mobius------------
float mobius(int pixel, float complex a, float complex b, float complex c,float complex d, int n) {
  // pixel es la posiciòn no la intensidad en ese punto
  float complex calc;
  float newPixel;
  calc = (float) pixel+0*I;
  //printf("%d : ", pixel);
  //printf("%f+%fi ", crealf(calc),cimagf(calc));
  for (int iter = 0; iter < n; iter++){
    calc = (a*calc+b)/(c*calc+d);
  }
  newPixel =  cabsf(calc);
  //printf("%f\n", newPixel);
  return newPixel;
}


void imShowMobius(unsigned char *im, float complex a, float complex b, float complex c,float complex d, int n) {
  float Mobx,Moby;
  glNewList(1,GL_COMPILE);
  for(int x = 0; x < x_size; x++){
    for(int y = 0; y < y_size; y++){
      Mobx = mobius(x, a, b, c,d, n);
      Moby = mobius(y, a, b, c,d, n);
      glColor3f((float) im[x+x_size*y]/256,(float) im[x+x_size*y]/256,(float) im[x+x_size*y]/256);
      glBegin(GL_POINTS);
      printf("%f %f\n",Mobx,Moby );
      glVertex2i(Mobx,Moby);
      glEnd();
    }
  }
  glEndList();
  glCallList(1); //Se llama a la primera figura de la lista
  glutSwapBuffers(); //Se despliega en doble buffer
}
