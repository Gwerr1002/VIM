#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <unistd.h>

int x_size, y_size, z_size;

void setDimensions(int dimx,int dimy, int dimz){
  x_size = dimx;
  y_size = dimy;
  z_size = dimz;
}

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

//------Mostrar solo un corte------
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

void rotatez(int angle) {
  glTranslated((float)x_size/2,(float)y_size/2,0);
  glRotatef(angle,0,0,1);
  //Rota sobre el eje z
  glTranslated(-(float)x_size/2,-(float)y_size/2,0);
}
